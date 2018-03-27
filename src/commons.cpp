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
#include <commons/core/Block.h>
#include <commons/core/lang.hpp>
#include <commons/core/Array.h>


#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>


using namespace commons::core;

class P {

public:
	int edad;
	char sex;

	P() {
		cout<< "Constructor"<<endl;
		edad = 9;
		sex = 'f';
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

Array<P> ans2(){

	Array<P> arr(3);

	arr[0].edad = 4;

	println(&arr[0]);


	return arr;

}

mutex m;

int main() {


	Array<P> a{10};


	a = ans2();

	println(&a[0]);



	return 0;
}

