/*
 * Range.cpp
 *
 *  Created on: 27 de jan de 2017
 *      Author: Cassiano
 */

#include "range.h"

#include <iostream>
#include <cmath>

range::range(int last) :
		range(0, last) {
}

range::range(int _first, int _last, int _step) :
		first(_first), last(_last), step(_step), _begin(this, first), _end(this,
				(first) + (step * (ceil(static_cast<float>(last - first) / step)))) {
}

range::~range() {

}

range::iterator::iterator(const range* _rr, int _current) :
		reference(_rr), current(_current) {
}

range::iterator::~iterator() {
}

range::iterator range::begin() {
	return _begin;
}

range::iterator range::end() {
	return _end;
}

range::iterator& range::iterator::operator ++() {
	current = current + reference->step;

	return *this;
}

bool range::iterator::operator ==(const iterator& o) const {
	return (reference == o.reference) && (current == o.current);
}

int& range::iterator::operator *() {
	return current;
}

bool range::iterator::operator !=(const iterator& o) const {
	return !(*this == o);
}

std::size_t range::size() const {
	return static_cast<int>(ceil(static_cast<float>(last - first) / step));
}
