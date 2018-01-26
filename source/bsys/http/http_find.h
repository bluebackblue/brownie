#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(RingBufferBase<u8>& a_ringbuffer,u8 a_find_a,u8 a_find_b);


	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(RingBufferBase<u8>& a_ringbuffer,u8 a_find_a);


	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(const u8* a_data,s32 a_size,u8 a_find_a,u8 a_find_b);


	/** FindContentsLength
	*/
	s32 FindContentsLength(const STLString& a_string);


	/** FindStatusCode
	*/
	s32 FindStatusCode(const STLString& a_string);


}}
#endif

