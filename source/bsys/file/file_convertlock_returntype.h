#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include "../types/types.h"


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
			//���R���o�[�g => �R���o�[�g���B
			Locked = 0,

			//�R���o�[�g�� => �R���o�[�g�ς݁B
			Unlocked,

			//�R���o�[�g���B
			ConvertNow,

			//�R���o�[�g�ς݁B
			AlreadyConverted,
		};
	};
}}
#endif
