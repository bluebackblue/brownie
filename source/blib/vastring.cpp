﻿

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 可変引数文字列操作。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"
#include "./blib_bootinitialize.h"


/** include
*/
#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)

	#include <stdarg.h>

#endif


/** NBlib
*/
namespace NBlib
{
	/** VaString

	a_buffer		: バッファ。
	a_buffer_size	: バッファサイズ。
	a_format		: フォーマット。

	return			: a_buffer

	*/
	const char* VaString(void* a_buffer,s32 a_buffer_size,const char* a_format,...)
	{
		{
			s32 t_buffer_len = a_buffer_size;

			va_list t_va;
			va_start(t_va,a_format);

			#if defined(PLATFORM_VCWIN)
			{
				::_vsnprintf_s(reinterpret_cast<char*>(a_buffer),t_buffer_len,t_buffer_len-1,a_format,t_va);
			}
			#else
			{
				ASSERT(0);
			}
			#endif

			va_end(t_va);
		}

		return reinterpret_cast<char*>(a_buffer);
	}


	/** VaString

	a_buffer		: バッファ。
	a_buffer_size	: バッファサイズ。
	a_format		: フォーマット。

	return			: a_buffer

	*/
	const wchar* VaString(void* a_buffer,s32 a_buffer_size,const wchar* a_format,...)
	{
		{
			s32 t_buffer_len = a_buffer_size / 2;

			va_list t_va;
			va_start(t_va,a_format);

			#if defined(PLATFORM_VCWIN)
			{
				::_vsnwprintf_s(reinterpret_cast<wchar*>(a_buffer),t_buffer_len,t_buffer_len-1,a_format,t_va);
			}
			#else
			{
				ASSERT(0);
			}
			#endif

			va_end(t_va);
		}

		return reinterpret_cast<wchar*>(a_buffer);
	}


	#if defined(ROM_MASTER)

	#else

	/** [static]GetBuffer
	*/
	char* DebugLogBuffer::GetBuffer()
	{
		#if(BLIB_THREADLOCAL_ENABLE)
		{
			ThreadLocal& t_threadlocal_reference = GetThreadLocal(BLIB_VASTRING_DEBUG_THREADLOCALSLOT);

			if(t_threadlocal_reference.pointer == nullptr){
				t_threadlocal_reference.pointer = std::malloc(BLIB_VASTRING_DEBUG_SIZE);

				CallOnExit(std::bind([](void* a_pointer){
					return std::free(a_pointer);
				},t_threadlocal_reference.pointer));
			}

			return reinterpret_cast<char*>(t_threadlocal_reference.pointer);
		}
		#else
		{
			ASSERT(0);
		}
		#endif
	}


	/** [static]GetBufferSize
	*/
	s32 DebugLogBuffer::GetBufferSize()
	{
		return BLIB_VASTRING_DEBUG_SIZE;
	}

	#endif


}

