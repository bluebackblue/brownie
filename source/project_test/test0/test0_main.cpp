

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �C���N���[�h�B
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST0
*/
#if defined(DEF_TEST0)


/** include
*/
#include "./test0_main.h"


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
void Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,s32 a_line)
{
}
#endif


/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
void Blib_DebugBreak_Callback()
{
}
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
void Blib_DebugLog_Callback(const char* a_tag,const char* a_string)
{
}
#endif


/** Test_Main
*/
void Test_Main()
{
	STATIC_ASSERT(sizeof(s32) == 4);

	TAGLOG("main","DEF_TEST0");
	TAGLOG("main",L"DEF_TEST0");

	DEBUGLOG("%s%s\n","�f�o�b�O","���O");	
	DEBUGLOG(L"%s%s\n",L"�f�o�b�O",L"���O");	

	DEBUGBREAK();

	STLString t_string;
	STACKTRACE(t_string,-1);
	DEBUGLOG("%s\n",t_string.c_str());	

	ASSERT(0);

	return;
}

#endif

