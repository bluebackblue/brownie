

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
#if(DEF_TEST_INDEX == 12)


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
static void AddDebugLog(const wchar* a_wstring,const NBsys::NColor::Color_F& a_color)
{
	LogItem& t_logitem = s_loglist[s_loglist_index];

	//文字。
	{
		s32 t_length = Memory::strlen(a_string,COUNTOF(LogItem::buffer) - 1);
		if(t_length <= 0){
			return;
		}

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
const wchar* GetDebugLogString(s32 a_index)
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

/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
bool Blib_DebugAssert_Callback(const wchar* a_wmessage,const wchar* a_wfilename,s32 a_line)
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
bool Blib_DebugLog_Callback(const NBlib::wchar* a_tag,const NBlib::wchar* a_wstring)
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

#if defined(new)
#undef new
#endif

/** 単純な記憶域の確保。確保に失敗した場合bad_alloc例外をスローする。
*/
void* operator new(std::size_t a_size)
{
	void* t_pointer = operator new(a_size,std::nothrow_t());

	if(t_pointer == nullptr){
		throw(std::bad_alloc());
	}

	return t_pointer;
}

/** 単純な記憶域の確保。例外をスローしない。
*/
void* operator new(std::size_t a_size,const std::nothrow_t& /*_*/) noexcept
{
	return std::malloc(a_size);
}

/** 配置newによる記憶域の確保。
*/
#if(0)
void* operator new(std::size_t a_size,void* a_pointer) noexcept
{
}
#endif

/** 単純な記憶域の解放。
*/
void operator delete(void* a_pointer,std::size_t a_size) noexcept
{
	operator delete(a_pointer,std::nothrow_t());
}

/** 単純な記憶域の解放。例外をスローしない。
*/
void operator delete(void* a_pointer,const std::nothrow_t& /**/) noexcept
{
	std::free(a_pointer);
}

/** replacement-newに対応する記憶域の解放。
*/
#if(0)
void operator delete(void* a_pointer,void* /**/) noexcept
{
}
#endif

/** 単純な配列の記憶域の確保。
*/
void* operator new[](std::size_t a_size)
{
	return operator new(a_size);
}

/** 単純な配列の記憶域の確保。例外をスローしない。
*/
void* operator new[](std::size_t a_size,const std::nothrow_t& /*_*/) noexcept
{
	return operator new(a_size,std::nothrow_t());
}

/** 配置newによる配列の記憶域の確保。
*/
#if(0)
void* operator new[](std::size_t a_size,void* a_pointer) noexcept
{
}
#endif

/** 単純な配列の記憶域の解放。
*/
void operator delete[](void* a_pointer,std::size_t a_size) noexcept
{
	operator delete(a_pointer);
}

/** 単純な配列の記憶域の解放。例外をスローしない。
*/
void operator delete[](void* a_pointer,const std::nothrow_t& /*_*/) noexcept
{
	operator delete(a_pointer,std::nothrow_t());
}

/** replacement-newによる配列の記憶域の確保。
*/
#if(0)
void operator delete[](void* a_pointer,void* /*_*/) noexcept
{
}
#endif

#endif

