/*
 * Performance.h
 *
 *  Created on: Mar 30, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_PERFORMANCE_H_
#define COMMONS_CORE_PERFORMANCE_H_

#include <functional>
#include <chrono>
#include <commons/core/Timer.h>

namespace commons {
namespace core {

class Performance {

private:
	std::function<void()> callback;

public:


	explicit Performance(std::function<void()> callback) :
			callback(callback) {

	}

	long long repeat(Timer& t, unsigned int aggregate) {
		long long sum = 0;
		for (unsigned int j = 0; j < aggregate; j++) {
			t.start();
			callback();
			t.end();
			sum += t.elapsed_nanos();
		}
		long long took = sum / (long long) aggregate;

		return took;
	}

	void test(unsigned int times, unsigned int aggregate) {
		Timer t;

		for (unsigned int i = 0; i < times; i++) {
			long long took = repeat(t, aggregate);
			Timer::print(took);
		}
	}

	void test_millis(unsigned int times, unsigned int aggregate) {
		Timer t;

		for (unsigned int i = 0; i < times; i++) {
			long long took = repeat(t, aggregate);

			Timer::print_millis(took);
		}
	}

	void test_seconds(unsigned int times, unsigned int aggregate) {
		Timer t;

		for (unsigned int i = 0; i < times; i++) {
			long long took = repeat(t, aggregate);

			Timer::print_seconds(took);
		}
	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_PERFORMANCE_H_ */
