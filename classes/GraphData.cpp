#pragma once
#include <Python.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

struct Node {
	int x, y, d;
};

class GraphData {
private:
	Node *nodes;
public:
	int n, c;

	GraphData(PyObject *problem) {
		n = PyLong_AsLong(PyDict_GetItemString(problem, "n"));
		c = PyLong_AsLong(PyDict_GetItemString(problem, "c"));
		nodes = new Node[n];
		PyObject *v = PyDict_GetItemString(problem, "v");
		PyObject *d = PyDict_GetItemString(problem, "d");
		for (int i = 0; i < n; ++i) {
			PyObject *node = PyList_GET_ITEM(v, i);
			nodes[i].x = PyLong_AsLong(PyTuple_GET_ITEM(node, 0));
			nodes[i].y = PyLong_AsLong(PyTuple_GET_ITEM(node, 1));
			nodes[i].d = PyLong_AsLong(PyList_GET_ITEM(d, i));
		}
	}

	double dist(int a, int b) {
		ll dx = nodes[a].x - nodes[b].x;
		ll dy = nodes[a].y - nodes[b].y;
		return sqrt(dx * dx + dy * dy);
	}

	int demand(int a) {
		return nodes[a].d;
	}

	~GraphData() {
		delete[] nodes;
	}
};