#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÇlÇlÇcÅBÇoÇlÇwÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../file/file.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NMmdPmx
{

	bool Load(sharedptr< NFile::File_Object >& a_file);

}}
#endif

