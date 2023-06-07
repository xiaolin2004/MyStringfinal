#pragma once
#ifndef MY_CSTRING_H_
#define MY_CSTRING_H_

#include <cassert>
#include <iostream>
#include <cstddef>

namespace mystl
{
	void* memcpy(void* dest, const void* src, size_t n) { // 在进行内存拷贝之前，需要保证目标内存的空间足够大，因此可以使用assert宏进行断言判断
		assert(dest != nullptr && src != nullptr);
		// 可以使用一个for循环来逐字节地将源内存中的内容复制到目标内存中
		for (size_t i = 0; i < n; ++i) {
			// cpp不允许直接对void指针进行操作,因此转换为char*(单字节模式)
			*(reinterpret_cast<char*>(dest) + i) =
				*(reinterpret_cast<const char*>(src) + i);
		}

		return dest;
	}
	// memmove是memcpy的进阶版本,可以处理源内存与目标内存重叠的情况,当出现重叠,应改变复制方式,避免数据覆盖
	// 实现将情况简化为
	// 源地址与目标地址的头比较,如果源内存地址在目标内存地址前面,则有可能出现重叠情况
	void* memmove(void* dest, const void* src, size_t n) {
		assert(dest != nullptr && src != nullptr);

		char* pDest = static_cast<char*>(dest);
		const char* pSrc = static_cast<const char*>(src);

		if (pSrc >= pDest) {
			// 如果源内存地址在目标内存地址后面，则从前往后复制
			for (size_t i = 0; i < n; ++i) {
				*(pDest + i) = *(pSrc + i);
			}
		}
		else {
			// 如果源内存地址在目标内存地址前面，则从后往前复制
			for (size_t i = n; i > 0; --i) {
				*(pDest + i - 1) = *(pSrc + i - 1);
			}
		}

		return dest;
	}
	// strcpy用于拷贝c风格string,即char*,策略为全部复制
	char* strcpy(char* dest, const char* src) {
		char* start = dest;

		while (*src != '\0') {
			*dest = *src;
			dest++;
			src++;
		}
		// 自行在末尾添加休止符
		*dest = '\0';
		return start;
	}

	// strncpy可以指定复制的char数目n
	char* strncpy(char* dest, const char* src, size_t count) {
		size_t i;
		// 考虑到数组越界的情况,有效条件应该包含边界判断
		for (i = 0; i < count && src[i] != '\0'; i++) {
			dest[i] = src[i];
		}
		// 因为是覆盖写入,所以默认原数据丢失,可以多次写入终止符
		// 如果src长度大于n,该函数不会自动添加休止符,需要用户手动添加
		// 而且该函数并没有包含对dest数组的边界判断,因此容易出错
		for (; i < count; i++) {
			dest[i] = '\0';
		}

		return dest;
	}

	// strcat用于附加字符串
	char* strcat(char* dest, const char* src) {
		char* p = dest; // 将指针 p 指向 dest 的起始位置
		while (*p)      // 找到 dest 中的 null 终止符
			++p;
		while (*src) // 将 src 中的字符逐个复制到 dest 中
			*p++ = *src++;
		*p = '\0';   // 在 dest 的末尾添加 null 终止符
		return dest; // 返回拼接后的字符串
	}

	// strncat用于附加字符串,可以指定char的数目
	char* strncat(char* dest, const char* src,
		size_t n) { // 先记录目标sting数组的开头,最后返回
		char* ret = dest;
		// 移动到目标数组的末尾
		while (*dest != '\0') {
			dest++;
		}
		while (n-- && *src != '\0') {
			*dest++ = *src++;
		}
		*dest = '\0';
		return ret;
	}

	// 判断n个字节是否相等,如果相等返回0,如果不相等返回一个整数
	int memcmp(const void* ptr1, const void* ptr2, size_t size) {
		// 将指针转为const unsigned char类型，以保证可以进行字节级别的比较
		const unsigned char* p1 = static_cast<const unsigned char*>(ptr1);
		const unsigned char* p2 = static_cast<const unsigned char*>(ptr2);

		// 逐字节比较两个指针所指向的内存块，并返回首个不相等的字节的差值
		for (size_t i = 0; i < size; i++) {
			if (p1[i] != p2[i]) {
				return p1[i] - p2[i];
			}
		}
		// 如果两个指针所指向的内存块完全相等，则返回0
		return 0;
	}

	int strcmp(const char* str1, const char* str2) {
		// 逐字符比较两个字符串，直到遇到不相等的字符或者其中一个字符串结束为止
		while (*str1 && *str2 && (*str1 == *str2)) {
			str1++;
			str2++;
		}

		// 如果两个字符串已经完全相等，则返回0
		if (*str1 == *str2) {
			return 0;
		}

		// 如果str1指向的字符大于str2指向的字符，则返回正数
		if (*str1 > *str2) {
			return 1;
		}
		else {
			// 否则返回负数
			return -1;
		}
	}

	//	// 使用locale库进行本地化比较
	// 	   //strcoll实现难度过大,无法通过测试,以下程序仅为实现形式
	//#include <locale.h>
	//	int strcoll(const char* str1, const char* str2) {
	//		// 设置本地化信息
	//		setlocale(LC_COLLATE, "");
	//
	//		// 使用当前本地化信息比较两个字符串
	//		return strcoll(str1, str2);
	//	}

	int strncmp(const char* s1, const char* s2, size_t n) {
		// 如果n为0，说明字符串相等
		if (n == 0)
			return 0;

		// 遍历两个字符串
		while (*s1 && (*s1 == *s2) && --n) {
			s1++;
			s2++;
		}

		// 返回比较结果
		return (*(const unsigned char*)s1) - (*(const unsigned char*)s2);
	}

	size_t strlen(const char* str)
	{
		const char* p = str;

		// 逐个字符遍历，直到遇到字符串结束符 '\0'
		while (*p != '\0')
			++p;

		// 计算字符串的长度，即指针 p 减去初始指针 str
		return p - str;
	}
	// 自定义实现的 strxfrm 函数
	size_t strxfrm(char* destination, const char* source, size_t num)
	{
		// 获取源字符串的长度
		size_t sourceLength = strlen(source);

		// 如果 num 为 0，则直接返回源字符串的长度
		if (num == 0)
			return sourceLength;

		// 计算拷贝的长度，确保不超过最大拷贝长度
		size_t copyLength = (sourceLength < num - 1) ? sourceLength : num - 1;

		// 将源字符串的前 copyLength 个字符拷贝到目标字符数组中
		strncpy(destination, source, copyLength);

		// 在目标字符数组的最后一个位置添加空字符，确保字符串正确终止
		destination[copyLength] = '\0';

		// 返回源字符串的长度作为结果
		return sourceLength;
	}

	// 自定义实现的 memchr 函数
	void* memchr(const void* ptr, int value, size_t num)
	{
		// 将指针 ptr 强制转换为 const unsigned char* 类型的指针
		const unsigned char* p = static_cast<const unsigned char*>(ptr);

		// 将要搜索的值 value 强制转换为 unsigned char 类型
		unsigned char val = static_cast<unsigned char>(value);

		// 循环比较每个字节
		for (size_t i = 0; i < num; ++i)
		{
			// 如果找到匹配的值，则返回指针 p 的地址
			if (*p == val)
				return const_cast<void*>(static_cast<const void*>(p));

			// 移动指针 p 到下一个字节
			++p;
		}

		// 如果遍历完所有字节仍然没有找到匹配值，则返回空指针
		return nullptr;
	}
	//同上
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

	// 自定义实现的 strcspn 函数
	size_t strcspn(const char* str, const char* charset)
	{
		// 将指针 str 强制转换为 const char* 类型的指针
		const char* p = str;

		// 外层循环：逐个遍历字符串 str 中的字符
		while (*p != '\0')
		{
			// 将指针 charset 强制转换为 const char* 类型的指针
			const char* q = charset;

			// 内层循环：逐个遍历字符集 charset 中的字符
			while (*q != '\0')
			{
				// 如果在字符集中找到了与当前字符相匹配的字符，
				// 则返回当前字符在字符串 str 中的位置索引（即偏移量）
				if (*p == *q)
					return p - str;

				// 移动指针 q 到下一个字符
				++q;
			}

			// 移动指针 p 到下一个字符
			++p;
		}

		// 如果遍历完整个字符串 str 仍然没有找到任何匹配字符，
		// 则返回字符串 str 的长度（即从开头到结尾的字符数）
		return p - str;
	}

	// 自定义实现的 strpbrk 函数
	char* strpbrk(const char* str, const char* charset)
	{
		// 将指针 str 强制转换为 const char* 类型的指针
		const char* p = str;

		// 外层循环：逐个遍历字符串 str 中的字符
		while (*p != '\0')
		{
			// 将指针 charset 强制转换为 const char* 类型的指针
			const char* q = charset;

			// 内层循环：逐个遍历字符集 charset 中的字符
			while (*q != '\0')
			{
				// 如果在字符集中找到了与当前字符相匹配的字符，
				// 则返回当前字符的指针，需要进行类型转换来消除常量性
				if (*p == *q)
					return const_cast<char*>(p);

				// 移动指针 q 到下一个字符
				++q;
			}

			// 移动指针 p 到下一个字符
			++p;
		}

		// 如果遍历完整个字符串 str 仍然没有找到任何匹配字符，
		// 则返回空指针
		return nullptr;
	}

	char* $$strrchr(const char* str, int ch)
	{
		const char* p = str;
		char c = static_cast<char>(ch);
		char* last = nullptr;

		// 遍历字符串，记录最后一个匹配字符的位置
		while (*p != '\0')
		{
			if (*p == c)
				last = const_cast<char*>(p);
			++p;
		}

		// 返回最后一个匹配字符的位置，如果没有匹配字符则返回空指针
		return last;
	}

	size_t strspn(const char* str, const char* charset)
	{
		const char* p = str;

		// 遍历字符串，直到遇到不在字符集中的字符为止
		while (*p != '\0')
		{
			const char* q = charset;
			bool found = false;

			// 遍历字符集，查找是否存在与当前字符匹配的字符
			while (*q != '\0')
			{
				if (*p == *q)
				{
					found = true;
					break;
				}

				++q;
			}

			// 如果当前字符不在字符集中，则返回当前字符的位置索引
			if (!found)
				return p - str;

			++p;
		}

		// 如果遍历完整个字符串，说明所有字符都在字符集中，返回字符串的长度
		return p - str;
	}

	char* strstr(const char* str, const char* substr)
	{
		const char* p = str;

		// 外层循环：遍历主字符串中的每个字符
		while (*p != '\0')
		{
			const char* q = substr;
			const char* match = p;

			// 内层循环：匹配子字符串中的字符与主字符串中的字符
			while (*q != '\0' && *match == *q)
			{
				++match;
				++q;
			}

			// 如果子字符串已经完全匹配，则返回匹配的起始位置
			if (*q == '\0')
				return const_cast<char*>(p);

			// 移动主字符串的指针到下一个字符
			++p;
		}

		// 如果遍历完整个主字符串仍未找到匹配的子字符串，则返回空指针
		return nullptr;
	}

	char* strtok(char* str, const char* delim)
	{
		static char* nextToken = nullptr;

		// 如果 str 不为 nullptr，则更新下一个令牌的起始位置
		if (str != nullptr)
			nextToken = str;

		// 如果下一个令牌为 nullptr，则表示已经遍历完整个字符串，返回 nullptr
		if (nextToken == nullptr)
			return nullptr;

		// 跳过字符串开头的分隔符
		while (*nextToken != '\0' && strchr(delim, *nextToken) != nullptr)
			++nextToken;

		// 如果已经遍历完整个字符串，返回 nullptr
		if (*nextToken == '\0')
		{
			nextToken = nullptr;
			return nullptr;
		}

		// 找到下一个分隔符的位置，并将其替换为字符串结束符 '\0'
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

		// 逐个字节将指定值写入内存区域
		for (size_t i = 0; i < num; ++i)
		{
			*p = byteValue;
			++p;
		}

		return ptr;
	}

	char* strerror(int errnum)
	{
		// 错误码与错误消息的映射表
		static const char* errorMessages[] = {
			"Success",
			"Operation not permitted",
			"No such file or directory",
			// ... 其他错误消息
		};

		// 错误码的范围
		static const size_t numErrors = sizeof(errorMessages) / sizeof(errorMessages[0]);

		// 检查错误码是否在有效范围内
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

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为整数，直到遇到非数字字符或字符串结束符
		while (std::isdigit(*str))
		{
			result = result * 10 + (*str - '0');
			++str;
		}

		// 根据符号位确定最终的结果
		return (negative ? -result : result);
	}

#include <cctype>
#include <climits>

	long stol(const char* str)
	{
		long result = 0;
		bool negative = false;

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为长整数，直到遇到非数字字符或字符串结束符
		while (std::isdigit(*str))
		{
			// 检查溢出情况
			if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10))
			{
				// 处理溢出情况，根据符号位返回最大或最小值
				return (negative ? LONG_MIN : LONG_MAX);
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// 根据符号位确定最终的结果
		return (negative ? -result : result);
	}

	unsigned long stoul(const char* str)
	{
		unsigned long result = 0;

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 转换数字字符为无符号长整数，直到遇到非数字字符或字符串结束符
		while (std::isdigit(*str))
		{
			// 检查溢出情况
			if (result > ULONG_MAX / 10 || (result == ULONG_MAX / 10 && (*str - '0') > ULONG_MAX % 10))
			{
				// 处理溢出情况，返回最大值
				return ULONG_MAX;
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// 返回最终的结果
		return result;
	}

	long long stoll(const char* str)
	{
		long long result = 0;
		bool negative = false;

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为长长整数，直到遇到非数字字符或字符串结束符
		while (std::isdigit(*str))
		{
			// 检查溢出情况
			if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10))
			{
				// 处理溢出情况，根据符号位返回最大或最小值
				return (negative ? LLONG_MIN : LLONG_MAX);
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// 根据符号位确定最终的结果
		return (negative ? -result : result);
	}

	unsigned long long stoull(const char* str)
	{
		unsigned long long result = 0;

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 转换数字字符为无符号长长整数，直到遇到非数字字符或字符串结束符
		while (std::isdigit(*str))
		{
			// 检查溢出情况
			if (result > ULLONG_MAX / 10 || (result == ULLONG_MAX / 10 && (*str - '0') > ULLONG_MAX % 10))
			{
				// 处理溢出情况，返回最大值
				return ULLONG_MAX;
			}

			result = result * 10 + (*str - '0');
			++str;
		}

		// 返回最终的结果
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

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为浮点数，直到遇到非数字字符、小数点或字符串结束符
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

		// 根据符号位确定最终的结果
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

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为浮点数，直到遇到非数字字符、小数点或字符串结束符
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

		// 根据符号位确定最终的结果
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

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为浮点数，直到遇到非数字字符、小数点或字符串结束符
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

		// 根据符号位确定最终的结果
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

		// 跳过空白字符
		while (std::isspace(*str))
			++str;

		// 检查符号位
		if (*str == '-' || *str == '+')
		{
			negative = (*str == '-');
			++str;
		}

		// 转换数字字符为浮点数，直到遇到非数字字符、小数点或字符串结束符
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

		// 根据符号位确定最终的结果
		if (negative)
			result = -result;

		return result;
	}

#include <cstddef>

	template <typename T>
	char* to_string(const T& value)
	{
		// 最大支持的整数位数为20位（包括符号位）
		constexpr size_t MaxDigits = 20;

		// 创建一个字符数组来保存结果
		static char buffer[MaxDigits + 1];

		T absValue = value;
		bool negative = false;
		size_t index = MaxDigits;

		// 处理负数情况
		if (value < 0)
		{
			negative = true;
			absValue = -absValue;
		}

		// 将整数部分转换为字符，并保存在字符数组中
		do
		{
			buffer[--index] = static_cast<char>('0' + absValue % 10);
			absValue /= 10;
		} while (absValue > 0);

		// 如果为负数，添加负号
		if (negative)
			buffer[--index] = '-';

		// 返回指向结果字符串的指针
		return &buffer[index];
	}
}
#endif
