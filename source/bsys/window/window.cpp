

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ウィンドウ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./window_impl.h"


/** include
*/
#include "./window.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
namespace NBsys{namespace NWindow
{
	/** constructor
	*/
	Window::Window()
	{
		this->impl.reset(new Window_Impl());
	}


	/** GetImpl
	*/
	sharedptr<Window_Impl>& Window::GetImpl()
	{
		return this->impl;
	}


	/** GetImpl
	*/
	const sharedptr<Window_Impl>& Window::GetImpl() const
	{
		return this->impl;
	}


	/** destructor
	*/
	Window::~Window()
	{
	}


	/** [static]GetDesktopSize
	*/
	std::tuple<s32,s32> Window::GetDesktopSize()
	{
		return Window_Impl::GetDesktopSize();
	}


	/** 作成。
	*/
	void Window::Create(const STLWString& a_title,s32 a_width,s32 a_height)
	{
		this->impl->Create(a_title,a_width,a_height);
	}


	/** 削除。
	*/
	void Window::Delete()
	{
		this->impl->Delete();
	}


	/** GetClientWidth
	*/
	s32 Window::GetClientWidth()
	{
		return this->impl->GetClientWidth();
	}


	/** GetClientHeight
	*/
	s32 Window::GetClientHeight()
	{
		return this->impl->GetClientHeight();
	}


	/** GetMouseX
	*/
	s32 Window::GetMouseX()
	{
		return this->impl->GetMouseX();
	}


	/** GetMouseY
	*/
	s32 Window::GetMouseY()
	{
		return this->impl->GetMouseY();
	}


	/** 更新。
	*/
	void Window::Update()
	{
		this->impl->Update();
	}


	/** 終了チェック。
	*/
	bool Window::IsEnd()
	{
		return this->impl->IsEnd();
	}


	/** 表示中チェック。
	*/
	bool Window::IsView()
	{
		return this->impl->IsView();
	}


	/** アクティブチェック。
	*/
	bool Window::IsActive()
	{
		return this->impl->IsActive();
	}


}}
#endif

