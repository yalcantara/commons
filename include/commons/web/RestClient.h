/*
 * RestClient.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_WEB_RESTCLIENT_H_
#define COMMONS_WEB_RESTCLIENT_H_

#include <commons/web/Response.h>
#include <commons/web/Query.h>
#include <cpprest/http_client.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace commons {
namespace web {

class RestClient {
private:
	string root;

public:
	RestClient() {

	}

	RestClient(const char* root) :
			root(root) {
	}

	Response get(const char* target) {

		http_client client{root};


		http_response res = client.request(methods::GET, target).get();
		return Response(res);
	}

	Response get(string& target) {
		const char* str = target.c_str();
		return get(str);
	}

	Response get(const char* path, Query& query) {
		uri_builder b;
		b.append_path(path);
		string q = query.to_string();
		b.append_query(q);

		string target = b.to_string();
		return get(target);
	}

	void get_foo(){

	}

};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_WEB_RESTCLIENT_H_ */
