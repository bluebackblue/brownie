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

/** Test12_WindowMenu_Texture
*/
class Test12_WindowMenu_Texture : public NBsys::NWindowMenu::WindowMenu_Window_Base
{
private:
	/** id
	*/
	s32 id;

	/** endrequest
	*/
	bool endrequest;

	/** title_bg
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> title_bg;

	/** d3d11
	*/
	sharedptr<NBsys::ND3d11::D3d11> d3d11;

public:
	/** constructor
	*/
	Test12_WindowMenu_Texture(s32 a_id,const STLWString& a_string,f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11);

	/** destructor
	*/
	virtual ~Test12_WindowMenu_Texture();

public:
	/** 削除リクエスト。取得。
	*/
	virtual bool CallBack_GetDeleteRequest();

	/** 削除リクエスト。設定。
	*/
	virtual void CallBack_SetDeleteRequest();
};

#endif

