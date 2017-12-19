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


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
namespace NBsys{namespace NWindow
{

	/** Window_Impl
	*/
	class Window_Impl
	{
	private:
		/** handle
		*/
		#if defined(PLATFORM_VCWIN)
		HWND handle;
		#endif

		/** mouse
		*/
		s32 mouse_x;
		s32 mouse_y;
		bool isview;
		bool isactive;

		/** isopen
		*/
		bool isopen;

		/** default
		*/
		s32 default_width;
		s32 default_height;

		/** client
		*/
		s32 client_width;
		s32 client_height;

	public:
		/** constructor
		*/
		Window_Impl();

		/** destructor
		*/
		nonvirtual ~Window_Impl();

	public:
		static std::tuple<s32,s32> GetDesktopSize();

	public:
		/** Create
		*/
		void Create(const STLWString& a_title,s32 a_width,s32 a_height);

		/** Delete
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

		/** Update
		*/
		void Update();

		/** IsEnd
		*/
		bool IsEnd();

		/** IsView
		*/
		bool IsView();

		/** IsActive
		*/
		bool IsActive();

		/** CallBackProc
		*/
		#if defined(PLATFORM_VCWIN)
		LRESULT CallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam);
		#endif

		/** GetHandle
		*/
		#if defined(PLATFORM_VCWIN)
		HWND GetHandle();
		#endif

		/** StaticCallBackProc
		*/
		#if defined(PLATFORM_VCWIN)
		static LRESULT CALLBACK StaticCallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam);
		#endif

	};

}}
#endif

