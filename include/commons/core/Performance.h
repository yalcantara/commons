/*
 * Performance.h
 *
 *  Created on: Mar 30, 2018
 *      Author: yaison
 */

#ifndef COMMONS_CORE_PERFORMANCE_H_
#define COMMONS_CORE_PERFORMANCE_H_

#include <commons/core/Timer.h>

namespace commons {
namespace core {

class Performance {
private:
	void (*callback)(void);

public:
	Performance(void (*callback)(void)) :
			callback(callback) {

	}

	void run(){

	}

	void test(unsigned int times, unsigned int aggregate) {
		Timer t;

		for (unsigned int i = 0; i < times; i++) {
			long long sum = 0;
			for (unsigned int j = 0; j < aggregate; j++) {
				t.start();
				callback();
				t.end();
				sum += t.elapsed_nanos();
			}
			long long took = sum / (long long) aggregate;
			Timer::print(took);
		}
	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_PERFORMANCE_H_ */
