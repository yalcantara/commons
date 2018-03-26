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

	void release() {
		if (ptr) {
			delete[] ptr;
		}
	}

public:


	Block() noexcept {
		this->length = 0;
		this->ptr = nullptr;
	}

	Block(size_t length) noexcept {

		this->length = length;
		this->ptr = new T[length]();
	}

	//Rule of five (Constructors, Move Assignment & Destructor)
	//=========================================================================
	//1. Copy Constructor
	//We don't allow Block to be copied.
	Block(const Block<T>& other) = delete;

	//2. Copy Assignment
	//We don't allow Block to be copied.
	Block<T>& operator=(const Block<T>& other) = delete;

	//3. Move Constructor
	//noexcept allows std containers to use it.
	Block(Block<T> && other) noexcept {

		this->length = other.length;
		this->ptr = other.ptr;
		other.drop();
	}

	//4. Move Assignment
	//noexcept allows std containers to use it.
	Block<T>& operator=(Block<T> && other) noexcept {
		if (this == &other) {
			return *this;
		}

		this->length = other.length;
		this->ptr = other.ptr;
		other.drop();

		return *this;
	}

	//5. Destructor
	virtual ~Block() noexcept {
		release();
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
		check_idx(idx);
		return ptr[idx];
	}

	T& operator[](size_t idx) {
		return ptr[idx];
	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_BLOCK_H_ */
