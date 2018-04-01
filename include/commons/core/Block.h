/*
 * Block.h
 *
 *  Created on: Mar 17, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_BLOCK_H_
#define COMMONS_CORE_BLOCK_H_

#include <stdlib.h>
#include <string>
#include <sstream>
#include <utility>
#include <commons/core/lang.hpp>
#include <commons/core/Exception.h>
#include <commons/core/View.h>

namespace commons {
namespace core {

template<typename T>
class Block {
private:
	T* ptr = nullptr;
	size_t length;

	void check_idx(size_t idx) const {
		if (idx >= length) {
			throw Exception(
					"Block index out of bounds. The length is: "
							+ to_string(length) + ", while the index is: "
							+ to_string(idx) + ".");
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

	Block() noexcept {
		this->ptr = nullptr;
		this->length = 0;
	}

	Block(size_t length) {

		this->ptr = new T[length]();
		this->length = length;
	}

	Block(size_t length, bool init) {

		if (init) {
			this->ptr = new T[length]();
		} else {
			this->ptr = new T[length];
		}
		this->length = length;
	}

	//Rule of five
	//=========================================================================
	//1. Copy Constructor
	//We don't allow Block to be copied.
	Block(const Block<T>& other) = delete;

	//2. Copy Assignment
	//We don't allow Block to be copied.
	Block<T>& operator=(const Block<T>& other) = delete;

	//3. Move Constructor
	Block(Block<T> && other) noexcept {

		this->ptr = other.ptr;
		this->length = other.length;
		other.drop();
	}

	//4. Move Assignment
	//We don't allow Block to be moved.
	Block<T>& operator=(Block<T> && other) = delete;

	//5. Destructor
	virtual ~Block() noexcept {
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

		os << "Block (";
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

#endif /* COMMONS_CORE_BLOCK_H_ */
