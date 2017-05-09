

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �E�B���h�E�B
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

	/** �쐬�B
	*/
	void Window::Create(const STLWString& a_title,s32 a_width,s32 a_height)
	{
		this->impl->Create(a_title,a_width,a_height);
	}

	/** �폜�B
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

	/** �X�V�B
	*/
	void Window::Update()
	{
		this->impl->Update();
	}

	/** �I���`�F�b�N�B
	*/
	bool Window::IsEnd()
	{
		return this->impl->IsEnd();
	}

	/** �\�����`�F�b�N�B
	*/
	bool Window::IsView()
	{
		return this->impl->IsView();
	}

	/** �A�N�e�B�u�`�F�b�N�B
	*/
	bool Window::IsActive()
	{
		return this->impl->IsActive();
	}

}}
#endif

