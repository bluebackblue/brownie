

/**
 * Copyright (c) 2016-2018 blueback
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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBsys{namespace NWindow
{
	/** constructor
	*/
	Window_Impl::Window_Impl()
		:
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		handle(WIN_NULL),
		#endif
		mouse(),
		isview(false),
		isactive(false),
		isopen(false),
		default_size(0),
		client_size(0)
	{
	}


	/** destructor
	*/
	Window_Impl::~Window_Impl()
	{
		this->Delete();
	}


	/** [static]GetDesktopSize
	*/
	Size2DType<f32> Window_Impl::GetDesktopSize()
	{
		RECT t_rect;
		HWND t_hwnd_desktop = ::GetDesktopWindow();
		::GetWindowRect(t_hwnd_desktop, &t_rect);

		return Size2DType<f32>(static_cast<f32>(t_rect.right - t_rect.left),static_cast<f32>(t_rect.bottom - t_rect.top));
	}


	/** GetClientWidth
	*/
	const Size2DType<f32>& Window_Impl::GetClientSize() const
	{
		return this->client_size;
	}


	/** GetMouse
	*/
	Position2DType<f32> Window_Impl::GetMouse() const
	{
		POINT t_pos;
		if(::GetCursorPos(&t_pos) == TRUE){
			if(::ScreenToClient(this->handle,&t_pos)){
				this->mouse.xx = static_cast<f32>(t_pos.x);
				this->mouse.yy = static_cast<f32>(t_pos.y);
			}
		}

		return this->mouse;
	}


	/** Create
	*/
	void Window_Impl::Create(const STLWString& a_title,const Size2DType<f32>& a_size)
	{
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)

		HINSTANCE t_instance = ::GetModuleHandle(WIN_NULL);

		this->default_size = a_size;
		this->client_size = a_size;

		RECT t_rect = {
			0,
			0,
			static_cast<s32>(a_size.ww),
			static_cast<s32>(a_size.hh)
		};

		::AdjustWindowRect(&t_rect,WS_OVERLAPPEDWINDOW,FALSE);

		const wchar* t_classname = L"brownie window class";

		WNDCLASSEXW t_wndclass;
		{
			t_wndclass.cbSize			= sizeof(WNDCLASSEX);
			t_wndclass.style			= CS_VREDRAW | CS_HREDRAW;
			t_wndclass.cbClsExtra		= 0;
			t_wndclass.cbWndExtra		= 0;
			t_wndclass.lpfnWndProc		= Window_Impl::StaticCallBackProc;
			t_wndclass.hInstance		= t_instance;
			t_wndclass.hIcon			= ::LoadIcon(t_instance,IDI_APPLICATION);
			t_wndclass.hIconSm			= ::LoadIcon(t_instance,IDI_APPLICATION);
			t_wndclass.hCursor			= ::LoadCursor(WIN_NULL,IDC_ARROW);
			t_wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
			t_wndclass.lpszMenuName		= WIN_NULL;
			t_wndclass.lpszClassName	= t_classname;
		}

		::RegisterClassExW(&t_wndclass);

		HWND t_handle = ::CreateWindowExW(0,t_classname,a_title.c_str(),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,t_rect.right - t_rect.left,t_rect.bottom - t_rect.top,(HWND)WIN_NULL,(HMENU)WIN_NULL,t_instance,(LPSTR)WIN_NULL);
		if(t_handle != WIN_NULL){

			#if defined(ROM_64BIT)
			LONG_PTR t_value = reinterpret_cast<LONG_PTR>(this);
			::SetWindowLongPtr(t_handle,GWLP_USERDATA,t_value);
			#else
			LONG t_value = reinterpret_cast<LONG>(this);
			::SetWindowLongPtr(t_handle,GWL_USERDATA,t_value);
			#endif

			::ShowWindow(t_handle,SW_SHOW);

			this->mouse.Set(0,0);
			this->isview = true;
			this->isactive = false;
			this->handle = t_handle;
			this->isopen = true;
		}else{
			ASSERT(0);
		}

		#endif
	}


	/** Delete
	*/
	void Window_Impl::Delete()
	{
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		{
			if(this->handle != WIN_NULL){
				SendMessage(this->handle,WM_CLOSE,0,0);
			}

			{
				HINSTANCE t_instance = ::GetModuleHandle(WIN_NULL);
				const wchar_t* t_classname = L"brownie window class";
				::UnregisterClassW(t_classname,t_instance);
			}
		}
		#endif
	}


	/** Update
	*/
	void Window_Impl::Update()
	{
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		{
			MSG t_msg;
			if(::PeekMessage(&t_msg,0,0,0,PM_REMOVE)){
				::TranslateMessage(&t_msg);
				::DispatchMessage(&t_msg);
			}
		}
		#endif
	}


	/** IsEnd
	*/
	bool Window_Impl::IsEnd() const
	{
		if(this->isopen){
			return false;
		}
		return true;
	}


	/** IsView
	*/
	bool Window_Impl::IsView() const
	{
		return this->isview;
	}


	/** IsActive
	*/
	bool Window_Impl::IsActive() const
	{
		return this->isactive;
	}


	/** GetHandle
	*/
	#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
	HWND Window_Impl::GetHandle() const
	{
		return this->handle;
	}
	#endif

	
	/** CallBackProc
	*/
	#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
	LRESULT Window_Impl::CallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam)
	{
		switch(a_msg){
		case WM_CLOSE:
			{
				if(this->handle != WIN_NULL){
					#if defined(ROM_64BIT)
					LONG_PTR t_value = reinterpret_cast<AddressType>(nullptr);
					::SetWindowLongPtr(this->handle,GWLP_USERDATA,t_value);
					#else
					LONG t_value = reinterpret_cast<AddressType>(nullptr);
					::SetWindowLongPtr(this->handle,GWL_USERDATA,t_value);
					#endif
				}

				this->handle = WIN_NULL;
				this->isopen = false;

				return ::DefWindowProc(a_hwnd,a_msg,a_wparam,a_lparam);
			}
			break;
		case WM_DESTROY:
			{
			}break;
		case WM_ACTIVATEAPP:
			{
				if(a_wparam){
					this->isactive = true;
				}else{
					this->isactive = false;
				}
			}break;
		case WM_SIZE:
			{
				if((a_wparam == SIZE_MINIMIZED)||(a_wparam == SIZE_MAXHIDE)){
					this->isview  = false;
				}else{
					this->client_size.ww = static_cast<f32>(LOWORD(a_lparam));
					this->client_size.hh = static_cast<f32>(HIWORD(a_lparam));
					this->isview  = true;
				}
			}break;
		case WM_NCMOUSEMOVE:
			{
			}break;
		case WM_MOUSEMOVE:
			{
				//this->mouse.x = static_cast<s32>(static_cast<f32>(LOWORD(a_lparam)));
				//this->mouse.y = static_cast<s32>(static_cast<f32>(HIWORD(a_lparam)));
			}break;
		case WM_MOUSEWHEEL:
			{
				//l_getinput()->SetMouseWheel((short)HIWORD(a_wparam));
			}break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			break;
		default:
			{
				return ::DefWindowProc(a_hwnd,a_msg,a_wparam,a_lparam);
			}break;
		}
		return 0;
	}
	#endif


	/** StaticCallBackProc
	*/
	#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
	LRESULT CALLBACK Window_Impl::StaticCallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam)
	{
		#if defined(ROM_64BIT)
		LONG_PTR t_value = ::GetWindowLongPtr(a_hwnd,GWLP_USERDATA);
		Window_Impl* t_this = reinterpret_cast<Window_Impl*>(t_value);
		#else
		LONG t_value = ::GetWindowLongPtr(a_hwnd,GWL_USERDATA);
		Window_Impl* t_this = reinterpret_cast<Window_Impl*>(t_value);
		#endif

		if(t_this){
			return t_this->CallBackProc(a_hwnd,a_msg,a_wparam,a_lparam);
		}else{
			return ::DefWindowProc(a_hwnd,a_msg,a_wparam,a_lparam);
		}
	}
	#endif


}}
#pragma warning(pop)
#endif

