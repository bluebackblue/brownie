﻿#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief DirectSound
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../wave/wave.h"
#include "../window/window.h"
#pragma warning(pop)


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** システムの開始。
	*/
	void StartSystem(const sharedptr<NBsys::NWindow::Window>& a_window);


	/** システムの終了リクエスト。
	*/
	void EndSystemRequest();


	/** システムの終了。
	*/
	void EndSystem();


	/** 更新。
	*/
	void Update();


	/** サウンドバッファ作成。
	*/
	s32 CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d);


	/** サウンドバッファ削除。
	*/
	void DeleteSoundBuffer(s32 a_id);


	/** 再生。
	*/
	s32 Play(s32 a_id,bool a_duplicate,bool a_loop,bool a_auto_delete);

	
	/** 再生中チェック。
	*/
	bool IsPlay(s32 a_id);


}}
#pragma warning(pop)
#endif

