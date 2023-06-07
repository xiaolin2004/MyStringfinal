#pragma once
#ifndef MY_CSTRING_H_
#define MY_CSTRING_H_

#include <cassert>
#include <iostream>
#include <cstddef>

namespace mystl
{
	void* memcpy(void* dest, const void* src, size_t n) { // �ڽ����ڴ濽��֮ǰ����Ҫ��֤Ŀ���ڴ�Ŀռ��㹻����˿���ʹ��assert����ж����ж�
		assert(dest != nullptr && src != nullptr);
		// ����ʹ��һ��forѭ�������ֽڵؽ�Դ�ڴ��е����ݸ��Ƶ�Ŀ���ڴ���
		for (size_t i = 0; i < n; ++i) {
			// cpp������ֱ�Ӷ�voidָ����в���,���ת��Ϊchar*(���ֽ�ģʽ)
			*(reinterpret_cast<char*>(dest) + i) =
				*(reinterpret_cast<const char*>(src) + i);
		}

		return dest;
	}
	// memmove��memcpy�Ľ��װ汾,���Դ���Դ�ڴ���Ŀ���ڴ��ص������,�������ص�,Ӧ�ı临�Ʒ�ʽ,�������ݸ���
	// ʵ�ֽ������Ϊ
	// Դ��ַ��Ŀ���ַ��ͷ�Ƚ�,���Դ�ڴ��ַ��Ŀ���ڴ��ַǰ��,���п��ܳ����ص����
	void* memmove(void* dest, const void* src, size_t n) {
		assert(dest != nullptr && src != nullptr);

		char* pDest = static_cast<char*>(dest);
		const char* pSrc = static_cast<const char*>(src);

		if (pSrc >= pDest) {
			// ���Դ�ڴ��ַ��Ŀ���ڴ��ַ���棬���ǰ������
			for (size_t i = 0; i < n; ++i) {
				*(pDest + i) = *(pSrc + i);
			}
		}
		else {
			// ���Դ�ڴ��ַ��Ŀ���ڴ��ַǰ�棬��Ӻ���ǰ����
			for (size_t i = n; i > 0; --i) {
				*(pDest + i - 1) = *(pSrc + i - 1);
			}
		}

		return dest;
	}
	// strcpy���ڿ���c���string,��char*,����Ϊȫ������
	char* strcpy(char* dest, const char* src) {
		char* start = dest;

		while (*src != '\0') {
			*dest = *src;
			dest++;
			src++;
		}
		// ������ĩβ�����ֹ��
		*dest = '\0';
		return start;
	}

	// strncpy����ָ�����Ƶ�char��Ŀn
	char* strncpy(char* dest, const char* src, size_t count) {
		size_t i;
		// ���ǵ�����Խ������,��Ч����Ӧ�ð����߽��ж�
		for (i = 0; i < count && src[i] != '\0'; i++) {
			dest[i] = src[i];
		}
		// ��Ϊ�Ǹ���д��,����Ĭ��ԭ���ݶ�ʧ,���Զ��д����ֹ��
		// ���src���ȴ���n,�ú��������Զ������ֹ��,��Ҫ�û��ֶ����
		// ���Ҹú�����û�а�����dest����ı߽��ж�,������׳���
		for (; i < count; i++) {
			dest[i] = '\0';
		}

		return dest;
	}

	// strcat���ڸ����ַ���
	char* strcat(char* dest, const char* src) {
		char* p = dest; // ��ָ�� p ָ�� dest ����ʼλ��
		while (*p)      // �ҵ� dest �е� null ��ֹ��
			++p;
		while (*src) // �� src �е��ַ�������Ƶ� dest ��
			*p++ = *src++;
		*p = '\0';   // �� dest ��ĩβ��� null ��ֹ��
		return dest; // ����ƴ�Ӻ���ַ���
	}

	// strncat���ڸ����ַ���,����ָ��char����Ŀ
	char* strncat(char* dest, const char* src,
		size_t n) { // �ȼ�¼Ŀ��sting����Ŀ�ͷ,��󷵻�
		char* ret = dest;
		// �ƶ���Ŀ�������ĩβ
		while (*dest != '\0') {
			dest++;
		}
		while (n-- && *src != '\0') {
			*dest++ = *src++;
		}
		*dest = '\0';
		return ret;
	}

	// �ж�n���ֽ��Ƿ����,�����ȷ���0,�������ȷ���һ������
	int memcmp(const void* ptr1, const void* ptr2, size_t size) {
		// ��ָ��תΪconst unsigned char���ͣ��Ա�֤���Խ����ֽڼ���ıȽ�
		const unsigned char* p1 = static_cast<const unsigned char*>(ptr1);
		const unsigned char* p2 = static_cast<const unsigned char*>(ptr2);

		// ���ֽڱȽ�����ָ����ָ����ڴ�飬�������׸�����ȵ��ֽڵĲ�ֵ
		for (size_t i = 0; i < size; i++) {
			if (p1[i] != p2[i]) {
				return p1[i] - p2[i];
			}
		}
		// �������ָ����ָ����ڴ����ȫ��ȣ��򷵻�0
		return 0;
	}

	int strcmp(const char* str1, const char* str2) {
		// ���ַ��Ƚ������ַ�����ֱ����������ȵ��ַ���������һ���ַ�������Ϊֹ
		while (*str1 && *str2 && (*str1 == *str2)) {
			str1++;
			str2++;
		}

		// ��������ַ����Ѿ���ȫ��ȣ��򷵻�0
		if (*str1 == *str2) {
			return 0;
		}

		// ���str1ָ����ַ�����str2ָ����ַ����򷵻�����
		if (*str1 > *str2) {
			return 1;
		}
		else {
			// ���򷵻ظ���
			return -1;
		}
	}

	//	// ʹ��locale����б��ػ��Ƚ�
	// 	   //strcollʵ���Ѷȹ���,�޷�ͨ������,���³����Ϊʵ����ʽ
	//#include <locale.h>
	//	int strcoll(const char* str1, const char* str2) {
	//		// ���ñ��ػ���Ϣ
	//		setlocale(LC_COLLATE, "");
	//
	//		// ʹ�õ�ǰ���ػ���Ϣ�Ƚ������ַ���
	//		return strcoll(str1, str2);
	//	}

	int strncmp(const char* s1, const char* s2, size_t n) {
		// ���nΪ0��˵���ַ������
		if (n == 0)
			return 0;

		// ���������ַ���
		while (*s1 && (*s1 == *s2) && --n) {
			s1++;
			s2++;
		}

		// ���رȽϽ��
		return (*(const unsigned char*)s1) - (*(const unsigned char*)s2);
	}

	size_t strlen(const char* str)
	{
		const char* p = str;

		// ����ַ�������ֱ�������ַ��������� '\0'
		while (*p != '\0')
			++p;

		// �����ַ����ĳ��ȣ���ָ�� p ��ȥ��ʼָ�� str
		return p - str;
	}
	// �Զ���ʵ�ֵ� strxfrm ����
	size_t strxfrm(char* destination, const char* source, size_t num)
	{
		// ��ȡԴ�ַ����ĳ���
		size_t sourceLength = strlen(source);

		// ��� num Ϊ 0����ֱ�ӷ���Դ�ַ����ĳ���
		if (num == 0)
			return sourceLength;

		// ���㿽���ĳ��ȣ�ȷ����������󿽱�����
		size_t copyLength = (sourceLength < num - 1) ? sourceLength : num - 1;

		// ��Դ�ַ�����ǰ copyLength ���ַ�������Ŀ���ַ�������
		strncpy(destination, source, copyLength);

		// ��Ŀ���ַ���������һ��λ����ӿ��ַ���ȷ���ַ�����ȷ��ֹ
		destination[copyLength] = '\0';

		// ����Դ�ַ����ĳ�����Ϊ���
		return sourceLength;
	}

	// �Զ���ʵ�ֵ� memchr ����
	void* memchr(const void* ptr, int value, size_t num)
	{
		// ��ָ�� ptr ǿ��ת��Ϊ const unsigned char* ���͵�ָ��
		const unsigned char* p = static_cast<const unsigned char*>(ptr);

		// ��Ҫ������ֵ value ǿ��ת��Ϊ unsigned char ����
		unsigned char val = static_cast<unsigned char>(value);

		// ѭ���Ƚ�ÿ���ֽ�
		for (size_t i = 0; i < num; ++i)
		{
			// ����ҵ�ƥ���ֵ���򷵻�ָ�� p �ĵ�ַ
			if (*p == val)
				return const_cast<void*>(static_cast<const void*>(p));

			// �ƶ�ָ�� p ����һ���ֽ�
			++p;
		}

		// ��������������ֽ���Ȼû���ҵ�ƥ��ֵ���򷵻ؿ�ָ��
		return nullptr;
	}
	//ͬ��
	char* strchr(const char* str, int ch)
	{
		const char* p = str;
		char c = static_cast<char>(ch);

		while (*p != '\0')
		{
			if (*p == c)
				return const_cast<char*>(p);
			++p;
		}

		return nullptr;
	}

	// �Զ���ʵ�ֵ� strcspn ����
	size_t strcspn(const char* str, const char* charset)
	{
		// ��ָ�� str ǿ��ת��Ϊ const char* ���͵�ָ��
		const char* p = str;

		// ���ѭ������������ַ��� str �е��ַ�
		while (*p != '\0')
		{
			// ��ָ�� charset ǿ��ת��Ϊ const char* ���͵�ָ��
			const char* q = charset;

			// �ڲ�ѭ������������ַ��� charset �е��ַ�
			while (*q != '\0')
			{
				// ������ַ������ҵ����뵱ǰ�ַ���ƥ����ַ���
				// �򷵻ص�ǰ�ַ����ַ��� str �е�λ����������ƫ������
				if (*p == *q)
					return p - str;

				// �ƶ�ָ�� q ����һ���ַ�
				++q;
			}

			// �ƶ�ָ�� p ����һ���ַ�
			++p;
		}

		// ��������������ַ��� str ��Ȼû���ҵ��κ�ƥ���ַ���
		// �򷵻��ַ��� str �ĳ��ȣ����ӿ�ͷ����β���ַ�����
		return p - str;
	}

	// �Զ���ʵ�ֵ� strpbrk ����
	char* strpbrk(const char* str, const char* charset)
	{
		// ��ָ�� str ǿ��ת��Ϊ const char* ���͵�ָ��
		const char* p = str;

		// ���ѭ������������ַ��� str �е��ַ�
		while (*p != '\0')
		{
			// ��ָ�� charset ǿ��ת��Ϊ const char* ���͵�ָ��
			const char* q = charset;

			// �ڲ�ѭ������������ַ��� charset �е��ַ�
			while (*q != '\0')
			{
				// ������ַ������ҵ����뵱ǰ�ַ���ƥ����ַ���
				// �򷵻ص�ǰ�ַ���ָ�룬��Ҫ��������ת��������������
				if (*p == *q)
					return const_cast<char*>(p);

				// �ƶ�ָ�� q ����һ���ַ�
				++q;
			}

			// �ƶ�ָ�� p ����һ���ַ�
			++p;
		}

		// ��������������ַ��� str ��Ȼû���ҵ��κ�ƥ���ַ���
		// �򷵻ؿ�ָ��
		return nullptr;
	}

	char* $$strrchr(const char* str, int ch)
	{
		const char* p = str;
		char c = static_cast<char>(ch);
		char* last = nullptr;

		// �����ַ�������¼���һ��ƥ���ַ���λ��
		while (*p != '\0')
		{
			if (*p == c)
				last = const_cast<char*>(p);
			++p;
		}

		// �������һ��ƥ���ַ���λ�ã����û��ƥ���ַ��򷵻ؿ�ָ��
		return last;
	}

	size_t strspn(const char* str, const char* charset)
	{
		const char* p = str;

		// �����ַ�����ֱ�����������ַ����е��ַ�Ϊֹ
		while (*p != '\0')
		{
			const char* q = charset;
			bool found = false;

			// �����ַ����������Ƿ�����뵱ǰ�ַ�ƥ����ַ�
			while (*q != '\0')
			{
				if (*p == *q)
				{
					found = true;
					break;
				}

				++q;
			}

			// �����ǰ�ַ������ַ����У��򷵻ص�ǰ�ַ���λ������
			if (!found)
				return p - str;

			++p;
		}

		// ��������������ַ�����˵�������ַ������ַ����У������ַ����ĳ���
		return p - str;
	}

	char* strstr(const char* str, const char* substr)
	{
		const char* p = str;

		// ���ѭ�����������ַ����е�ÿ���ַ�
		while (*p != '\0')
		{
			const char* q = substr;
			const char* match = p;

			// �ڲ�ѭ����ƥ�����ַ����е��ַ������ַ����е��ַ�
			while (*q != '\0' && *match == *q)
			{
				++match;
				++q;
			}

			// ������ַ����Ѿ���ȫƥ�䣬�򷵻�ƥ�����ʼλ��
			if (*q == '\0')
				return const_cast<char*>(p);

			// �ƶ����ַ�����ָ�뵽��һ���ַ�
			++p;
		}

		// ����������������ַ�����δ�ҵ�ƥ������ַ������򷵻ؿ�ָ��
		return nullptr;
	}

	char* strtok(char* str, const char* delim)
	{
		static char* nextToken = nullptr;

		// ��� str ��Ϊ nullptr���������һ�����Ƶ���ʼλ��
		if (str != nullptr)
			nextToken = str;

		// �����һ������Ϊ nullptr�����ʾ�Ѿ������������ַ��������� nullptr
		if (nextToken == nullptr)
			return nullptr;

		// �����ַ�����ͷ�ķָ���
		while (*nextToken != '\0' && strchr(delim, *nextToken) != nullptr)
			++nextToken;

		// ����Ѿ������������ַ��������� nullptr
		if (*nextToken == '\0')
		{
			nextToken = nullptr;
			return nullptr;
		}

		// �ҵ���һ���ָ�����λ�ã��������滻Ϊ�ַ��������� '\0'
		char* token = nextToken;
		while (*nextToken != '\0' && strchr(delim, *nextToken) == nullptr)
			++nextToken;

		if (*nextToken != '\0')
		{
			*nextToken = '\0';
			++nextToken;
		}

		return token;
	}

	void* memset(void* ptr, int value, size_t num)
	{
		unsigned char* p = static_cast<unsigned char*>(ptr);
		unsigned char byteValue = static_cast<unsigned char>(value);

		// ����ֽڽ�ָ��ֵд���ڴ�����
		for (size_t i = 0; i < num; ++i)
		{
			*p = byteValue;
			++p;
		}

		return ptr;
	}

	char* strerror(int errnum)
	{
		// �������������Ϣ��ӳ���
		static const char* errorMessages[] = {
			"Success",
			"Operation not permitted",
			"No such file or directory",
			// ... ����������Ϣ
		};

		// ������ķ�Χ
		static const size_t numErrors = sizeof(errorMessages) / sizeof(errorMessages[0]);

		// ���������Ƿ�����Ч��Χ��
		if (errnum >= 0 && static_cast<size_t>(errnum) < numErrors)
			return const_cast<char*>(errorMessages[errnum]);
		else
			return const_cast<char*>("Unknown error");
	}

#include <cctype>

	int stoi(const char* str)
	{
		int result = 0;
		bool negative = false;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ������ֱ�������������ַ����ַ���������
		while (std::isdigit(*str))
		{
			result = result * 10 + (*str - '0');
			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		return (negative ? -result : result);
	}

#include <cctype>
#include <climits>

	long stol(const char* str)
	{
		long result = 0;
		bool negative = false;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ��������ֱ�������������ַ����ַ���������
		while (std::isdigit(*str))
		{
			// ���������
			if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10))
			{
				// ���������������ݷ���λ����������Сֵ
				return (negative ? LONG_MIN : LONG_MAX);
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		return (negative ? -result : result);
	}

	unsigned long stoul(const char* str)
	{
		unsigned long result = 0;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ת�������ַ�Ϊ�޷��ų�������ֱ�������������ַ����ַ���������
		while (std::isdigit(*str))
		{
			// ���������
			if (result > ULONG_MAX / 10 || (result == ULONG_MAX / 10 && (*str - '0') > ULONG_MAX % 10))
			{
				// �������������������ֵ
				return ULONG_MAX;
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// �������յĽ��
		return result;
	}

	long long stoll(const char* str)
	{
		long long result = 0;
		bool negative = false;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ����������ֱ�������������ַ����ַ���������
		while (std::isdigit(*str))
		{
			// ���������
			if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10))
			{
				// ���������������ݷ���λ����������Сֵ
				return (negative ? LLONG_MIN : LLONG_MAX);
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		return (negative ? -result : result);
	}

	unsigned long long stoull(const char* str)
	{
		unsigned long long result = 0;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ת�������ַ�Ϊ�޷��ų���������ֱ�������������ַ����ַ���������
		while (std::isdigit(*str))
		{
			// ���������
			if (result > ULLONG_MAX / 10 || (result == ULLONG_MAX / 10 && (*str - '0') > ULLONG_MAX % 10))
			{
				// �������������������ֵ
				return ULLONG_MAX;
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// �������յĽ��
		return result;
	}

#include <cmath>
#include <limits>

	float stof(const char* str)
	{
		float result = 0.0f;
		bool negative = false;
		bool decimal = false;
		float fraction = 1.0f;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ��������ֱ�������������ַ���С������ַ���������
		while (std::isdigit(*str) || *str == '.')
		{
			if (*str == '.')
			{
				decimal = true;
				++str;
				continue;
			}

			if (decimal)
			{
				fraction *= 0.1f;
				result += (*str - '0') * fraction;
			}
			else
			{
				result = result * 10.0f + (*str - '0');
			}

			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		if (negative)
			result = -result;

		return result;
	}

	double stod(const char* str)
	{
		double result = 0.0;
		bool negative = false;
		bool decimal = false;
		double fraction = 1.0;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ��������ֱ�������������ַ���С������ַ���������
		while (std::isdigit(*str) || *str == '.')
		{
			if (*str == '.')
			{
				decimal = true;
				++str;
				continue;
			}

			if (decimal)
			{
				fraction *= 0.1;
				result += (*str - '0') * fraction;
			}
			else
			{
				result = result * 10.0 + (*str - '0');
			}

			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		if (negative)
			result = -result;

		return result;
	}

	long double stolda(const char* str)
	{
		long double result = 0.0;
		bool negative = false;
		bool decimal = false;
		long double fraction = 1.0;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ��������ֱ�������������ַ���С������ַ���������
		while (std::isdigit(*str) || *str == '.')
		{
			if (*str == '.')
			{
				decimal = true;
				++str;
				continue;
			}

			if (decimal)
			{
				fraction *= 0.1L;
				result += (*str - '0') * fraction;
			}
			else
			{
				result = result * 10.0L + (*str - '0');
			}

			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		if (negative)
			result = -result;

		return result;
	}

	long double stold(const char* str)
	{
		long double result = 0.0;
		bool negative = false;
		bool decimal = false;
		long double fraction = 1.0;

		// �����հ��ַ�
		while (std::isspace(*str))
			++str;

		// ������λ
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// ת�������ַ�Ϊ��������ֱ�������������ַ���С������ַ���������
		while (std::isdigit(*str) || *str == '.')
		{
			if (*str == '.')
			{
				decimal = true;
				++str;
				continue;
			}

			if (decimal)
			{
				fraction *= 0.1L;
				result += (*str - '0') * fraction;
			}
			else
			{
				result = result * 10.0L + (*str - '0');
			}

			++str;
		}

		// ���ݷ���λȷ�����յĽ��
		if (negative)
			result = -result;

		return result;
	}

#include <cstddef>

	template <typename T>
	char* to_string(const T& value)
	{
		// ���֧�ֵ�����λ��Ϊ20λ����������λ��
		constexpr size_t MaxDigits = 20;

		// ����һ���ַ�������������
		static char buffer[MaxDigits + 1];

		T absValue = value;
		bool negative = false;
		size_t index = MaxDigits;

		// ���������
		if (value < 0)
		{
			negative = true;
			absValue = -absValue;
		}

		// ����������ת��Ϊ�ַ������������ַ�������
		do
		{
			buffer[--index] = static_cast<char>('0' + absValue % 10);
			absValue /= 10;
		} while (absValue > 0);

		// ���Ϊ��������Ӹ���
		if (negative)
			buffer[--index] = '-';

		// ����ָ�����ַ�����ָ��
		return &buffer[index];
	}
}
#endif
