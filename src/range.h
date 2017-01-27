/*
 * Range.h
 *
 *  Created on: 27 de jan de 2017
 *      Author: Cassiano
 */

#ifndef RANGE2_H_
#define RANGE2_H_

#include <cstddef>
#include <cmath>
#include <type_traits>

namespace r2 {

using namespace std;

template<typename T> struct identity {
	typedef T type;
};

template<class TF, class TL = TF, class TS = TF>
class Range {
public:

	typedef typename std::common_type<TF, TL, TS>::type common;

	Range(const typename identity<TL>::type& last);
	Range(const typename identity<TF>::type& first,
			const typename identity<TL>::type& last,
			const typename identity<TS>::type& step = 1);
	virtual ~Range();

	class iterator {

	public:
		iterator(const Range<TF, TL, TS>* range_reference, common current);
		virtual ~iterator();

		iterator& operator++();

		bool operator==(const iterator& o) const;
		bool operator!=(const iterator& o) const;

		common& operator*();

	private:

		const Range<TF, TL, TS>* reference;

		common current;
	};

	iterator begin();
	iterator end();

	std::size_t size() const;

	friend class iterator;

private:

	const common first;
	const common last;
	const common step;

	const iterator _begin;
	const iterator _end;
};

template<class TF, class TL, class TS>
Range<TF, TL, TS>::Range(const typename identity<TL>::type& last) :
		Range(0, last) {
}

template<class TF, class TL, class TS>
Range<TF, TL, TS>::Range(const typename identity<TF>::type& _first,
		const typename identity<TL>::type& _last,
		const typename identity<TS>::type& _step) :
		first(_first), last(_last), step(_step), _begin(this, first), _end(this,
				(first)
						+ (step
								* (ceil(static_cast<float>(last - first) / step)))) {
}

template<class TF, class TL, class TS>
Range<TF, TL, TS>::~Range() {

}

template<class TF, class TL, class TS>
Range<TF, TL, TS>::iterator::iterator(const Range<TF, TL, TS>* _rr,
		common _current) :
		reference(_rr), current(_current) {
}

template<class TF, class TL, class TS>
Range<TF, TL, TS>::iterator::~iterator() {
}

template<class TF, class TL, class TS>
typename Range<TF, TL, TS>::iterator Range<TF, TL, TS>::begin() {
	return _begin;
}

template<class TF, class TL, class TS>
typename Range<TF, TL, TS>::iterator Range<TF, TL, TS>::end() {
	return _end;
}

template<class TF, class TL, class TS>
typename Range<TF, TL, TS>::iterator& Range<TF, TL, TS>::iterator::operator ++() {
	current = current + reference->step;

	return *this;
}

template<class TF, class TL, class TS>
bool Range<TF, TL, TS>::iterator::operator ==(const iterator& o) const {
	return (reference == o.reference) && (current == o.current);
}

template<class TF, class TL, class TS>
typename std::common_type<TF, TL, TS>::type& Range<TF, TL, TS>::iterator::operator *() {
	return current;
}

template<class TF, class TL, class TS>
bool Range<TF, TL, TS>::iterator::operator !=(const iterator& o) const {
	return !(*this == o);
}

template<class TF, class TL, class TS>
std::size_t Range<TF, TL, TS>::size() const {
	return static_cast<int>(ceil(static_cast<float>(last - first) / step));
}

template<class TF, class TL = TF, class TS = TF>
Range<TF, TL, TS> range(TF f, TL l, TS s = 0) {
	return Range<TF, TL, TS>(f, l, s);
}

}

#endif /* RANGE2_H_ */
