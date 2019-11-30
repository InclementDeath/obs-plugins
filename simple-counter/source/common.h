#pragma once

#include <obs-internal.h>
#include <util/platform.h>
#include <string>
#include <regex>
#include <utility>

static const char* ToNarrow(const wchar_t* wcs)
{
	size_t len = wcslen(wcs);
	char* text = new char[len];
	os_wcs_to_utf8(wcs, 0, text, len);

	return text;
}

static const wchar_t* ToWide(const char* utf8)
{
	size_t len = strlen(utf8);
	wchar_t* text = new wchar_t[len];
	os_utf8_to_wcs(utf8, 0, text, len);

	return text;
}


template <typename T1, typename T2>
static void Clamp(T1* num, const T2& min, const T2& max)
{
	assert(!(max < min));
	*num = (*num < min) ? min : (max < *num) ? max : *num;
}

template <typename T1, typename T2>
static T1 Clamp(const T1& num, const T2& min, const T2& max)
{
	assert(!(max < min));
	return (num < min) ? min : (max < num) ? max : num;
}


using text_function = std::wstring(*)(void* data);
struct text_method
{
	std::wstring syntax;
	text_function func;

	text_method(std::wstring _syntax, const text_function& _func) : syntax(std::move(_syntax)), func(_func) {}
	text_method(const char* const _syntax, const text_function& _func) : syntax(ToWide(_syntax)), func(_func) {}

	std::wregex get_regex() const
	{
		std::wstring reg = L"\\$\\{(" + syntax + L")\\}";
		return std::wregex(reg, std::regex_constants::extended);
	}
};