//============================================================================
// Name        : Range.cpp
// Author      : Cassiano
// Version     : 0.0.1
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <string>

#include "range.h"

int main(void) {

	using namespace r2;

	auto a = range('a', 'z'+1, 1);

	for (auto& b : a) {
		std::cout << (char)b << "\n";
	}

	return EXIT_SUCCESS;
}
