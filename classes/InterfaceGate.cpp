#pragma once
#include <Python.h>
#include <vector>
#include "ChartData.cpp"

using namespace std;

typedef long long ll;

class InterfaceGate {
private:
	static PyObject *bridge_dict;
public:
	static void init() {
		Py_Initialize();
		PyEval_InitThreads();
		PyEval_SaveThread();

		auto state = PyGILState_Ensure();
		bridge_dict = PyModule_GetDict(PyImport_ImportModule("bridge"));
		call("run_browser_async", PyTuple_New(0));
		PyGILState_Release(state);
	}

	static void update_chart(ChartData *chart) {
		auto state = PyGILState_Ensure();
		vector <pair <ll, ll> > data = chart->get_points();
		PyObject *points = PyTuple_New(data.size());
		for (int i = 0; i < data.size(); ++i) {
			PyObject *x = PyLong_FromLong(data[i].first);
			PyObject *y = PyLong_FromLong(data[i].second);
			PyTuple_SET_ITEM(points, i, PyTuple_Pack(2, x, y));
		}
		execjs("updateChart", points);
		PyGILState_Release(state);
	}
private:
	InterfaceGate() {}

	static void execjs(string func, PyObject *args) {
		call("execute_js_func", PyTuple_Pack(2, PyUnicode_FromString(func.c_str()), args));
	}

	static PyObject* call(string func, PyObject *args) {
		return PyObject_CallObject(PyDict_GetItemString(bridge_dict, func.c_str()), args);
	}
};

PyObject* InterfaceGate::bridge_dict;