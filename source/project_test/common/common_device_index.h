#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 自動テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest
*/
#pragma warning(push)
#pragma warning(disable:4710)
namespace NTest{namespace NCommon
{
	/** DeviceIndex
	*/
	struct DeviceIndex
	{
		enum Id
		{
			/** project_test/test + DEF_TEST_STRING
			*/
			Local = 0,

			/** project_test/common
			*/
			Common,

			/** sdk
			*/
			Sdk,

			/** brownie_testdata/data
			*/
			TestData,

			Max,
		};
	};


}}
#pragma warning(pop)

