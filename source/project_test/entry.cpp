

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


/** include
*/
#include "./test0/test0_main.h"
#include "./test1/test1_main.h"
#include "./test2/test2_main.h"

#include "./test10/test10_main.h"
#include "./test11/test11_main.h"
#include "./test12/test12_main.h"

#include "./test22/test22_main.h"


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
void main(int a_argc,char** a_argv)
{
	#if defined(PLATFORM_VCWIN)
	#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
	if(s_leakcheck == false){
		s_leakcheck = true;
		::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF);
	}
	#endif
	#endif

	if(NBlib::IsBootInitialize() == false){
		NBlib::BootInitialize();
	}

	try{
		Test_Main();
	}catch(...){
		DEBUGBREAK();
	}
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

	if(NBlib::IsBootInitialize() == false){
		NBlib::BootInitialize();
	}

	GetEntryParamReference().hinstance = a_hinstance;

	main(__argc,__argv);

	return 0;
}
#endif

