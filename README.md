# Cpp-Range

A small range library for C++11.

Usage:

```cpp
#include <iostream>

#include "range.h"

int main(void) {

	for (auto& n : range(1, 5)) {
		std::cout << n << " ";
	}

	std::cout << std::endl;

	return 0;
}
```

Output:

```
1 2 3 4 
```

More examples:

```cpp
#include "range.h"

int main(void) {

	auto r1 = range(5);					// 0 1 2 3 4
	auto r2 = range(1, 6);				// 1 2 3 4 5
	auto r3 = range(1, 6, 2);			// 1 3 5
	auto r4 = range(1, -1.5, -0.5);		// 1.0 0.5 0.0 -0.5 -1.0
	
	return 0;
}
```
