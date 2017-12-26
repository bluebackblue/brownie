

/**
* Copyright (c) 2017 blueback
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
#include "../types/types.h"


/** include
*/
#include "./window_impl.h"


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
namespace NBsys{namespace NWindow
{
	/** constructor
	*/
	Window_Impl::Window_Impl()
		:
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		handle(WIN_NULL),
		#endif
		mouse_x(0),
		mouse_y(0),
		isview(false),
		isactive(false),
		isopen(false),
		default_width(0),
		default_height(0),
		client_width(0),
		client_height(0)
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
	std::tuple<s32,s32> Window_Impl::GetDesktopSize()
	{
		RECT t_rect;
		HWND t_hwnd_desktop = ::GetDesktopWindow();
		::GetWindowRect(t_hwnd_desktop, &t_rect);

		return std::tuple<s32,s32>(t_rect.right - t_rect.left,t_rect.bottom - t_rect.top);
	}


	/** GetClientWidth
	*/
	s32 Window_Impl::GetClientWidth()
	{
		return this->client_width;
	}


	/** GetClientHeight
	*/
	s32 Window_Impl::GetClientHeight()
	{
		return this->client_height;
	}


	/** GetMouseX
	*/
	s32 Window_Impl::GetMouseX()
	{
		return this->mouse_x;
	}


	/** GetMouseY
	*/
	s32 Window_Impl::GetMouseY()
	{
		return this->mouse_y;
	}


	/** Create
	*/
	void Window_Impl::Create(const STLWString& a_title,s32 a_width,s32 a_height)
	{
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)

		HINSTANCE t_instance = ::GetModuleHandle(WIN_NULL);

		this->default_width = a_width;
		this->default_height = a_height;
		this->client_width = a_width;
		this->client_height = a_height;

		RECT t_rect = { 0, 0, a_width, a_height };
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
			LONG_PTR t_value = reinterpret_cast<AddressType>(this);
			::SetWindowLongPtr(t_handle,GWLP_USERDATA,t_value);
			#else
			LONG t_value = reinterpret_cast<AddressType>(this);
			::SetWindowLongPtr(t_handle,GWL_USERDATA,t_value);
			#endif

			::ShowWindow(t_handle,SW_SHOW);

			this->mouse_x = 0;
			this->mouse_y = 0;
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
	bool Window_Impl::IsEnd()
	{
		if(this->isopen){
			return false;
		}
		return true;
	}


	/** IsView
	*/
	bool Window_Impl::IsView()
	{
		return this->isview;
	}


	/** IsActive
	*/
	bool Window_Impl::IsActive()
	{
		return this->isactive;
	}


	/** GetHandle
	*/
	#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
	HWND Window_Impl::GetHandle()
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
					this->client_width = static_cast<s32>(LOWORD(a_lparam));
					this->client_height = static_cast<s32>(HIWORD(a_lparam));
					this->isview  = true;
				}
			}break;
		case WM_NCMOUSEMOVE:
			{
			}break;
		case WM_MOUSEMOVE:
			{
				this->mouse_x = static_cast<s32>(static_cast<f32>(LOWORD(a_lparam)));
				this->mouse_y = static_cast<s32>(static_cast<f32>(HIWORD(a_lparam)));
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
#endif

