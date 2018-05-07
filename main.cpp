#include <iostream>
#include "classes/ChartData.cpp"
#include "classes/InterfaceGate.cpp"

using namespace std;

int main() {
	InterfaceGate::init();
	ChartData *chart = new ChartData();
	int cnt = 0;
	while (true) {
		int x;
		cin >> x;
		for (int i = 0; i < x; ++i)
			chart->add_node(++cnt, i);
		InterfaceGate::update_chart(chart);
	}
	return 0;
}