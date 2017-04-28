#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�t�H�[�}���X�J�E���^�[�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{
	/** PerformanceCounter
	*/
	class PerformanceCounter
	{
	public:

		/** [static]�uBootInitialize�v����Ăяo�����B
		*/
		static void InitPerformanceCounter();

		/** [static]GetPerformanceCounter
		*/
		static u64 GetPerformanceCounter();

		/** [static]�P�b�ɕK�v�ȃJ�E���g�����擾�B
		*/
		static u64 GetPerformanceSecCounter();

		/** [static]�P�}�C�N���b�ɕK�v�ȃJ�E���g�����擾�B
		*/
		static u64 GetPerformanceMicroSecCounter();

	};
}

