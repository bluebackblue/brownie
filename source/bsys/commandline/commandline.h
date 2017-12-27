#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コマンドライン。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


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

