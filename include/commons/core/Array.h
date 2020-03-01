/*
 * Array.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_ARRAY_H_
#define COMMONS_CORE_ARRAY_H_

#include <stdlib.h>
#include <string>
#include <sstream>
#include <commons/core/Exception.h>
#include <commons/core/lang.hpp>
#include <commons/core/View.h>

namespace commons {
namespace core {

template<typename T>
class Array {

private:
	T* ptr = nullptr;
	size_t length;

	void check_idx(size_t idx) const {
		if (idx >= length) {
			throw Exception(
					"Array index out of bounds. The length is: "
							+ std::to_string(length) + ", while the index is: "
							+ std::to_string(idx) + ".");
		}
	}

	void drop() {
		ptr = nullptr;
		length = 0;
	}

	void free() {
		if (ptr) {
			delete[] ptr;
			drop();
		}
	}

public:

	Array() noexcept :
			length(0) {
	}

	Array(size_t length)  {
		this->ptr = new T[length]();
		this->length = length;
	}

	//Rule of five
	//=========================================================================
	//1. Copy Constructor
	Array(const Array<T>& other) noexcept {

		this->ptr = new T[other.length];
		this->length = other.length;
		std::copy(other.begin(), other.end(), ptr);
	}

	//2. Copy Assignment
	Array<T>& operator=(const Array<T>& other) noexcept {

		//2 cases
		if (this->length == other.length) {
			//a. Same length, just copy
			std::copy(other.begin(), other.end(), ptr);
		} else {
			//b. Different length, we need to free, allocate, then copy
			free();
			this->ptr = new T[other.length];
			this->length = other.length;
			std::copy(other.begin(), other.end(), ptr);
		}

		return *this;
	}

	//3. Move Constructor
	//noexcept allows std containers to use it.
	Array(Array<T> && other) noexcept {

		this->ptr = other.ptr;
		this->length = other.length;
		other.drop();
	}

	//4. Move Assignment
	//noexcept allows std containers to use it.
	Array<T>& operator=(Array<T> && other) noexcept {
		if (this == &other) {
			return *this;
		}

		this->free();

		this->ptr = other.ptr;
		this->length = other.length;
		other.drop();

		return *this;
	}

	//5. Destructor
	virtual ~Array() noexcept {
		free();
	}
	//=========================================================================

	size_t size() const {
		return length;
	}

	View<T> view() {
		return View<T>(ptr, length);
	}

	T* data() const {
		return ptr;
	}

	T* data(size_t idx) const {
		check_idx(idx);
		return (ptr + idx);
	}

	T& at(size_t idx) const {
		return *data(idx);
	}

	//C++11 for-each mechanism
	T* begin() const {
		return ptr;
	}

	T* end() const {
		return (ptr + length);
	}
	//========================

	const T& operator[](size_t idx) const {
		return at(idx);
	}

	T& operator[](size_t idx) {
		return at(idx);
	}

	void print() {
		ostringstream os;

		os << "Array (";
		os << to_string(length);
		os << ")";

		os << " [";

		for (size_t i = 0; i < length; i++) {

			T* p = data(i);

			if (is_same<T, char>::value || is_same<T, const char>::value) {
				char casted = *((char*) p);
				if (casted == '\0') {
					os << "''";
				} else {
					os << casted;
				}
			} else if (is_same<T, string>::value
					|| is_same<T, const string>::value) {
				os << '"';
				os << to_string2(p);
				os << '"';
			} else {
				os << to_string2(p);
			}

			if (i + 1 < length) {
				os << ", ";
			}
		}

		os << "]";

		string str = os.str();
		println(str);
	}

};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_ARRAY_H_ */
