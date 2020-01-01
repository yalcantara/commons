/*
 * Query.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_QUERY_H_
#define COMMONS_WEB_QUERY_H_

#include <commons/core/lang.hpp>
#include <cpprest/uri_builder.h>

using namespace commons::core;
using namespace std;
using namespace web;

namespace commons {
namespace web {

class Query {
private:
	uri_builder _builder;

public:
	Query() {

	}

	void put(const char* name, const char* val) {
		_builder.append_query(name, val);
	}

	void put(const char* name, string val) {
		_builder.append_query(name, val);
	}

	void put(const char* name, unsigned int val) {
		_builder.append_query(name, val);
	}

	uri_builder& builder() {
		return _builder;
	}

	string to_string() {
		return _builder.query();
	}

	void print() {
		string str = to_string();
		println(str);
	}
};

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_QUERY_H_ */
