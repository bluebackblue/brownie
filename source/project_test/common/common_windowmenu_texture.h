#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NTest{namespace NCommon
{
	/** WindowMenu_Texture
	*/
	class WindowMenu_Texture : public NBsys::NWindowMenu::WindowMenu_Window_Base
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
		WindowMenu_Texture(f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11);

		/** destructor
		*/
		virtual ~WindowMenu_Texture();

	public:

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest() const;

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
#pragma warning(pop)
#endif

