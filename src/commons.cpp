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


using namespace commons::core;



class P {

public:
	int edad;
	char sex;

	P() {
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




void send2(Block<float>& r) {

}




int main() {


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




	return 0;
}



