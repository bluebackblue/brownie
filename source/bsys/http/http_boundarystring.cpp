#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** MakeBoundaryString
	*/
	STLString MakeBoundaryString()
	{
		STLString t_boundary;

		static char s_charlist[] = {
			'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
			'1','2','3','4','5','6','7','8','9','0',

			//'_',':','\'',',','=','(','?',')','.','+','/',
		};

		//１文字以上、７０文字以下。
		//最後は「スペース」以外。
		for(s32 ii=0;ii<32;ii++){
			t_boundary += s_charlist[NBlib::GlobalRand_Get().Get() % COUNTOF(s_charlist)];
		}

		return t_boundary;
	}


}}
#endif

