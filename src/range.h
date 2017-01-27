/*
 * Range.h
 *
 *  Created on: 27 de jan de 2017
 *      Author: Cassiano
 */

#ifndef RANGE_H_
#define RANGE_H_

#include <cstddef>

class range {
public:

	range(int last);
	range(int first, int last, int step = 1);
	virtual ~range();

	class iterator {

	public:
		iterator(const range* range_reference, int current);
		virtual ~iterator();

		iterator& operator++();

		bool operator==(const iterator& o) const;
		bool operator!=(const iterator& o) const;

		int& operator*();

	private:

		const range* reference;

		int current;
	};

	iterator begin();
	iterator end();

	std::size_t size() const;

	friend class iterator;

private:

	const int first;
	const int last;
	const int step;

	const iterator _begin;
	const iterator _end;
};

#endif /* RANGE_H_ */
