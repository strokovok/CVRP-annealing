from cefpython3 import cefpython as cef
import win32gui
import threading
import sys
import time

if not hasattr(sys, 'argv'):
    sys.argv  = ['']

browser = None
# events = queue.Queue()
# last_event = None

def run_browser():
    sys.excepthook = cef.ExceptHook
    cef.Initialize()
    global browser
    browser = cef.CreateBrowserSync(url="file:///interface/dist/index.html", window_title="CVRP")
    win32gui.MoveWindow(browser.GetWindowHandle(), 50, 50, 1190, 665, True)
    cef.MessageLoop()
    cef.Shutdown()

def run_browser_async():
	global browser
	t = threading.Thread(target=run_browser)
	t.start()

def execute_js_func(func, arg):
    browser.ExecuteFunction(func, arg)