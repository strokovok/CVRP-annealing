#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include "GraphData.cpp"

using namespace std;

struct Route {
	vector <int> r;
	int c;
	Route(int c): c(c) {}
};

class RouteSolution {
public:
	GraphData *graph;
	vector <Route*> routes;
	double cost;

	~RouteSolution() {
		for (auto &route : routes)
			delete route;
	}

	RouteSolution(GraphData *graph): graph(graph) {
		routes.push_back(new Route(graph->c));
		for (int i = 1; i < graph->n; ++i) {
			if (routes.back()->c < graph->demand(i))
				routes.push_back(new Route(graph->c));
			routes.back()->r.push_back(i);
			routes.back()->c -= graph->demand(i);
		}

		count_cost();
	}

	RouteSolution(RouteSolution *prev): graph(prev->graph) {
		int change = min(1 + rand() % 7, graph->n - 1);
		vector <int> filter;
		for (int i = 1; i < graph->n; ++i)
			filter.push_back(i);
		random_shuffle(filter.begin(), filter.end());
		filter.resize(change);
		set <int> changed;
		for (auto &x : filter)
			changed.insert(x);
		for (int i = 0; i < prev->routes.size(); ++i) {
			routes.push_back(new Route(graph->c));
			for (auto &x : prev->routes[i]->r)
				if (changed.count(x) == 0) {
					routes.back()->r.push_back(x);
					routes.back()->c -= graph->demand(x);
				}
			if (routes.back()->r.size() == 0)
				routes.pop_back();
		}
		if (routes.size() == 0)
			routes.push_back(new Route(graph->c));
		vector <int> routesOrder, changedOrder;
		for (int i = 0; i < routes.size(); ++i)
			routesOrder.push_back(i);
		for (auto &x : changed)
			changedOrder.push_back(x);
		random_shuffle(changedOrder.begin(), changedOrder.end());
		vector <int> rest;
		for (auto &x : changedOrder) {
			random_shuffle(routesOrder.begin(), routesOrder.end());
			bool inserted = false;
			for (auto &i : routesOrder) {
				if (routes[i]->c < graph->demand(x))
					continue;
				vector <int> &r = routes[i]->r;
				auto pos = r.begin() + rand() % (r.size() + 1);
				r.insert(pos, x);
				routes[i]->c -= graph->demand(x);
				inserted = true;
				break;
			}
			if (!inserted)
				rest.push_back(x);
		}
		for (auto &x : rest) {
			if (routes.back()->c < graph->demand(x))
				routes.push_back(new Route(graph->c));
			routes.back()->r.push_back(x);
			routes.back()->c -= graph->demand(x);
		}

		count_cost();
	}

private:
	void count_cost() {
		cost = 0;
		for (auto &route : routes) {
			cost += graph->dist(0, route->r[0]);
			for (int i = 1; i < route->r.size(); ++i)
				cost += graph->dist(route->r[i - 1], route->r[i]);
			cost += graph->dist(route->r.back(), 0);
		}
	}
};