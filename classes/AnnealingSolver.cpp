#pragma once
#include <iostream>
#include <vector>
#include <Python.h>
#include <cmath>
#include <cstdlib>
#include "GraphData.cpp"
#include "RouteSolution.cpp"
#include "ChartData.cpp"
#include "AdvancedTimer.cpp"

using namespace std;

typedef long double ld;
typedef long long ll;

class AnnealingSolver {
private:
	RouteSolution *bestSolution, *currentSolution;
	ChartData *chart;
	AdvancedTimer timer;
	ld t, factor, tEnd;
	ll timeLimit, iterationsTotal;
	ll iterationsCnt = 0;

public:
	~AnnealingSolver() {
		delete bestSolution;
		delete currentSolution;
		delete chart;
	}

	AnnealingSolver(GraphData *graph, PyObject *settings) {
		bestSolution = currentSolution = new RouteSolution(graph);
		chart = new ChartData();
		timer.run();
		t = PyFloat_AsDouble(PyDict_GetItemString(settings, "T_START"));
		factor = PyFloat_AsDouble(PyDict_GetItemString(settings, "T_COOLING"));
		tEnd = PyFloat_AsDouble(PyDict_GetItemString(settings, "T_END"));
		timeLimit = PyLong_AsLongLong(PyDict_GetItemString(settings, "TIME_LIMIT")) * 1000;
		iterationsTotal = PyLong_AsLongLong(PyDict_GetItemString(settings, "ITERATIONS"));
	}

	bool isFinished() {
		return t < tEnd || timer.value() >= timeLimit || iterationsCnt >= iterationsTotal;
	}

	void runIteration() {
		RouteSolution *newSolution = new RouteSolution(currentSolution);
		ld delta = newSolution->cost - currentSolution->cost;
		if (ld(rand()) / RAND_MAX < exp(-delta / t)) {
			if (currentSolution != bestSolution)
				delete currentSolution;
			currentSolution = newSolution;
			if (currentSolution->cost < bestSolution->cost) {
				delete bestSolution;
				bestSolution = currentSolution;
			}
		} else
			delete newSolution;
		t *= factor;
		++iterationsCnt;
		chart->add_node(timer.value(), currentSolution->cost);
	}

	void pause() {
		timer.pause();
	}

	void unpause() {
		timer.run();
	}

	PyObject* makeUpdate() {
		PyObject *update = PyDict_New();
		PyDict_SetItemString(update, "stats", makeStats());
		PyDict_SetItemString(update, "currentCars", makeCars(currentSolution));
		PyDict_SetItemString(update, "bestCars", makeCars(bestSolution));
		PyDict_SetItemString(update, "currentRoutes", makeRoutes(currentSolution));
		PyDict_SetItemString(update, "bestRoutes", makeRoutes(bestSolution));
		PyDict_SetItemString(update, "chart", makeChart());
		return update;
	}
private:
	PyObject* makeStats() {
		PyObject *stats = PyDict_New();
		PyDict_SetItemString(stats, "TIME_PASSED", PyLong_FromLongLong(timer.value() / 1000));
		PyDict_SetItemString(stats, "ITERATIONS", PyLong_FromLongLong(iterationsCnt));
		PyDict_SetItemString(stats, "TEMPERATURE", PyFloat_FromDouble(t));
		PyDict_SetItemString(stats, "BEST_RESULT", PyFloat_FromDouble(bestSolution->cost));
		int p = min(iterationsCnt * 100 / iterationsTotal, 100ll);
		PyDict_SetItemString(stats, "PROGRESS", PyLong_FromLongLong(p));
		return stats;
	}

	PyObject* makeCars(RouteSolution *sol) {
		PyObject *cars = PyList_New(0);
		for (auto &route : sol->routes) {
			ll cargo = sol->graph->demand(route->r[0]);
			ld dist = sol->graph->dist(0, route->r[0]) + sol->graph->dist(route->r.back(), 0);
			for (int i = 1; i < route->r.size(); ++i) {
				cargo += sol->graph->demand(route->r[i]);
				dist += sol->graph->dist(route->r[i - 1], route->r[i]);
			}
			PyObject *car = PyDict_New();
			PyDict_SetItemString(car, "cargo", PyLong_FromLongLong(cargo));
			PyDict_SetItemString(car, "distance", PyFloat_FromDouble(dist));
			PyList_Append(cars, car);
		}
		return cars;
	}

	PyObject* makeRoutes(RouteSolution *sol) {
		PyObject *routes = PyList_New(0);
		for (auto &route : sol->routes) {
			PyObject *pyroute = PyList_New(0);
			for (auto &x : route->r)
				PyList_Append(pyroute, PyLong_FromLongLong(x));
			PyList_Append(routes, pyroute);
		}
		return routes;
	}

	PyObject* makeChart() {
		vector <pair <ll, double> > raw = chart->get_points();
		PyObject *points = PyList_New(0);
		for (auto &p : raw) {
			PyObject *x = PyLong_FromLongLong(p.first);
			PyObject *y = PyFloat_FromDouble(p.second);
			PyList_Append(points, PyTuple_Pack(2, x, y));
		}
		return points;
	}
};