/*
 * Json.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_JSON_H_
#define COMMONS_WEB_JSON_H_

#include <string>
#include <cpprest/json.h>

using namespace std;
using namespace web;

namespace commons {
namespace web {

class Json {
public:
	Json() {

	}



	static string to_string(json::value::value_type type) {
		switch (type) {
			case json::value::value_type::Number:
				return "Number";
			case json::value::value_type::Boolean:
				return "Boolean";
			case json::value::value_type::String:
				return "String";
			case json::value::value_type::Object:
				return "Object";
			case json::value::value_type::Array:
				return "Array";
			case json::value::value_type::Null:
				return "Null";
			default:
				return "Other";
		}

	}

	virtual bool is_object() = 0;
	virtual bool is_array() = 0;

};

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_JSON_H_ */
