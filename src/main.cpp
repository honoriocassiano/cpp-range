//============================================================================
// Name        : Range.cpp
// Author      : Cassiano
// Version     : 0.0.1
// Copyright   :
// Description :
//============================================================================

#include <iostream>

#include "range.h"

int main(void) {

	for (auto& b : range(0, 11, 2)) {
		std::cout << b << "\n";
	}

	return EXIT_SUCCESS;
}
