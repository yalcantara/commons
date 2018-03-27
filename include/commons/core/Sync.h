/*
 * Lock.h
 *
 *  Created on: Mar 17, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_SYNC_H_
#define COMMONS_CORE_SYNC_H_

#include <mutex>

using namespace std;

namespace commons {
namespace core {

class Sync {
private:
	mutex& mtx;

public:

	Sync(mutex& mtx) :
			Sync(mtx, true) {

	}

	Sync(mutex& mtx, bool lock) :
			mtx(mtx) {
		if (lock) {
			mtx.lock();
		}
	}

	//Rule of five
	//=========================================================================
	//1. Copy Constructor
	//No copy constructor allowed
	Sync(const Sync&) = delete;

	//2. Copy Assignment
	//no copy assignment allowed
	Sync& operator=(const Sync& other) = delete;

	//3. Move Constructor
	//No move constructor allowed
	Sync(Sync && other) = delete;

	//4. Move Assignment
	//No move assignment allowed
	Sync& operator=(Sync && other) = delete;

	//5. Destructor
	virtual ~Sync() {
		mtx.unlock();
	}
	//=========================================================================

	void lock() {
		mtx.lock();
	}

	bool try_lock() {
		return mtx.try_lock();
	}

	void unlock() {
		mtx.unlock();
	}

};

}
}

#endif /* COMMONS_CORE_SYNC_H_ */
