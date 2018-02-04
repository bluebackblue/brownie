#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジョイスティック。
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
	#include <mmsystem.h>

#endif


/** NBsys::NJoy
*/
#if(BSYS_JOY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NJoy
{
	/** Joy_Impl
	*/
	class Joy_Impl
	{
	private:

		#if defined(PLATFORM_VCWIN)

		/** 接続。
		*/
		bool connected;

		/** id
		*/
		UINT id;

		/** caps
		*/
		JOYCAPSW caps;

		/** info
		*/
		JOYINFOEX info;

		#endif

	public:

		/** constructor
		*/
		Joy_Impl(s32 a_index);

		/** destructor
		*/
		nonvirtual ~Joy_Impl();

	public:

		/** 更新。
		*/
		void Update();

		/** 接続確認。
		*/
		bool IsConnected() const;

		/** 上。
		*/
		bool Up() const;

		/** 下。
		*/
		bool Down() const;

		/** 左。
		*/
		bool Left() const;

		/** 右。
		*/
		bool Right() const;

	};


}}
#pragma warning(pop)
#endif

