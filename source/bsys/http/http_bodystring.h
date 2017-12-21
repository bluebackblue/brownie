#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ÇgÇsÇsÇoÅB
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** MakeBodyString_DataHeader
	*/
	STLString MakeBodyString_DataHeader(const STLString& a_boundarystring,const STLString& a_formname,const STLString& a_filename);

	/** MakeBodyString_DataFooter
	*/
	STLString MakeBodyString_DataFooter();

	/** MakeBodyString_TextHeader
	*/
	STLString MakeBodyString_TextHeader(const STLString& a_boundarystring,const STLString& a_formname);

	/** MakeBodyString_DataFooter
	*/
	STLString MakeBodyString_TextFooter();

	/** MakeBodyString_Header
	*/
	STLString MakeBodyString_Header(const STLString& a_boundarystring,Http_Mode::Id a_mode,const STLString& a_request,const STLString& a_host,s32 a_all_content_size);

	/** MakeBodyString_PostDataFooter
	*/
	STLString MakeBodyString_PostDataFooter(const STLString& a_boundarystring);
}}
#endif

