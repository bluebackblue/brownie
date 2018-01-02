﻿#pragma once

/**
 * Copyright (c) 2016-2018 blueback
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


/** include
*/
#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBsys::NWindow
*/
#if(BSYS_WINDOW_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NWindow
{
	/** Window_Impl
	*/
	class Window_Impl
	{
	private:

		/** handle
		*/
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
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

		/** GetDesktopSize
		*/
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
		s32 GetClientWidth() const;

		/** GetClientHeight
		*/
		s32 GetClientHeight() const;

		/** GetMouseX
		*/
		s32 GetMouseX() const;

		/** GetMouseY
		*/
		s32 GetMouseY() const;

		/** Update
		*/
		void Update();

		/** IsEnd
		*/
		bool IsEnd() const;

		/** IsView
		*/
		bool IsView() const;

		/** IsActive
		*/
		bool IsActive() const;

		/** CallBackProc
		*/
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		LRESULT CallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam);
		#endif

		/** GetHandle
		*/
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		HWND GetHandle() const;
		#endif

		/** StaticCallBackProc
		*/
		#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)
		static LRESULT CALLBACK StaticCallBackProc(HWND a_hwnd,UINT a_msg,WPARAM a_wparam,LPARAM a_lparam);
		#endif

	};


}}
#pragma warning(pop)
#endif

