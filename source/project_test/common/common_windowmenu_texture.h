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


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** Common_WindowMenu_Texture
	*/
	class Common_WindowMenu_Texture : public NBsys::NWindowMenu::WindowMenu_Window_Base
	{
	private:

		/** endrequest
		*/
		bool endrequest;

		/** window_texture
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> window_texture;

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

	public:

		/** constructor
		*/
		Common_WindowMenu_Texture(const STLWString& a_string,f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11);

		/** destructor
		*/
		virtual ~Common_WindowMenu_Texture();

	public:

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest();

		/** 削除リクエスト。設定。
		*/
		virtual void CallBack_SetDeleteRequest();

	public:

		/** 左ボタン。
		*/
		void PushLeftButton();

		/** 右ボタン。
		*/
		void PushRightButton();

	};


}}
#endif

