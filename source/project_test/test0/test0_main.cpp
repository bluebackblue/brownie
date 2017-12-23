

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST_INDEX
*/
#if(DEF_TEST_INDEX == 0)


/** include
*/
#include "./test0_main.h"


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
bool Blib_DebugAssert_Callback(const wchar* a_wmessage,const wchar* a_wfilename,s32 a_line)
{
	return true;
}
#endif


/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
bool Blib_DebugBreak_Callback()
{
	return true;
}
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
bool Blib_DebugLog_Callback(const NBlib::wchar* a_tag,const NBlib::wchar* a_wstring)
{
	return true;
}
#endif


/** Test_Main
*/
void Test_Main()
{
	std::unordered_map<Key,s32> list;


	STATIC_ASSERT(sizeof(s32) == 4);

	TAGLOG(L"main",u8"テスト");
	TAGLOG(L"main",L"テスト");

	DEBUGLOG(u8"%s%s\n",u8"デバッグ",u8"ログ");	
	DEBUGLOG(L"%s%s\n",L"デバッグ",L"ログ");	

	DEBUGBREAK();

	STLString t_string;
	STACKTRACE(t_string,-1);
	DEBUGLOG(u8"%s\n",t_string.c_str());	

	ASSERT(0);

	return;
}

#endif

