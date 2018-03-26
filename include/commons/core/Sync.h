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
	
	Sync(mutex& mtx):Sync(mtx, true){
		
	} 
	
	Sync(mutex& mtx, bool lock) :
			mtx(mtx) {
		if (lock) {
			mtx.lock();
		}
	}

	//no copy constructor
	Sync(const Sync&) = delete;
	
	//no move operator;
	Sync& operator=(const Sync&) = delete;

	void lock() {
		mtx.lock();
	}

	bool try_lock() {
		return mtx.try_lock();
	}

	void unlock() {
		mtx.unlock();
	}

	virtual ~Sync() {
		mtx.unlock();
	}
};

}
}

#endif /* COMMONS_CORE_SYNC_H_ */
