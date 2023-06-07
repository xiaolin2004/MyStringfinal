#pragma once
#ifndef MYSTL_CSTRING_TEST_H_
#define MYSTL_CSTRING_TEST_H_
#include "../MyString/mycstring.h"
namespace mystl {
	namespace test
	{
		namespace cstring_test
		{
			void TestCstring()
			{
				char str1[20] = "Hello";
				char str2[20] = "World";
				char str3[20];
				char* ptr;
				int result;

				// memcpy
				memcpy(str3, str1, sizeof(str1));
				printf("memcpy: %s\n", str3);

				// memmove
				char str4[] = "memmove can be very useful......";
				memmove(str4 + 20, str4 + 15, 11);
				printf("memmove: %s\n", str4);

				// strcpy
				strcpy(str3, str2);
				printf("strcpy: %s\n", str3);

				// strncpy
				strncpy(str3, str1, 3);
				str3[3] = '\0';
				printf("strncpy: %s\n", str3);

				// strcat
				strcat(str1, str2);
				printf("strcat: %s\n", str1);

				// strncat
				strncat(str1, str2, 3);
				printf("strncat: %s\n", str1);

				// memcmp
				result = memcmp(str1, str2, sizeof(str1));
				printf("memcmp: %d\n", result);

				// strcmp
				result = strcmp(str1, str2);
				printf("strcmp: %d\n", result);

				// strncmp
				result = strncmp(str1, str2, 3);
				printf("strncmp: %d\n", result);

				// memchr
				char str[] = "Hello, World!";
				char* ptrv = (char*)memchr(str, 'W', sizeof(str));
				if (ptrv != NULL) {
					printf("%s\n", ptrv);
				}
				else {
					printf("Not found\n");
				}

				// strchr
				ptr = strchr(str1, 'l');
				if (ptr != NULL) {
					printf("strchr: %c\n", *ptr);
				}
				else {
					printf("strchr: not found\n");
				}

				////strcoll

				//char string2[] = "ABC";
				//int res;
				//res = strcoll(string1, string2);
				//if (res > 0)
				//    printf("strcoll: string1 is greater than string2");
				//else if (res < 0)
				//    printf("strcoll: string2 is greater than string1");
				//else
				//    printf("strcoll: string1 is equal to string2");

				//strxfrm
				char string1[] = "abc";
				char dest[20];
				int len;
				len = strxfrm(dest, string1, sizeof(dest));
				printf("\nstrxfrm: The length of the transformed string is %d and the transformed string is %s.", len, dest);

				//strcspn

				const char s[] = "Programming in C language";
				const char r[] = "aeiou";
				len = strcspn(s, r);
				printf("\nstrcspn: The first vowel in the given string is at position %d.", len + 1);

				//strpbrk

				char* p;
				p = strpbrk(s, r);
				if (p)
					printf("\nstrpbrk: The first vowel in the given string is %c.", *p);
				else
					printf("\nstrpbrk: No vowels in the given string.");

				// strrchr
				ptr = strrchr(str1, 'l');
				if (ptr != NULL) {
					printf("\nstrrchr: %c\n", *ptr);
				}
				else {
					printf("\nstrrchr: not found\n");
				}

				// strspn

				const char accept[] = "0123456789";
				len = strspn(s, accept);
				printf("\nstrspn: The initial segment of s that consists entirely of characters from accept has length %d.", len);

				// strstr
				ptr = strstr(str1, "orl");
				if (ptr != NULL) {
					printf("\nstrstr: %s\n", ptr);
				}
				else {
					printf("\nstrstr: not found\n");
				}

				// strtok
				char input[100] = "A bird came down the walk";
				ptr = strtok(input, " ");
				while (ptr != NULL) {
					printf("\nstrtok: %s", ptr);
					ptr = strtok(NULL, " ");
				}

				// memset
				memset(str3, '*', sizeof(str3));
				printf("\nmemset: %s\n", str3);

				// strerror
				fprintf(stderr, "\nstrerror:%s", strerror(2));

				// strlen
				result = strlen(str1);
				printf("\nstrlen:%d\n", result);

				std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;

				//×ª»»º¯Êý
				char strpl[] = "12345";
				int i = stoi(strpl);
				long l = stol(strpl);
				unsigned long ul = stoul(strpl);
				long long ll = stoll(strpl);
				unsigned long long ull = stoull(strpl);
				float f = stof(strpl);
				double d = stod(strpl);
				long double ld = stolda(strpl);

				std::cout << "stoi: " << i << std::endl;
				std::cout << "stol: " << l << std::endl;
				std::cout << "stoul: " << ul << std::endl;
				std::cout << "stoll: " << ll << std::endl;
				std::cout << "stoull: " << ull << std::endl;
				std::cout << "stof: " << f << std::endl;
				std::cout << "stod: " << d << std::endl;
				std::cout << "stold: " << ld << std::endl;

				int num = 12345;
				std::string strpll = to_string(num);
				std::cout << "to_string: " << strpll << std::endl;
			}
		}
	}
}
#endif