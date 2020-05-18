/*
 * lang.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_LANG_CPP_
#define COMMONS_CORE_LANG_CPP_



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <codecvt>
#include <string>
#include <locale>
#include <mutex>
#include <vector>
#include <sstream>

#include <commons/core/Sync.h>

namespace commons {
namespace core {

//mutex for printing
mutex stdout_mutex;

template<typename T>
bool is_primitive() {
	return is_arithmetic < T > ::value || is_same<T, bool>::value;
}

template<typename T>
string to_string2(T* ptr) {

	if (ptr == nullptr) {
		return "null";
	}

	if (is_same<T, bool>::value || is_same<T, const bool>::value) {
		bool casted = *((bool*) ptr);
		if (casted) {
			return "true";
		}
		return "false";
	}

	if (is_integral < T > ::value) {

		if (is_unsigned < T > ::value) {
			return std::to_string(*((unsigned long*) ptr));
		}

		return std::to_string(*((int*) ptr));
	}

	if (is_floating_point < T > ::value) {
		return std::to_string(*((double*) ptr));
	}

	if (is_same<T, size_t>::value || is_same<T, const size_t>::value) {
		return std::to_string(*((size_t*) ptr));
	}

	if (is_same<T, string>::value || is_same<T, const string>::value) {
		return *((string*) ptr);
	}

	if (is_array < T > ::value) {
		return "[array]";
	}

	if (is_pointer < T > ::value) {
		return "[pointer]";
	}

	if (is_pod < T > ::value) {
		return "[pod]";
	}

	if (is_class < T > ::value) {
		return "[class]";
	}

	return "[other]";
}

void print(char c) {
	Sync sync(stdout_mutex);
	fputc(c, stdout);
	fflush(stdout);
}

void print(const char* str) {
	Sync sync(stdout_mutex);
	fputs(str, stdout);
	fflush(stdout);
}

void print(float val) {
	Sync sync(stdout_mutex);
	fprintf(stdout, "%.2f", val);
	fflush(stdout);
}

void print(std::string& str) {
	Sync sync(stdout_mutex);
	const char* ptr = str.c_str();
	fputs(ptr, stdout);
	fflush(stdout);
}

void println() {
	Sync sync(stdout_mutex);
	fputc('\n', stdout);
	fflush(stdout);
}

template<typename T>
void println(T* ptr) {
	Sync sync(stdout_mutex);
	fprintf(stdout, "%p\n", ptr);
	fflush(stdout);
}

void println(char c) {
	Sync sync(stdout_mutex);
	fputc(c, stdout);
	fputc('\n', stdout);
	fflush(stdout);
}

void println(int val) {
	Sync sync(stdout_mutex);
	fprintf(stdout, "%d\n", val);
	fflush(stdout);
}

void println(long int val) {
	Sync sync(stdout_mutex);
	fprintf(stdout, "%ld\n", val);
	fflush(stdout);
}

void println(unsigned long int val) {
	Sync sync(stdout_mutex);
	fprintf(stdout, "%lu\n", val);
	fflush(stdout);
}

void println(float val) {
	Sync sync(stdout_mutex);
	printf("%.2f\n", val);
	fflush(stdout);
}

void println(double val) {
	Sync sync(stdout_mutex);
	printf("%.2f\n", val);
	fflush(stdout);
}

void println(const char* str) {
	Sync sync(stdout_mutex);
	if(str == NULL){
	    fputs("null", stdout);
	}else {
        fputs(str, stdout);
    }
	fputc('\n', stdout);
	fflush(stdout);
}

void println(std::string& str) {
	Sync sync(stdout_mutex);
	const char* ptr = str.c_str();
	fputs(ptr, stdout);
	fputc('\n', stdout);
	fflush(stdout);
}

void println(std::string&& str) {
    Sync sync(stdout_mutex);
    const char* ptr = str.c_str();
    fputs(ptr, stdout);
    fputc('\n', stdout);
    fflush(stdout);
}

void println(u16string& str) {
	Sync sync(stdout_mutex);

	std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> cv;
	std::cout << cv.to_bytes(str) << endl;
	fflush(stdout);
}

void println(string_view& view){
    string txt{view};
    println(txt);
}

void println(string_view&& view){
    string txt{view};
    println(txt);
}

//Other prints
void println(std::vector<string>& vec, bool horizontal) {
    Sync sync(stdout_mutex);

    std::size_t size = vec.size();

	std::cout << "[";
	for (std::size_t i = 0; i < size; i++) {
		std::string& e = vec[i];
        std::cout << e;
		if ((i + 1) < size) {
		    if(horizontal) {
                std::cout << ", ";
            }else{
                std::cout << "," << std::endl;
		    }
		}
	}
    std::cout << "]";
    std::cout << std::endl;
}

void println(std::vector<string>& vec){
    println(vec, true);
}

void print(ostringstream& oss, std::vector<string>& vec, bool horizontal) {


    std::size_t size = vec.size();

    oss << "[";
    for (std::size_t i = 0; i < size; i++) {
        std::string& e = vec[i];
        oss << e;
        if ((i + 1) < size) {
            if(horizontal) {
                oss << ", ";
            }else{
               oss << "," << std::endl;
            }
        }
    }
    oss << "]";
}

string vec_to_string(std::vector<string>& vec, bool horizontal){
    ostringstream oss;
    print(oss, vec, horizontal);
    return oss.str();
}


template<typename t>
void insert_all(std::vector<t>& dest, std::vector<t> src){
	dest.insert(std::end(dest), std::begin(src), std::end(src));
}

}
}

#endif /* COMMONS_CORE_LANG_CPP_ */
