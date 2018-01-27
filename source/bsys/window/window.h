#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ウィンドウ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


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

		/** GetImpl
		*/
		const sharedptr<Window_Impl>& GetImpl() const;

	public:

		/** constructor
		*/
		Window();

		/** destructor
		*/
		nonvirtual ~Window();

	public:

		/** [static]GetDesktopSize
		*/
		static Size2DType<f32> GetDesktopSize();

		/** FindFromClassName
		*/
		static bool FindFromClassName();

	public:

		/** 作成。
		*/
		void Create(const STLWString& a_title,const Size2DType<f32>& a_size);

		/** 削除。
		*/
		void Delete();

		/** GetClientSize
		*/
		const Size2DType<f32>& GetClientSize();

		/** GetMouse
		*/
		Position2DType<f32> GetMouse();

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

		/** タイトル設定。
		*/
		void SetTitle(const STLWString& a_title);

	};


}}
#endif

