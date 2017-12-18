

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
bool Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,s32 a_line)
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
bool Blib_DebugLog_Callback(const char* a_tag,const char* a_string)
{
	return true;
}
#endif


/** Test_Main
*/
void Test_Main()
{
	STATIC_ASSERT(sizeof(s32) == 4);

	TAGLOG("main","DEF_TEST0");
	TAGLOG("main",L"DEF_TEST0");

	DEBUGLOG("%s%s\n","デバッグ","ログ");	
	DEBUGLOG(L"%s%s\n",L"デバッグ",L"ログ");	

	DEBUGBREAK();

	STLString t_string;
	STACKTRACE(t_string,-1);
	DEBUGLOG("%s\n",t_string.c_str());	

	ASSERT(0);

	return;
}

#endif

