#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �G���[�R�[�h�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{

	/** ErrorCode
	*/
	struct ErrorCode
	{
		enum Id
		{
			//�����B
			Success						= 0x00000000,

			//�������B
			Busy						= 0x80000001,	//�������B

			//���[�h�B
			Load_Error					= 0x80001000,	// �s���B
			Load_AccessError			= 0x80001001,	// �A�N�Z�X�G���[�B
			Load_ReadError				= 0x80001002,	// �ǂݍ��݃G���[�B
			Load_WriteError				= 0x80001003,	// �������݃G���[�B
			Load_OpenError				= 0x80001004,	// �I�[�v���G���[�B
			Load_CancelError			= 0x80001005,	// �L�����Z���ɂ�蒆�f���ꂽ�B

			//�������B
			Memory_Error				= 0x80002000,	// �s���B
			Memory_OutOfMainMemoryError	= 0x80002001,	// ���C���������s���B

			//�I�����C���B
			Online_Error				= 0x80003000,	// �s���B
			Online_StepError			= 0x80003001,	// �葱���G���[�B
			Online_WirelessOff			= 0x80003002,	// ���C�����X�n�e�e�B
			Online_BufferError			= 0x80003003,	// �o�b�t�@�G���[�B
			Online_DisConnect 			= 0x80003004,	// �ؒf�B

			//�V�X�e���B
			System_Error				= 0x8000F000,	// �s���B
			System_InvalidID			= 0x8000F001,	// �����Ȃh�c�B
			System_BufferOver			= 0x8000F002,	// �z��O�B

			//�s���B
			UnknownError				= 0xFFFFFFFF,
		};
	};
}

