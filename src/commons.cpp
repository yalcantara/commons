//============================================================================
// Name        : commons.cpp
// Author      : Yaison Alcantara
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdlib.h>
#include <vector>
#include <string>
#include <thread>
#include <commons/core/Block.h>
#include <commons/core/lang.hpp>
#include <commons/core/Array.h>
#include <commons/core/Timer.h>
#include <commons/core/Performance.h>
#include <commons/core/Lazy.h>
#include <commons/web/Query.h>
#include <commons/web/RestClient.h>
#include <boost/asio.hpp>

#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>


using namespace boost::asio;
using namespace commons::web;
using namespace commons::core;

class P {

public:
	int edad;
	char sex;

	P() {
		edad = 9;
		sex = 'f';
		println("Constructor called");
	}

	~P() {
		cout << "destroyed" << endl;
	}
};

void call(View<float> read) {

}

Block<float> send() {
	Block<float> r(4);

	Block<float> e(5);

	return e;
}

void send2(Block<int>& r) {

}

void send2(Block<float>& r) {

}

void test2() {
	Block<float> A(10);

	Block<float> pop = send();

	send2(pop);

	call(A.view());

	Array<char> a(10);
	Array<int> b(20);

	Array<string> c(10);
	Array<vector<float>> d(10);
	Array<bool> e(10);

	Block<int> x(10);

	for (size_t i = 0; i < e.size(); i++) {
		e[i] = true;
	}

	for (size_t i = 0; i < c.size(); i++) {
		c[i] = "Pop " + std::to_string(i);
	}

	a.print();
	b.print();
	c.print();
	d.print();
	e.print();
}

Block<int> p;

Block<int> ans() {

	Block<int> r(3);

	r[0] = 1;
	r[1] = 2;
	r[2] = 3;

	return r;

}

Array<P> ans2() {

	Array<P> arr(3);

	arr[0].edad = 4;

	println(&arr[0]);

	return arr;

}

void main3() {
	for (int i = 0; i < 5; i++) {
		Timer t;

		t.start();
		Array<P> a { 10 };
		t.end();

		t.print();
		t.print_seconds();
		println(&a[0]);
	}
}

void run() {

	int r = (rand() / (double) RAND_MAX) * 5000;

	Timer t;

	long long took;
	do {
		t.end();
		took = t.elapsed_micros();
	} while (took < r);
}

P call() {
	P p;
	return p;
}

int main() {

	Query q;
	q.put("method", "flickr.photos.getRecent");
	q.put("api_key", "9ed5f887daf515511a3d64612498e9d0");
	q.put("format", "json");
	q.put("nojsoncallback", 1);
	q.put("per_page", "10");
	q.put("page", 1);

	q.print();




	RestClient client("https://api.flickr.com");

	Response r = client.get("/services/rest", q);

	JsonObject json = r.body_json_object();

	json.print();

	return 0;
}

