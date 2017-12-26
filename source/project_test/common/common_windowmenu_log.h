#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** WindowMenu_Log
	*/
	class WindowMenu_Log : public NBsys::NWindowMenu::WindowMenu_Window_Base
	{
	private:

		/** endrequest
		*/
		bool endrequest;

		/** logtext
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> window_logtext[16];

		/** debuglog_counter
		*/
		s32 debuglog_counter;

	public:

		/** constructor
		*/
		WindowMenu_Log(f32 a_offset_x,f32 a_offset_y);

		/** destructor
		*/
		virtual ~WindowMenu_Log();

	public:

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest();

		/** 削除リクエスト。設定。
		*/
		virtual void CallBack_SetDeleteRequest();

		/** 更新処理。
		*/
		virtual void CallBack_Update();

	};


}}
#endif

