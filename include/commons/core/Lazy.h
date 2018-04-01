/*
 * Lazy.h
 *
 *  Created on: Mar 30, 2018
 *      Author: yaison
 */

#ifndef COMMONS_CORE_LAZY_H_
#define COMMONS_CORE_LAZY_H_

#include <mutex>
#include <functional>
#include <commons/core/Exception.h>
#include <commons/core/Sync.h>

namespace commons {
namespace core {

template<typename T>
class Lazy {

private:
	T val;
	mutex mtx;
	std::function<T()> retriever = nullptr;
	volatile bool init = false;

	void drop() {
		Sync sync(mtx);
		init = false;
		retriever = nullptr;
	}

public:

	Lazy() {

	}

	explicit Lazy(T (*retriever)(void)) :
			retriever(retriever) {
	}

	explicit Lazy(std::function<T()> retriever) :
			retriever(retriever) {
	}

	//Rule of five
	//=========================================================================
	//1. Copy Constructor
	Lazy(const Lazy& other) noexcept {
		this->init = false;
		this->retriever = other.retriever;
	}

	//2. Copy Assignment
	Lazy<T>& operator=(const Lazy<T>& other) noexcept {

		//just set init=false
		//and copy the retriever
		this->init = false;
		this->retriever = other.retriever;

		return *this;
	}

	//3. Move Constructor
	//noexcept allows std containers to use it.
	Lazy(Lazy<T> && other) noexcept {

		this->retriever = std::move(other.retriever);
		this->val = std::move(other.val);
		this->init = std::move(other.init);
		this->mtx = std::move(other.mtx);
		other.drop();
	}

	//4. Move Assignment
	//noexcept allows std containers to use it.
	Lazy<T>& operator=(Lazy<T> && other) noexcept {
		if (this == &other) {
			return *this;
		}

		this->retriever = std::move(other.retriever);
		this->val = std::move(other.val);
		this->init = std::move(other.init);
		this->mtx = std::move(other.mtx);
		other.drop();

		return *this;
	}

	//5. Destructor
	virtual ~Lazy() noexcept {
		//do nothing
		//automatic memory handled
	}
	//=========================================================================


	T& get() {
		//Simple locking mechanism.
		//In the future we may use double-checked locking
		Sync sync(mtx);

		if (init) {
			return val;
		}

		if (retriever == nullptr) {
			throw Exception("The retriever function is null.");
		}
		val = retriever();
		init = true;

		return val;
	}

	void reset() {
		Sync sync(mtx);
		init = false;
	}

	bool is_init(){
		Sync sync(mtx);
		return init;
	}
};

} /* namespace core */
} /* namespace commons */

#endif /* COMMONS_CORE_LAZY_H_ */
