﻿#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＯＰＥＮＳＳＬ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#if(BSYS_OPENSSL_ENABLE)
	#include <brownie_config/openssl_include.h>
#endif


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** OpenSsl_Item
	*/
	class OpenSsl_Item
	{
	private:

		/** id
		*/
		s32 id;

		/** ssl
		*/
		SSL* ssl;

	public:

		/** constructor
		*/
		OpenSsl_Item(s32 a_id);
		
		/** destructor
		*/
		nonvirtual ~OpenSsl_Item();

	public:

		/** GetId
		*/
		s32 GetId();

		/** GetSsl
		*/
		SSL* GetSsl();

		/** SetSsl
		*/
		void SetSsl(SSL* a_ssl);

	};


}}
#pragma warning(pop)
#endif

