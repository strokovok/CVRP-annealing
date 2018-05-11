from cefpython3 import cefpython as cef
import threading
import sys
import wx
from pyutils.parseproblem import parseproblem
from pyutils.parsesolution import parsesolution
import queue
wx.DisableAsserts()

if not hasattr(sys, 'argv'):
    sys.argv  = ['']

browser = None
events = queue.Queue()
last_event = None
problem = None

def extract_event():
    last_event = None if events.empty() else events.get()
    return last_event

def load_solution():
    app = wx.App(None)
    dialog = wx.FileDialog(None, 'Open', style=(wx.FD_OPEN | wx.FD_FILE_MUST_EXIST))
    if dialog.ShowModal() != wx.ID_OK:
        return
    sendAppEvent({'newState': 'SOLUTION_LOADING'})
    path = dialog.GetPath()
    dialog.Destroy()
    global problem
    solution = parsesolution(path, problem)
    if solution is None:
        sendAppEvent({'newState': 'INCORRECT_SOLUTION'})
    else:
        sendAppEvent({
            'newState': 'SOLUTION_VIEW',
            'update': {
                'stats': {
                    'BEST_RESULT': solution['cost'],
                },
                'currentCars': solution['cars'],
                'bestCars': solution['cars'],
                'currentRoutes': solution['routes'],
                'bestRoutes': solution['routes']
            }
        })

def load_problem():
    app = wx.App(None)
    dialog = wx.FileDialog(None, 'Open', style=(wx.FD_OPEN | wx.FD_FILE_MUST_EXIST))
    if dialog.ShowModal() != wx.ID_OK:
        return
    path = dialog.GetPath()
    dialog.Destroy()
    global problem
    problem = parseproblem(path)
    if problem is None:
        sendAppEvent({'newState': 'INCORRECT_PROBLEM'})
    else:
        sendAppEvent({
            'newState': 'PROBLEM_LOADING',
            'update': {
                'graph': problem['v'],
                'file': path.split('\\')[-1]
            }
        })
        events.put({
            'type': 'PROBLEM_LOADING',
            'problem': problem
        })

def save_solution(solution):
    app = wx.App(None)
    dialog = wx.FileDialog(None, 'Save', style=(wx.FD_SAVE))
    if dialog.ShowModal() != wx.ID_OK:
        return
    path = dialog.GetPath()
    dialog.Destroy()
    f = open(path, 'w')
    num = 0
    for route in solution['routes']:
        num += 1
        f.write('Route #{}: '.format(num) + ' '.join(list(map(str, route))) + '\n')
    f.write('cost {}'.format(int(solution['cost'])))
    f.close()

def launch_solve(settings):
    settings['T_START'] = float(settings['T_START'])
    settings['T_END'] = float(settings['T_END'])
    settings['T_COOLING'] = float(settings['T_COOLING'])
    settings['ITERATIONS'] = int(settings['ITERATIONS'])
    settings['TIME_LIMIT'] = int(settings['TIME_LIMIT'])
    settings['MIN_ITERATION_DELAY'] = int(settings['MIN_ITERATION_DELAY'])
    events.put({
        'type': 'LAUNCH',
        'settings': settings
    })

def pause_solve():
    events.put({ 'type': 'PAUSE' })

def stop_solve():
    events.put({ 'type': 'STOP' })

class CloseHandler(object):
    def OnBeforeClose(self, browser):
        events.put({ 'type': 'CLOSE' })

def run_browser():
    sys.excepthook = cef.ExceptHook
    cef.Initialize({ 'context_menu': { 'enabled': False } })
    global browser
    browser = cef.CreateBrowserSync(url="file:///interface/dist/index.html", window_title="CVRP")
    browser.SetClientHandler(CloseHandler())

    bindings = cef.JavascriptBindings(bindToFrames=False, bindToPopups=False)
    bindings.SetFunction('requestProblemLoading', load_problem)
    bindings.SetFunction('requestSolutionLoading', load_solution)
    bindings.SetFunction('requestSolutionSaving', save_solution)
    bindings.SetFunction('requestLaunchSolve', launch_solve)
    bindings.SetFunction('requestPauseSolve', pause_solve)
    bindings.SetFunction('requestStopSolve', stop_solve)
    browser.SetJavascriptBindings(bindings)

    cef.MessageLoop()
    cef.Shutdown()

def run_browser_async():
    t = threading.Thread(target=run_browser)
    t.start()

def sendAppEvent(event):
    browser.ExecuteFunction('handleAppEvent', event)