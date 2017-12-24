﻿

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief エントリー。
*/


/** include
*/
#include "./include.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** Test_Main
*/
void Test_Main();


/** include
*/
#include "./entry.h"


/** FileAllocator
*/
class FileAllocator : public NBsys::NFile::File_Allocator
{
public:
	virtual void* Alloc(u32 a_size)
	{
		return new u8[a_size];
	}
	virtual void Free(void* a_pointer)
	{
		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}
};


/** GetEntryParamReference
*/
EntryParam& GetEntryParamReference()
{
	static EntryParam s_entryparam;
	return s_entryparam;
}

#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
bool s_leakcheck = false;
#endif


/** Main
*/
#if defined(PLATFORM_VCWIN)
void main(int a_argc,char** a_argv)
#elif defined(PLATFORM_GNUCWIN)
int main(int a_argc,char** a_argv)
#endif
{
	#if defined(PLATFORM_VCWIN)
	#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
	if(s_leakcheck == false){
		s_leakcheck = true;
		::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	}
	#endif
	#endif

	sharedptr<Blib> t_blib;
	if(NBlib::IsBootInitialize() == false){
		t_blib = NBlib::BootInitialize();
	}

	#if(DEF_TEST_AUTO)
	{
		try{
			Test_Main();
		}catch(...){
			//DEBUGBREAK();
		}
	}
	#else
	{
		Test_Main();
	}
	#endif

	#if defined(PLATFORM_GNUCWIN)
	return 0;
	#endif
}


/** WinMain
*/
#if defined(PLATFORM_VCWIN)
int WINAPI WinMain(_In_ HINSTANCE a_hinstance,_In_opt_ HINSTANCE /*a_prev_hinstance*/,_In_ LPSTR a_commandline,_In_ int a_cmdshow)
{
	#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
	if(s_leakcheck == false){
		s_leakcheck = true;
		::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	}
	#endif

	sharedptr<Blib> t_blib;
	if(NBlib::IsBootInitialize() == false){
		t_blib = NBlib::BootInitialize();
	}

	GetEntryParamReference().hinstance = a_hinstance;

	main(__argc,__argv);

	return 0;
}
#endif

