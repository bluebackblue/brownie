﻿#pragma once

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

/** Test12_WindowMenu
*/
class Test12_WindowMenu : public NBsys::NWindowMenu::WindowMenu_Window_Base
{
private:
	/** id
	*/
	s32 id;

	/** endrequest
	*/
	bool endrequest;

	/** titlebg
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> titlebg;

public:
	/** constructor
	*/
	Test12_WindowMenu(s32 a_id,const STLWString& a_string,f32 a_offset_x,f32 a_offset_y);

	/** destructor
	*/
	virtual ~Test12_WindowMenu();

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

};

#endif

