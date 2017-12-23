#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
#include <string>


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

