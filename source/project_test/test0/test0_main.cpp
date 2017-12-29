

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(DEF_TEST_INDEX == 0)
namespace NTest
{
	/** Test_Main
	*/
	void Test_Main()
	{
		//コンパイル時アサート。
		STATIC_ASSERT(sizeof(s32) == 4);

		//タグログ。
		TAGLOG(L"main",u8"テスト");
		TAGLOG(L"main",L"テスト");

		//デバッグログ。
		DEBUGLOG(u8"%s%s\n",u8"デバッグ",u8"ログ");	
		DEBUGLOG(L"%s%s\n",L"デバッグ",L"ログ");	

		//デバッグブレイク。
		DEBUGBREAK();

		//スタックトレース。
		{
			STLString t_stacktrace;
			STACKTRACE(t_stacktrace,-1);
			DEBUGLOG(u8"%s\n",t_stacktrace.c_str());	
		}

		//アサート。
		ASSERT(0);

		return;
	}


}
#endif

