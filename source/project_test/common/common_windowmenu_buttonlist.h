#pragma once

/**
 * Copyright (c) blueback
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
	/** WindowMenu_ButtonList
	*/
	class WindowMenu_ButtonList : public NBsys::NWindowMenu::WindowMenu_Window_Base
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

		/** count
		*/
		s32 count;

	public:

		/** constructor
		*/
		WindowMenu_ButtonList(f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11);

		/** destructor
		*/
		virtual ~WindowMenu_ButtonList();

	public:

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest() const;

		/** 削除リクエスト。設定。
		*/
		virtual void CallBack_SetDeleteRequest();

	public:

		/** AddButton
		*/
		void AddButton(const STLWString& a_string,const std::function<void(void)>& a_function);

	};


}}
#pragma warning(pop)
#endif

