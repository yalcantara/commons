/*
 * JsonArray.h
 *
 *  Created on: Apr 10, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_JSONARRAY_H_
#define COMMONS_WEB_JSONARRAY_H_

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <commons/core/Exception.h>
#include <commons/web/Json.h>
#include <cpprest/json.h>

using namespace web;
using namespace commons::core;

namespace commons {
namespace web {

class JsonArray: public Json {

private:
	json::value delegator;

public:

	JsonArray() {
		delegator = json::value::array();
	}

	JsonArray(json::value& val) {
		if (val.is_object() == false) {
			json::value::value_type type = val.type();
			string t = Json::to_string(type);
			string msg = "The value is not a Json Object type. Got instead: "
					+ t + ".";
			throw Exception(msg);
		}

		delegator = val;
	}

	virtual bool is_object() {
		return false;
	}

	virtual bool is_array() {
		return true;
	}

	void print() {

		utility::string_t str = delegator.serialize();

		const char* json = str.c_str();
		rapidjson::Document d;
		d.Parse(json, str.length());

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		writer.SetIndent('\t', 1);
		d.Accept(writer);

		cout << buffer.GetString() << endl;
	}

};

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_JSONARRAY_H_ */
