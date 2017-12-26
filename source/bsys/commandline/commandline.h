#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief コマンドライン。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NCommandLine
*/
#if(BSYS_COMMANDLINE_ENABLE)
namespace NBsys{namespace NCommandLine
{
	/** コマンドライン文字列をJsonItemに変換する。
	*/
	sharedptr< JsonItem > ConvertToJsonItem(s32 a_argc,char* a_argv[]);


}}
#endif

