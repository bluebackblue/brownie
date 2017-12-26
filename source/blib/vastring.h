#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 可変引数文字列操作。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./threadlocal.h"


/** include
*/
#include <iostream>
#include <functional>


/** NBlib
*/
namespace NBlib
{
	/** VaString
	*/
	const char* VaString(void* a_buffer,s32 a_buffer_size,const char* a_format,...);


	/** VaString
	*/
	const wchar* VaString(void* a_buffer,s32 a_buffer_size,const wchar* a_format,...);


	/** デバッグ用のバッファ。
	*/
	#if !defined(ROM_MASTER)
	class DebugLogBuffer
	{
	public:

		/** GetBuffer
		*/
		static char* GetBuffer();

		/** GetBufferSize
		*/
		static s32 GetBufferSize();

	};
	#endif


}


/** VASTRING
*/
#define VASTRING(BUFFER,BUFFERSIZE,...)				NBlib::VaString(BUFFER,BUFFERSIZE,__VA_ARGS__)


/** デバッグ用バッファ。
*/
#if defined(ROM_MASTER)

#else

	#define VASTRING_DEBUG(...)						VASTRING(reinterpret_cast<void*>(NBlib::DebugLogBuffer::GetBuffer()),NBlib::DebugLogBuffer::GetBufferSize(),__VA_ARGS__)

#endif

