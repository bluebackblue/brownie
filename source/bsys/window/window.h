#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ウィンドウ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
namespace NBsys{namespace NWindow
{
	/** Window_Impl
	*/
	class Window_Impl;

	/** Window
	*/
	class Window
	{
	private:
		/** impl
		*/
		sharedptr<Window_Impl> impl;

	public:
		/** GetImpl
		*/
		sharedptr<Window_Impl>& GetImpl();

	public:
		/** constructor
		*/
		Window();

		/** destructor
		*/
		nonvirtual ~Window();

	public:
		/** 作成。
		*/
		void Create(const STLWString& a_title,s32 a_width,s32 a_height);

		/** 削除。
		*/
		void Delete();

		/** GetClientWidth
		*/
		s32 GetClientWidth();

		/** GetClientHeight
		*/
		s32 GetClientHeight();

		/** GetMouseX
		*/
		s32 GetMouseX();

		/** GetMouseY
		*/
		s32 GetMouseY();

		/** 更新。
		*/
		void Update();

		/** 終了チェック。
		*/
		bool IsEnd();

		/** 表示中チェック。
		*/
		bool IsView();

		/** アクティブチェック。
		*/
		bool IsActive();

	};

}}
#endif

