/*
 * Lazy.h
 *
 *  Created on: Mar 30, 2018
 *      Author: yaison
 */

#ifndef COMMONS_CORE_LAZY_H_
#define COMMONS_CORE_LAZY_H_

#include <mutex>
#include <functional>
#include <commons/core/Sync.h>

namespace commons {
namespace core {

template<typename T>
class Lazy {

private:
	std::function<T()> retriever;
	T val;
	volatile bool init = false;
	mutex mtx;

public:

	explicit Lazy(T (*retriever)(void)) :
			retriever(retriever) {

	}

	explicit Lazy(std::function<T()> retriever) :
			retriever(retriever) {

	}

	//Copy constructor
	Lazy(const Lazy& other)= delete;
	//Copy assignment
	Lazy<T>& operator=(const Lazy<T>& other) = delete;


	T& get() {
		//Simple locking mechanism.
		//In the future we may use double-checked locking
		Sync sync(mtx);

		if (init) {
			return val;
		}

		val = retriever();
		init = true;

		return val;
	}

	void reset() {
		Sync sync(mtx);
		init = false;
	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_LAZY_H_ */
