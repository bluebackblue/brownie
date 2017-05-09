

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


/** include
*/
#include "./window_impl.h"


/** include
*/
#include "./window.h"


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
	sharedptr< Window_Impl >& Window::GetImpl()
	{
		return this->impl;
	}

	/** destructor
	*/
	Window::~Window()
	{
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

	/** GetDefaultWidth
	*/
	s32 Window::GetDefaultWidth()
	{
		return this->impl->GetDefaultWidth();
	}

	/** GetDefaultHeight
	*/
	s32 Window::GetDefaultHeight()
	{
		return this->impl->GetDefaultHeight();
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

