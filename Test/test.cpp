﻿#ifdef _MSC_VER
#define _SCL_SECURE_NO_WARNINGS
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // check memory leaks

#include "string_test.h"
#include"cstring_test.h"

int main()
{
	using namespace mystl::test;

	std::cout.sync_with_stdio(false);

	RUN_ALL_TESTS();
	string_test::string_test();
	cstring_test::TestCstring();
#if defined(_MSC_VER) && defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // check memory leaks
}