#pragma once

/**
 * Copyright (c) 2016-2017 blueback
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
#pragma warning(push)
#pragma warning(disable:4710 4820 4548 4987 4623 4626 5027 4365 4571 4625 4514 5026 4774)
#include <iostream>
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4548 4987 4820 4514 4365 4623 5027 4626 4625)
#include <functional>
#pragma warning(pop)


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

