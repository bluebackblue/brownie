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


/** include
*/
#include "./http_recv_decl.h"
#include "./http_type.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http
	*/
	class Http
	{
	private:
	
		

	public:

		/** constructor
		*/
		Http();

		/** destructor
		*/
		nonvirtual ~Http();

	public:

	};


}}
#endif

