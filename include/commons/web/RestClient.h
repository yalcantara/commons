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
#include <cpprest/uri.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace commons {
namespace web {

class RestClient {
private:
	string root;
    http_client client;

    string fullp(const char* path, Query& query){
        uri_builder b;
        b.append_path(path);
        string q = query.to_string();
        b.append_query(q);

        string target = b.to_string();
        return target;
    }

public:

	RestClient(const char* root) :root(root), client(root) {
	}


	Response get(const char* path_query_fragment) {

        //construct the url first, before doing any network call.
        uri_builder b{root};
        b.append(path_query_fragment);
        uri url = b.to_uri();

		http_response res = client.request(methods::GET, path_query_fragment).get();

		Response ans{res, url};

		return ans;
	}

	Response get(std::string& path_query_fragment) {
		const char* str = path_query_fragment.c_str();
		return get(str);
	}

	Response get(const char* path, Query& query) {
		string target = fullp(path, query);
		return get(target);
	}

    Response get2xx(const char* path_query_fragment){
        Response r = get(path_query_fragment);
        unsigned short status = r.status_code();
        if(status < 200 || status >= 300){
            string url = r.url().to_string();
            string msg = "Response is not 2xx. Got: " + std::to_string(status) +", for url: " + url +".";
            throw Exception(msg);
        }
        return r;
    }

    Response get2xx(const char* path, Query& q){
	    string target = fullp(path, q);
	    return get2xx(target.c_str());
	}

    string wget(const char* path, Query& q){
        return get2xx(path, q).body_utf8();
    }

    string wget(const char* path){
        return get2xx(path).body_utf8();
    }

    string wget(string& path){
        return wget(path.c_str());
    }

    u16string wget_utf16(const char* path){
        return get2xx(path).body_utf16();
    }

    u16string wget_utf16( const char* path, Query& q){
        return get2xx(path, q).body_utf16();
    }
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_WEB_RESTCLIENT_H_ */
