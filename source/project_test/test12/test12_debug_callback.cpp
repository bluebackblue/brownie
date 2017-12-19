

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
static void AddDebugLog(const char* a_string,const NBsys::NColor::Color_F& a_color)
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

#if defined(new)
#undef new
#endif

void * operator new ( std::size_t size ) throw( std::bad_alloc )
{
    if ( size == 0 ) size = 1 ;

    // Executes a loop: Within the loop,
    while( true )
    {
        // the function first attempts to allocate the requested storage.
        void * ptr = std::malloc( size ) ;

        // if the attempt is successful
        if ( ptr != nullptr )
        {// Returns a pointer to the allocated storage
            return ptr ;
        }

        // Otherwise, 
        std::new_handler handler = std::set_new_handler( nullptr ) ;
        std::set_new_handler( handler ) ;

        // if the argument in the most recent call to set_new_handler() was a null pointer,
        if ( handler == nullptr )
        {// throws bad_alloc.
            throw std::bad_alloc() ;
        }

        // Otherwise, the function calls the current new_handler function.
        handler() ;
        // If the called function returns, the loop repeats.
    }
}

void * operator new( std::size_t size, const std::nothrow_t & ) throw()
{
    try {
        // Calls operator new(size).
        // If the call returns normally, returns the result of that call. 
        return operator new( size ) ;
    } catch( ... )
    {
        // Otherwise, returns a null pointer.
        return nullptr ;
    }
}

void operator delete( void * ptr ) throw()
{
    // If ptr is null, does nothing.(std::free does nothing too)
    // Otherwise, reclaims the storage allocated by the earlier call to operator new.
    std::free( ptr ) ;
}

void operator delete(void * ptr, const std::nothrow_t & ) throw()
{
       // calls operator delete(ptr).
       operator delete( ptr ) ;
}


#endif

