

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


/** s_loglist
*/
struct LogItem
{
	char buffer[1024];
	NBsys::NColor::Color_F color;
};


static LogItem s_loglist[16];
static s32 s_loglist_index = 0;
static s32 s_loglist_max = 0;
static s32 s_loglist_counter = 0;


/** AddDebugLog
*/
static void AddDebugLog(const char* a_string,const NBsys::NColor::Color_F& a_color)
{
	LogItem& t_logitem = s_loglist[s_loglist_index];

	//文字。
	{
		s32 t_length = Memory::strlen(a_string,COUNTOF(LogItem::buffer) - 1);
		Memory::memcpy(&t_logitem.buffer[0],sizeof(t_logitem.buffer),a_string,t_length);
		t_logitem.buffer[t_length] = 0;
	}

	//色。
	{
		t_logitem.color = a_color;
	}

	//インクリメント。
	{
		s_loglist_index = (s_loglist_index + 1) % COUNTOF(s_loglist);
		s_loglist_max++;
		if(s_loglist_max >= COUNTOF(s_loglist)){
			s_loglist_max = COUNTOF(s_loglist);
		}

		s_loglist_counter++;
	}
}


/** GetDebugLogString
*/
const char* GetDebugLogString(s32 a_index)
{
	s32 t_index = a_index;

	if(s_loglist_max >= COUNTOF(s_loglist)){
		t_index = (COUNTOF(s_loglist) + a_index + s_loglist_index) % COUNTOF(s_loglist);
	}

	return s_loglist[t_index].buffer;
}


/** GetDebugLogColor
*/
NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index)
{
	s32 t_index = a_index;

	if(s_loglist_max >= COUNTOF(s_loglist)){
		t_index = (COUNTOF(s_loglist) + a_index + s_loglist_index) % COUNTOF(s_loglist);
	}

	return s_loglist[t_index].color;
}


/** GetDebugLogCounter
*/
s32 GetDebugLogCounter()
{
	return s_loglist_counter;
}

/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
bool Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,s32 a_line)
{
	char t_buffer[COUNTOF(LogItem::buffer)];
	s32 t_buffer_offset = 0;
	VASTRING(t_buffer,COUNTOF(t_buffer),"[ASSERT]:%s:%s(%d)",a_message,a_filename,a_line);
	AddDebugLog(t_buffer,NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));

	return true;
}
#endif

/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
bool Blib_DebugBreak_Callback()
{
	AddDebugLog("DEBUGBREAK();",NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));

	return true;
}
#endif

/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
bool Blib_DebugLog_Callback(const char* a_tag,const char* a_string)
{
	char t_buffer[COUNTOF(LogItem::buffer)];
	s32 t_buffer_offset = 0;

	if(a_tag){
		VASTRING(t_buffer,COUNTOF(t_buffer),"[%s]%s",a_tag,a_string);
	}else{
		VASTRING(t_buffer,COUNTOF(t_buffer),"%s",a_string);
	}

	AddDebugLog(t_buffer,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));

	return false;
}
#endif

#endif

