/*
 * Range.h
 *
 *  Created on: 27 de jan de 2017
 *      Author: Cassiano
 */

#ifndef RANGE_H_
#define RANGE_H_

#include <cstddef>
#include <cmath>
#include <type_traits>
#include <vector>
#include <iostream>

template<typename T> struct identity {
	typedef T type;
};

template <typename T>
class Range;

template <typename T>
std::ostream& operator<< (std::ostream &, const Range<T>&);

template<class T>
class Range {
public:

	Range(const typename identity<T>::type& last);
	Range(const typename identity<T>::type& first,
			const typename identity<T>::type& last,
			const typename identity<T>::type& step = 1);
	virtual ~Range();

	class iterator {

	public:
		iterator(const Range<T>* range_reference, T current);
		virtual ~iterator();

		/**
		 * Prefix increment operator.
		 *
		 * @return iterator with next value in range
		 */
		iterator& operator++();

		/**
		 * Postfix increment operator. This method create a copy of object, go to next value in range and return the copy.
		 *
		 * @return a copy of the object
		 */
		iterator& operator++(int);

		/**
		 * Compare two iterators.
		 *
		 * @return if operators are equal
		 */
		bool operator==(const iterator& o) const;

		/**
		 * Compare two iterators.
		 *
		 * @return if operators are different
		 */
		bool operator!=(const iterator& o) const;

		/**
		 * Pointer operator.
		 *
		 * @return current value of iterator
		 */
		T& operator*();

	private:

		/**
		 * Reference to original range object
		 */
		const Range<T>* reference;

		/**
		 * Current value
		 */
		T current;
	};

	/**
	 * Begin of the range.
	 *
	 * @return iterator with first vale of range
	 */
	iterator begin() const;

	/**
	 * End of the range.
	 *
	 * @return iterator with last vale of range
	 */
	iterator end() const;

	/**
	 * Convert range to a std::vector.
	 *
	 * @return vector containing all elements in the range
	 */
	std::vector<T> to_vector() const;

	friend std::ostream& operator<< <T>(std::ostream& os, const Range<T>& range);

	/**
	 * Size of range.
	 *
	 * @return size of range
	 */
	std::size_t size() const;

	friend class iterator;

private:

	/**
	 * First element in range.
	 */
	const T first;

	/**
	 * Last element in range.
	 */
	const T last;

	/**
	 * Size of steps in range
	 */
	const T step;

	/**
	 * Iterator to begin of range.
	 */
	const iterator _begin;

	/**
	 * Iterator to end of range.
	 */
	const iterator _end;
};

template<class T>
Range<T>::Range(const typename identity<T>::type& last) :
		Range(0, last) {
}

template<class T>
Range<T>::Range(const typename identity<T>::type& _first,
		const typename identity<T>::type& _last,
		const typename identity<T>::type& _step) :
		first(_first), last(_last), step(_step), _begin(this, first), _end(this,
				(first)
						+ (step
								* (ceil(static_cast<float>(last - first) / step)))) {
}

template<class T>
Range<T>::~Range() {

}

template<class T>
Range<T>::iterator::iterator(const Range<T>* _rr, T _current) :
		reference(_rr), current(_current) {
}

template<class T>
Range<T>::iterator::~iterator() {
}

template<class T>
typename Range<T>::iterator Range<T>::begin() const {
	return _begin;
}

template<class T>
typename Range<T>::iterator Range<T>::end() const {
	return _end;
}

template<class T>
typename Range<T>::iterator& Range<T>::iterator::operator ++() {
	current = current + reference->step;

	return *this;
}

template<class T>
bool Range<T>::iterator::operator ==(const iterator& o) const {
	return (reference == o.reference) && (current == o.current);
}

template<class T>
typename Range<T>::iterator& Range<T>::iterator::operator ++(int) {
	auto it = *this;
	++(*this);

	return it;
}

template<class T>
T& Range<T>::iterator::operator *() {
	return current;
}

template<class T>
bool Range<T>::iterator::operator !=(const iterator& o) const {
	return !(*this == o);
}

template<class T>
std::vector<T> Range<T>::to_vector() const {
	std::vector<T> e(size());

	int i = 0;
	for (auto v : *this) {
		e[i] = v;

		++i;
	}

	return e;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Range<T>& range) {
	for(auto& n : range) {
		os << n << " ";
	}

	return os;
}

template<class T>
std::size_t Range<T>::size() const {
	return static_cast<int>(ceil(static_cast<float>(last - first) / step));
}

template<class TF, class TL = TF,
		class TS = typename std::common_type<TF, TL>::type>
Range<typename std::common_type<TF, TL, TS>::type> range(TF f, TL l, TS s = 0) {

	return Range<typename std::common_type<TF, TL, TS>::type>(f, l, s);
}

#endif /* RANGE2_H_ */
