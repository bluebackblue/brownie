#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_ConvertLock_ReturnType
	*/
	struct File_ConvertLock_ReturnType
	{
		enum Id
		{
			//未コンバート => コンバート中。
			Locked = 0,

			//コンバート中。
			ConvertNow,

			//コンバート済み。
			AlreadyConverted,
		};
	};


}}
#endif

