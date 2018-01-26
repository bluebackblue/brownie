#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 文字ツール。
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
	/** WcharからCharへ変換。
	*/
	void WcharToChar(const STLWString& a_wstring,STLString& a_string);


	/** CharからWcharへ変換。
	*/
	void CharToWchar(const STLString& a_string,STLWString& a_wstring);


	/** WcharToChar
	*/
	STLString WcharToChar(const STLWString& a_wstring);


	/** CharToWchar
	*/
	STLWString CharToWchar(const STLString& a_string);


	/** 16進数文字列 => s32 への変換。
	*/
	void HexCharToInt(const STLString& a_string,s32& a_value);


	/** a_stringの先頭文字がa_prefixと一致するかどうか。
	*/
	bool StartsWith(const STLString& a_string,const STLString& a_prefix);


}

