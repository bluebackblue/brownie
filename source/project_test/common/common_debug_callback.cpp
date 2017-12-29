

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
#include "../include.h"
#pragma warning(pop)


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NTest::NCommon
*/
namespace NTest{namespace NCommon
{
	/** LogItem
	*/
	struct LogItem
	{
		wchar buffer[1024];

		#if(BSYS_COLOR_ENABLE)
		NBsys::NColor::Color_F color;
		#endif
	};


	/** s_loglist
	*/
	static LogItem s_loglist[32] = {0};
	static s32 s_loglist_index = 0;
	static s32 s_loglist_write_cur = 0;
	static s32 s_loglist_max = 0;
	static s32 s_loglist_counter = 0;


	/** AddDebugLog
	*/
	#if(BSYS_COLOR_ENABLE)
	static void AddDebugLog(const wchar* a_wstring,const NBsys::NColor::Color_F& a_color)
	#else
	static void AddDebugLog(const wchar* a_wstring)
	#endif
	{
		//ログ総数更新。
		s_loglist_counter++;

		s32 t_read_cur = 0;
		for(;;){
			if((a_wstring[t_read_cur] == L'\n')||(a_wstring[t_read_cur] == 0x0000)){
				s_loglist[s_loglist_index].buffer[s_loglist_write_cur] = 0x0000;

				//改行、終端のある文字の色を採用。
				#if(BSYS_COLOR_ENABLE)
				s_loglist[s_loglist_index].color = a_color;
				#endif

				//改行。
				if(a_wstring[t_read_cur] == L'\n'){
					s_loglist_index = (s_loglist_index + 1) % COUNTOF(s_loglist);

					//ログ最大数更新。
					s_loglist_max++;
					if(s_loglist_max >= COUNTOF(s_loglist) - 1){
						s_loglist_max = COUNTOF(s_loglist) - 1;
					}

					//書き込みカーソルを一番左に。
					s_loglist_write_cur = 0;

					//次のカレントを初期化。
					s_loglist[s_loglist_index].buffer[s_loglist_write_cur] = 0x0000;
					#if(BSYS_COLOR_ENABLE)
					s_loglist[s_loglist_index].color = a_color;
					#endif
				}

				if(a_wstring[t_read_cur] == 0x0000){
					break;
				}
			}else{
				
				if(s_loglist_write_cur < COUNTOF(LogItem::buffer)){
					s_loglist[s_loglist_index].buffer[s_loglist_write_cur] = a_wstring[t_read_cur];
				}else{
					s_loglist[s_loglist_index].buffer[COUNTOF(LogItem::buffer) - 1] = 0x0000;
				}

				s_loglist_write_cur++;
			}

			t_read_cur++;
		}
	}


	/** GetDebugLogString

		0				: 一番古いログ。
		s_loglist_max	: 現在カレントのログ。

	*/
	const wchar* GetDebugLogString(s32 a_index)
	{
		s32 t_index = a_index;

		if(s_loglist_max >= (COUNTOF(s_loglist) - 1)){
			t_index = (COUNTOF(s_loglist) + s_loglist_index + a_index + 1) % COUNTOF(s_loglist);
		}

		return s_loglist[t_index].buffer;
	}

	
	/** GetDegubLogMax
	*/
	s32 GetDegubLogMax()
	{
		return s_loglist_max;
	}


	/** GetDebugLogColor
	*/
	#if(BSYS_COLOR_ENABLE)
	NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index)
	{
		s32 t_index = a_index;

		if(s_loglist_max >= COUNTOF(s_loglist)){
			t_index = (COUNTOF(s_loglist) + a_index + s_loglist_index) % COUNTOF(s_loglist);
		}

		return s_loglist[t_index].color;
	}
	#endif


	/** GetDebugLogCounter
	*/
	s32 GetDebugLogCounter()
	{
		return s_loglist_counter;
	}


}}


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
bool Blib_DebugAssert_Callback(const wchar* a_wmessage,const wchar* a_wfilename,s32 a_line)
{
	wchar t_buffer[COUNTOF(NTest::NCommon::LogItem::buffer)];

	VASTRING(t_buffer,COUNTOF(t_buffer),L"[ASSERT]:%s:%s(%d)",a_wmessage,a_wfilename,a_line);

	NTest::NCommon::AddDebugLog(t_buffer,NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));

	return true;
}
#endif


/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
bool Blib_DebugBreak_Callback()
{
	NTest::NCommon::AddDebugLog(L"DEBUGBREAK();",NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));

	return true;
}
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
bool Blib_DebugLog_Callback(const NBlib::wchar* a_tag,const NBlib::wchar* a_wstring)
{
	wchar t_buffer[COUNTOF(NTest::NCommon::LogItem::buffer)];

	if(a_tag){
		VASTRING(t_buffer,COUNTOF(t_buffer),L"[%s]%s\n",a_tag,a_wstring);
	}else{
		VASTRING(t_buffer,COUNTOF(t_buffer),L"%s",a_wstring);
	}

	NTest::NCommon::AddDebugLog(t_buffer,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));

	return true;
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
void operator delete(void* a_pointer,std::size_t /*a_size*/) noexcept
{
	operator delete(a_pointer,std::nothrow_t());
}


/** 単純な記憶域の解放。例外をスローしない。
*/
void operator delete(void* a_pointer,const std::nothrow_t& /*_*/) noexcept
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
void operator delete[](void* a_pointer,std::size_t /*a_size*/) noexcept
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


#if defined(custom_new)
#define new custom_new
#endif

