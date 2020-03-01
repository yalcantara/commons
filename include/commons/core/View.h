/*
 * View.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Yaison Alcantara
 */

#ifndef COMMONS_CORE_VIEW_H_
#define COMMONS_CORE_VIEW_H_

#include <stdlib.h>
#include <string>
#include <sstream>
#include <commons/core/Exception.h>

namespace commons {
namespace core {

template<typename T>
class View {
private:
	T* ptr;

	void check_idx(size_t idx) const {
		if (idx >= length) {
			throw Exception(
					"Index out of bounds. The length is: "
							+ std::to_string(length) + ", while the index is: "
							+ std::to_string(idx) + ".");
		}
	}

public:
	const size_t length;

	//Rule of 0 - Single Responsibility
	//=========================================================================
	View() :
			ptr(ptr), length(0) {

	}

	View(T* ptr, size_t length) :
			ptr(ptr), length(length) {
		//do nothing
	}
	//No need for destructor.
	//=========================================================================


	T* data() const {
		return ptr;
	}

	T* data(size_t idx) const {
		check_idx(idx);
		return (ptr + idx);
	}

	//C++11 for-each mechanism
	T* begin() const {
		return ptr;
	}

	T* end() const {
		return (ptr + length);
	}
	//========================

	T& at(size_t idx) const {
		return *data(idx);
	}

	const T& operator[](size_t idx) const {
		return at(idx);
	}

	T& operator[](size_t idx) {
		return at(idx);
	}

	View<T> first(size_t idx) const {
		check_idx(idx);
		return View<T>(ptr, idx);
	}

};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_VIEW_H_ */
