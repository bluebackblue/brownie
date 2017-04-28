

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �ψ��������񑀍�B
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include <stdarg.h>

#endif


/** NBlib
*/
namespace NBlib
{
	/** VaString

	a_buffer		: �o�b�t�@�B
	a_buffer_size	: �o�b�t�@�T�C�Y�B
	a_format		: �t�H�[�}�b�g�B

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

	a_buffer		: �o�b�t�@�B
	a_buffer_size	: �o�b�t�@�T�C�Y�B
	a_format		: �t�H�[�}�b�g�B

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
}

