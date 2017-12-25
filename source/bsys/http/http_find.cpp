

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./http.h"
#include "./http_recv.h"
#include "./http_bodystring.h"


/** include
*/
//#include "../ssl/ssl.h"


/** include
*/
#include <regex>


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(RingBufferBase<u8>& a_ringbuffer,u8 a_find_a,u8 a_find_b)
	{
		s32 t_usesize = a_ringbuffer.GetUseSize();

		for(s32 ii=0;ii<(t_usesize-1);ii++){
			if((*(a_ringbuffer.GetItemFromUseList(ii)) == a_find_a)&&(*(a_ringbuffer.GetItemFromUseList(ii+1)) == a_find_b)){
				return ii;
			}
		}

		return -1;
	}


	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(RingBufferBase<u8>& a_ringbuffer,u8 a_find_a)
	{
		s32 t_usesize = a_ringbuffer.GetUseSize();

		for(s32 ii=0;ii<t_usesize;ii++){
			if((*(a_ringbuffer.GetItemFromUseList(ii)) == a_find_a)){
				return ii;
			}
		}

		return -1;
	}


	/** FindFromRingBuffer
	*/
	s32 FindFromRingBuffer(const u8* a_data,s32 a_size,u8 a_find_a,u8 a_find_b)
	{
		s32 t_usesize = a_size;

		for(s32 ii=0;ii<(t_usesize-1);ii++){
			if((a_data[ii] == a_find_a)&&(a_data[ii+1] == a_find_b)){
				return ii;
			}
		}

		return -1;
	}


	/** FindContentsLength
	*/
	s32 FindContentsLength(const STLString& a_string)
	{
		#if defined(PLATFORM_GNUCWIN)
		std::cmatch t_result;
		if(std::regex_match(a_string.c_str(),t_result,std::regex("Content-Length: ([-]?[0-9]+)"))){
		#else
		std::smatch t_result;
		if(std::regex_match(a_string,t_result,std::regex("Content-Length: ([-]?[0-9]+)"))){
		#endif
			s32 t_value = std::atoi(t_result[1].str().c_str());
			return t_value;
		}

		return -1;
	}


	/** FindStatusCode
	*/
	s32 FindStatusCode(const STLString& a_string)
	{
		#if defined(PLATFORM_GNUCWIN)
		std::cmatch t_result;
		if(std::regex_match(a_string.c_str(),t_result,std::regex("HTTP/1.1 ([-]?[0-9]+) .*"))){
		#else
		std::smatch t_result;
		if(std::regex_match(a_string,t_result,std::regex("HTTP/1.1 ([-]?[0-9]+) .*"))){
		#endif
			s32 t_value = std::atoi(t_result[1].str().c_str());
			return t_value;
		}

		return -1;
	}


}}
#endif

