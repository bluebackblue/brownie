#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief エラーコード。
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
			//成功。
			Success						= 0x00000000,

			//不明。
			UnknownError				= 0xFFFFFFFF,

			//処理中。
			Busy						= 0x80000001,	//処理中。

			//未初期化。
			Uninitialized				= 0x80000002,	//未初期化。







			//ロード。
			Load_Error					= 0x80001000,	// 不明。
			Load_AccessError			= 0x80001001,	// アクセスエラー。
			Load_ReadError				= 0x80001002,	// 読み込みエラー。
			Load_WriteError				= 0x80001003,	// 書き込みエラー。
			Load_OpenError				= 0x80001004,	// オープンエラー。
			Load_CancelError			= 0x80001005,	// キャンセルにより中断された。

			//メモリ。
			Memory_Error				= 0x80002000,	// 不明。
			Memory_OutOfMainMemoryError	= 0x80002001,	// メインメモリ不足。

			//オンライン。
			Online_Error				= 0x80003000,	// 不明。
			Online_StepError			= 0x80003001,	// 手続きエラー。
			Online_WirelessOff			= 0x80003002,	// ワイヤレスＯＦＦ。
			Online_BufferError			= 0x80003003,	// バッファエラー。
			Online_DisConnect 			= 0x80003004,	// 切断。

			//システム。
			System_Error				= 0x8000F000,	// 不明。
			System_InvalidID			= 0x8000F001,	// 無効なＩＤ。
			System_BufferOver			= 0x8000F002,	// 配列外。
		};

		/** code
		*/
		u32 code;

		/** constructor
		*/
		ErrorCode(u32 a_code)
			:
			code(a_code)
		{
		}

		/** destructor
		*/
		nonvirtual ~ErrorCode()
		{
		}
	};


}

