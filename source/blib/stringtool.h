#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �����c�[���B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** Wchar����Char�֕ϊ��B
	*/
	void WcharToChar(const STLWString& a_wstring,STLString& a_string);

	/** Char����Wchar�֕ϊ��B
	*/
	void CharToWchar(const STLString& a_string,STLWString& a_wstring);

	/** Wchar����Sjis�֕ϊ��B
	*/
	#if defined(PLATFORM_VCWIN)
	void WcharToSjis(const STLWString& a_wstring,STLString& a_string);
	#endif

	/** 16�i�������� => s32 �ւ̕ϊ��B
	*/
	void HexCharToInt(const STLString& a_string,s32& a_value);

	/** �O����v�B
	*/
	bool StartsWith(const STLString& a_string,const STLString& a_prefix);
}

