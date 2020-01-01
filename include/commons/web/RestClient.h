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

		uri_builder b;
		b.append(root);
		b.append(target);
		std::string log =  ("GET " + b.to_string());
		println(log.c_str());

		http_response res = client.request(methods::GET, target).get();
		Response ans{res};

		return ans;
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
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_WEB_RESTCLIENT_H_ */
