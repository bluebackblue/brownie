

/**
 * Copyright (c) blueback
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
	Size2DType<f32> Window::GetDesktopSize()
	{
		return Window_Impl::GetDesktopSize();
	}


	/** FindFromClassName
	*/
	bool Window::FindFromClassName()
	{
		return Window_Impl::FindFromClassName();
	}


	/** 作成。
	*/
	void Window::Create(const STLWString& a_title,const Size2DType<f32>& a_size)
	{
		this->impl->Create(a_title,a_size);
	}


	/** 削除。
	*/
	void Window::Delete()
	{
		this->impl->Delete();
	}


	/** GetClientSize
	*/
	const Size2DType<f32>& Window::GetClientSize()
	{
		return this->impl->GetClientSize();
	}


	/** GetMouse
	*/
	Position2DType<f32> Window::GetMouse()
	{
		return this->impl->GetMouse();
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


	/** タイトル設定。
	*/
	void Window::SetTitle(const STLWString& a_title)
	{
		return this->impl->SetTitle(a_title);

	}


}}
#endif

