#pragma once
#include <ctime>
#include <chrono>

typedef long long ll;
typedef std::chrono::steady_clock::time_point tp;

class AdvancedTimer {
private:
	ll duration = 0;
	bool active = false;
	tp last_point;

	tp now() {
		return std::chrono::steady_clock::now();
	}

	ll dist(tp start, tp end) {
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
public:
	AdvancedTimer() {}

	void run() {
		if (!active) {
			active = true;
			last_point = now();
		}
	}

	void pause() {
		if (active) {
			active = false;
			duration += dist(last_point, now());
		}
	}

	ll value() {
		ll delta = (active) ? dist(last_point, now()) : 0;
		return duration + delta;
	}

	void clear() {
		duration = 0;
		active = false;
	}
};