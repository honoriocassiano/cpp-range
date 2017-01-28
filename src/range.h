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

template<typename T> struct identity {
	typedef T type;
};

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

		iterator& operator++();

		bool operator==(const iterator& o) const;
		bool operator!=(const iterator& o) const;

		T& operator*();

	private:

		const Range<T>* reference;

		T current;
	};

	iterator begin();
	iterator end();

	std::size_t size() const;

	friend class iterator;

private:

	const T first;
	const T last;
	const T step;

	const iterator _begin;
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
typename Range<T>::iterator Range<T>::begin() {
	return _begin;
}

template<class T>
typename Range<T>::iterator Range<T>::end() {
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
T& Range<T>::iterator::operator *() {
	return current;
}

template<class T>
bool Range<T>::iterator::operator !=(const iterator& o) const {
	return !(*this == o);
}

template<class T>
std::size_t Range<T>::size() const {
	return static_cast<int>(ceil(static_cast<float>(last - first) / step));
}

template<class TF, class TL = TF, class TS = TF>
Range<typename std::common_type<TF, TL, TS>::type> range(TF f, TL l, TS s = 0) {

	return Range<typename std::common_type<TF, TL, TS>::type>(f, l, s);
}

#endif /* RANGE2_H_ */
