#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パフォーマンスカウンター。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{
	/** PerformanceCounter
	*/
	class PerformanceCounter
	{
	public:

		/** [static]「BootInitialize」から呼び出される。
		*/
		static void InitPerformanceCounter();

		/** [static]GetPerformanceCounter
		*/
		static u64 GetPerformanceCounter();

		/** [static]１秒に必要なカウント数を取得。
		*/
		static u64 GetPerformanceSecCounter();

		/** [static]１マイクロ秒に必要なカウント数を取得。
		*/
		static u64 GetPerformanceMicroSecCounter();

	};


}

