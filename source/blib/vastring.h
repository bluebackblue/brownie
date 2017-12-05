#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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


/** NBlib
*/
namespace NBlib
{
	/** VaString
	*/
	const char* VaString(void* a_buffer,s32 a_buffer_size,const char* a_format,...);

	/** WVaString
	*/
	const wchar* VaString(void* a_buffer,s32 a_buffer_size,const wchar* a_format,...);

	/** デバッグ用のバッファ。
	*/
	#if defined(ROM_MASTER)

	#else

		class DebugLogBuffer
		{
		public:
			/** GetBuffer
			*/
			static char* GetBuffer()
			{
				#if(BLIB_THREADLOCAL_ENABLE)
				{
					ThreadLocal& t_threadlocal_reference = GetThreadLocal(BLIB_VASTRING_DEBUG_THREADLOCALSLOT);

					if(t_threadlocal_reference.pointer == nullptr){
						t_threadlocal_reference.pointer = ::malloc(BLIB_VASTRING_DEBUG_SIZE);
					}

					return reinterpret_cast<char*>(t_threadlocal_reference.pointer);
				}
				#else
				{
					ASSERT(0);
				}
				#endif
			}
			/** GetBufferSize
			*/
			static s32 GetBufferSize()
			{
				return BLIB_VASTRING_DEBUG_SIZE;
			}
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

