/*
 * Exception.h
 *
 *  Created on: Mar 17, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_EXCEPTION_H_
#define COMMONS_CORE_EXCEPTION_H_

#include <string>
#include <exception>

using namespace std;
namespace commons {
namespace core {

class Exception: public exception {
protected:
	string msg;

public:
	Exception() :
			msg("") {

	}

	Exception(string msg) :
			msg(msg) {

	}

	Exception(const char* msg) :
			msg(msg) {

	}

	virtual const char* what() const throw () {
		return msg.c_str();
	}

	virtual ~Exception() {

	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_EXCEPTION_H_ */
