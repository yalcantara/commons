/*
 * Timer.h
 *
 *  Created on: Mar 30, 2018
 *      Author: yaison
 */

#ifndef COMMONS_CORE_TIMER_H_
#define COMMONS_CORE_TIMER_H_

#include <chrono>

using namespace std::chrono;

namespace commons {
namespace core {

class Timer {
private:
	time_point<system_clock, nanoseconds> _start;
	time_point<system_clock, nanoseconds> _end;

public:
	Timer() {
		start();
	}

	void start() {
		_start = high_resolution_clock::now();
		_end = _start;
	}

	void end() {
		_end = high_resolution_clock::now();
	}

	long long elapsed_nanos() {
		nanoseconds ans = _end - _start;
		return ans.count();
	}

	long long elapsed_micros() {
		microseconds ans = duration_cast < microseconds > (_end - _start);
		return ans.count();
	}

	long long elapsed_millis() {
		milliseconds ans = duration_cast < milliseconds > (_end - _start);
		return ans.count();
	}

	void print() {
		long long took = (_end - _start).count();
		Timer::print(took);
	}

	void print_seconds() {
		long long took = duration_cast < nanoseconds > (_end - _start).count();
		double d = took / 1000000000.0;

		if (took < 1000) {
			printf("Took: %.9fs\n", d);
		} else if (took < 1000000) {
			printf("Took: %.6fs\n", d);
		} else if (took < 1000000000) {
			printf("Took: %.3fs\n", d);
		} else {
			printf("Took: %.1fs\n", d);
		}

		fflush (stdout);
	}

	static void print(long long took) {

		if (took < 1000) {
			double d = took;
			printf("Took: %5.1fns\n", d);
		} else if (took < 1000000) {
			double d = took / 1000.0;
			printf("Took: %5.1fμs\n", d);
		} else if (took < 1000000000) {
			double d = took / (1000000.0);
			printf("Took: %5.1fms\n", d);
		} else {
			double d = took / (1000000000.0);
			printf("Took: %5.1fs\n", d);
		}

		fflush (stdout);
	}

};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_TIMER_H_ */
