//============================================================================
// Name        : Range.cpp
// Author      : Cassiano
// Version     : 0.0.1
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>

#include "range.h"

int main(void) {

	auto a = range('a', 'z' + 1, 1);

	auto c = a.to_vector();

//	std::cout << std::boolalpha << std::is_same< decltype(range(1, 1.0, 1)) , decltype(range(1, 1.0, 1))>::value
//			<< std::endl;

//	for (auto& b : a) {
	for (auto& b : c) {
		std::cout << (char)b << " ";
	}

	std::cout << std::endl;

	return 0;
}

