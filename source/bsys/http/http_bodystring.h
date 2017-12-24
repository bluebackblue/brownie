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
	/** MakeBodyString_BinarHeader
	*/
	STLString MakeBodyString_BinaryHeader(const STLString& a_boundarystring,const STLString& a_formname,const STLString& a_filename);


	/** MakeBodyString_BinarFooter
	*/
	STLString MakeBodyString_BinarFooter();


	/** MakeBodyString_TextHeader
	*/
	STLString MakeBodyString_TextHeader(const STLString& a_boundarystring,const STLString& a_formname);


	/** MakeBodyString_BinarFooter
	*/
	STLString MakeBodyString_TextFooter();


	/** MakeBodyString_Header
	*/
	STLString MakeBodyString_Header(const STLString& a_boundarystring,Http_Mode::Id a_mode,const STLString& a_path,const STLString& a_host,s32 a_binary_size);


	/** MakeBodyString_PostBinarFooter
	*/
	STLString MakeBodyString_PostBinarFooter(const STLString& a_boundarystring);


}}
#endif

