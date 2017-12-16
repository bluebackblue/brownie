#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** Test12_WindowMenu_Log
*/
class Test12_WindowMenu_Log : public NBsys::NWindowMenu::WindowMenu_Window_Base
{
private:
	/** endrequest
	*/
	bool endrequest;

	/** titlebg
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> titlebg;

	/** logtext
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> logtext[16];

	/** debuglog_counter
	*/
	s32 debuglog_counter;

public:
	/** constructor
	*/
	Test12_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y);

	/** destructor
	*/
	virtual ~Test12_WindowMenu_Log();

public:
	/** 削除リクエスト。取得。
	*/
	virtual bool CallBack_GetDeleteRequest();

	/** 削除リクエスト。設定。
	*/
	virtual void CallBack_SetDeleteRequest();

	/** アクティブ変更。
	*/
	virtual void CallBack_ChangeActive(bool a_active);

	/** 更新処理。
	*/
	virtual void CallBack_Update();

};

#endif

