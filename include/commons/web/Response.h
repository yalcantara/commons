/*
 * Response.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_RESPONSE_H_
#define COMMONS_WEB_RESPONSE_H_

#include <commons/core/Lazy.h>
#include <commons/core/lang.hpp>
#include <commons/web/JsonObject.h>
#include <cpprest/http_client.h>

using namespace commons::core;
using namespace web::http;

namespace commons {
namespace web {

class Response {
private:
	http_response delegator;


public:
	Response(){

	}

	Response(http_response& res):delegator(res){

	}

	unsigned short status_code(){
		return delegator.status_code();
	}

	JsonObject body_json_object(){
		json::value val = delegator.extract_json().get();
		JsonObject ans{val};

		return ans;
	}

	std::string body_utf8string(){
		return delegator.extract_utf8string(true).get();
	}

	std::u16string body_string(){
		return delegator.extract_utf16string(true).get();
	}

	void print(){
		std::u16string body = body_string();

		println(body);
	}
};

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_RESPONSE_H_ */
