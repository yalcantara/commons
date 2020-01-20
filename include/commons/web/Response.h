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
#include <cpprest/uri.h>

using namespace commons::core;
using namespace web::http;

namespace commons {
namespace web {

class Response {
private:
	http_response _delegator;
    uri _url;

public:
	Response(){

	}
    Response(http_response& res):_delegator(res){

    }


	Response(http_response& res, uri& url):_delegator(res), _url(url){

	}

	unsigned short status_code(){
		return _delegator.status_code();
	}

	JsonObject body_json_object(){
		json::value val = _delegator.extract_json().get();
		JsonObject ans{val};

		return ans;
	}

	std::string body_utf8(){
		return _delegator.extract_utf8string(true).get();
	}

	std::u16string body_utf16(){
		return _delegator.extract_utf16string(true).get();
	}

	uri url(){
	    return _url;
	}

	void print(){
		std::u16string body = body_utf16();

		println(body);
	}
};

} /* namespace web */
} /* namespace commons */

#endif /* COMMONS_WEB_RESPONSE_H_ */
