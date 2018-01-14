#pragma once

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
		mutable Position2DType<f32> mouse;
		bool isview;
		bool isactive;

		/** isopen
		*/
		AtomicValue<bool> isopen;

		/** default_size
		*/
		Size2DType<f32> default_size;

		/** client_size
		*/
		Size2DType<f32> client_size;

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
		static Size2DType<f32> GetDesktopSize();

	public:

		/** Create
		*/
		void Create(const STLWString& a_title,const Size2DType<f32>& a_size);

		/** Delete
		*/
		void Delete();

		/** GetClientSize
		*/
		const Size2DType<f32>& GetClientSize() const;

		/** GetMouse
		*/
		Position2DType<f32> GetMouse() const;

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

