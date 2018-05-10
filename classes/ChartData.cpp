#pragma once
#include <deque>
#include <vector>

using namespace std;

typedef long long ll;

class ChartData {
private:
	static const int MAX_LEVEL = 100;
	static const int DEFAULT_MAX_SIZE = 1000;
	int max_size, size = 0;

	deque <pair <ll, double> > levels[MAX_LEVEL];
public:
	ChartData(int max_size = DEFAULT_MAX_SIZE): max_size(max_size) {}

	void add_node(ll x, double y) {
		levels[0].push_back(make_pair(x, y));
		++size;
		compress_data();
	}

	vector <pair <ll, double> > get_points() {
		vector <pair <ll, double> > res;
		for (int i = MAX_LEVEL - 1; i >= 0; --i)
			for (auto & cur : levels[i])
				res.push_back(cur);
		return res;
	}

private:
	void compress_data() {
		int lvl = 0;
		while (size > max_size && lvl + 1 < MAX_LEVEL) {
			if (levels[lvl].size() < 3) {
				++lvl;
				continue;
			}
			pair <ll, double> mn = levels[lvl].front(), mx = mn;
			levels[lvl].pop_front();
			for (int i = 0; i < 2; ++i) {
				pair <ll, double> cur = levels[lvl].front();
				levels[lvl].pop_front();
				mn = (cur.second < mn.second) ? cur : mn;
				mx = !(cur.second < mx.second) ? cur : mx;
			}
			pair <ll, double> l = mn, r = mx;
			if (mx.first < mn.first)
				l = mx, r = mn;
			levels[lvl + 1].push_back(l);
			levels[lvl + 1].push_back(r);
			--size;
		}
	}
};