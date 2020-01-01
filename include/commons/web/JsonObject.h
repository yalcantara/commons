/*
 * JsonObject.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_JSONOBJECT_H_
#define COMMONS_WEB_JSONOBJECT_H_

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <commons/core/Exception.h>
#include <commons/web/Json.h>
#include <commons/web/JsonArray.h>
#include <cpprest/json.h>

using namespace web;
using namespace commons::core;

namespace commons {
namespace web {

class JsonObject: public Json {

private:
	json::value delegator;

	json::value& get(const char* key) {
		return delegator[key];
	}

public:
	JsonObject() {
		delegator = json::value::object(true);
	}

	JsonObject(json::value& val) {
		if (val.is_object() == false) {
			json::value::value_type type = val.type();
			string t = Json::to_string(type);
			string msg = "The value is not a Json Object type. Got instead: "
					+ t + ".";
			throw Exception(msg);
		}

		delegator = val;
	}

	void put(string& key, double val) {
		json::value v { val };
		delegator[key] = v;
	}

	void put(const char* key, const char* val) {
		json::value v { val };
		delegator[key] = v;
	}

	void put(string& key, const char* val) {
		put(key.c_str(), val);
	}

	void put(string& key, string& val) {
		json::value v { val };
		delegator[key] = v;
	}

	void put(string& key, bool val) {
		json::value v { val };
		delegator[key] = v;
	}

	void put(string& key, JsonObject val) {
		json::value v { val.delegator };
		delegator[key] = v;
	}

	const string& get_string(string& key) {
		return get_string(key.c_str());
	}

	const string& get_string(const char* key) {
		json::value v = get(key);

		if (v.is_string()) {
			return v.as_string();
		}

		string msg;
		msg.append("The value for the key '");
		msg.append(key);
		msg.append("' is not a string.");
		throw Exception(msg);
	}

	double get_number(const char* key) {
		json::value v = get(key);

		if (v.is_number()) {
			return v.as_number().to_double();
		}

		string msg;
		msg.append("The value for the key '");
		msg.append(key);
		msg.append("' is not a string.");
		throw Exception(msg);
	}

	JsonArray get_array(const char* key) {
		json::value& v = get(key);

		if (v.is_array()) {
			JsonArray arr{v};
			return arr;
		}

		string msg;
		msg.append("The value for the key '");
		msg.append(key);
		msg.append("' is not an Array.");
		throw Exception(msg);
	}

	virtual bool is_object() {
		return true;
	}

	virtual bool is_array() {
		return false;
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
}
;

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_JSONOBJECT_H_ */
