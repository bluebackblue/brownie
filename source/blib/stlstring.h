#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＳＴＬストリング。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./staticassert.h"
#include "./stlallocator.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4987 4365 4820 4626 5027 4623 4571 4625 5026 4774 4514)
#include <string>
#pragma warning(pop)


/** NBlib
*/
namespace NBlib
{
	/** STLString
	*/
	typedef std::basic_string<char,std::char_traits<char>,STLAllocator_String<char>> STLString;


	/** STLWString
	*/
	typedef std::basic_string<wchar,std::char_traits<wchar>,STLAllocator_String<wchar>> STLWString;


	/** ToString
	*/
	template <typename T> STLString ToString(T a_value)
	{
		return STLString(std::to_string(a_value).c_str());
	}


	/** ToWString
	*/
	template <typename T> STLWString ToWString(T a_value)
	{
		return STLWString(std::to_wstring(a_value).c_str());
	}


}


/** std
*/
#if defined(PLATFORM_GNUCWIN)
namespace std
{
	/** STLString
	*/
	template <> struct hash<NBlib::STLString> : public std::string
	{
		std::size_t operator()(const NBlib::STLString& a_custom_string) const
		{
			return hash<std::string>().operator()(a_custom_string.c_str());
		}
	};


	/** STLWString
	*/
	template <> struct hash<NBlib::STLWString> : public std::string
	{
		std::size_t operator()(const NBlib::STLWString& a_custom_string) const
		{
			return hash<std::wstring>().operator()(a_custom_string.c_str());
		}
	};


}
#endif

