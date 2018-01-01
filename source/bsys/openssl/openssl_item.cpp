#pragma once

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
#include <brownie_config/openssl_lib.h>
#endif


/** include
*/
#include "./openssl_item.h"


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** constructor
	*/
	OpenSsl_Item::OpenSsl_Item(s32 a_id)
		:
		id(a_id),
		ssl(nullptr)
	{
	}


	/** destructor
	*/
	OpenSsl_Item::~OpenSsl_Item()
	{
	}


	/** GetId
	*/
	s32 OpenSsl_Item::GetId()
	{
		return this->id;
	}


	/** GetSsl
	*/
	SSL* OpenSsl_Item::GetSsl()
	{
		return this->ssl;
	}


	/** SetSsl
	*/
	void OpenSsl_Item::SetSsl(SSL* a_ssl)
	{
		this->ssl = a_ssl;
	}


}}
#pragma warning(pop)
#endif

