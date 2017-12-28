

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 初期化。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./fixedallocator.h"
#include "./lockobject.h"
#include "./autolock.h"
#include "./debuglog.h"
#include "./performancecounter.h"
#include "./random.h"
#include "./blib_bootinitialize.h"
#include "./math.h"
#include "./sharedptr.h"


/** NBlib
*/
namespace NBlib
{
	/** 初期化済みフラグ。
	*/
	static bool s_is_boot_initialize = false;


	/** グローバル固定長アロケータ。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	static GlobalFixedAllocator_Type s_globalfixedallocator;
	#endif


	/** グローバル固定長アロケータ。ロックオブジェクト。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	static LockObject s_globalfixedallocator_lockobject;
	#endif


	/** グローバル乱数。
	*/
	static RandomTemplate<Random_LinearCongruentialGenerators> s_globalrand;


	/** グローバル乱数。ロックオブジェクト。
	*/
	static LockObject s_globalrand_lockobject;


	/** インスｋタンス。
	*/
	static weakptr<Blib> s_instance;


	/** constructor
	*/
	Blib::Blib()
		:
		call_list()
	{
	}


	/** destructor
	*/
	nonvirtual Blib::~Blib()
	{
		auto t_it_end = this->call_list.cend();
		for(auto t_it = this->call_list.cbegin();t_it!=t_it_end;++t_it){
			(*t_it)();
		}
		this->call_list.clear();
	}


	/** 起動時初期化。
	*/
	sharedptr<Blib> BootInitialize()
	{
		//グローバル固定長アロケータの初期化。
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		{
			AutoLock t_autolock(s_globalfixedallocator_lockobject);
			s_globalfixedallocator.Reset();
		}
		#endif

		//ログを表示するまえに。
		s_is_boot_initialize = true;

		//インスタンス作成。
		sharedptr<Blib> t_instance(new Blib());
		s_instance = t_instance;

		Math::Initialize();

		{
			#if defined(PLATFORM_VCWIN)
			{
				TAGLOG(L"blib",L"platform = PLATFORM_VCWIN");
			}
			#elif defined(PLATFORM_GNUCWIN)
			{
				TAGLOG(L"blib",L"platform = PLATFORM_GNUCWIN");			
			}
			#else
			{
				#warning
			}
			#endif
		}

		{
			#if defined(ROM_MASTER)
			{
				TAGLOG(L"blib",L"rom = ROM_MASTER");
			}
			#elif defined(ROM_DEVELOP)
			{
				TAGLOG(L"blib",L"rom = ROM_DEVELOP");
			}
			#elif defined(ROM_DEEPDEBUG)
			{
				TAGLOG(L"blib",L"rom = ROM_DEEPDEBUG");
			}
			#elif defined(ROM_FULLDEBUG)
			{
				TAGLOG(L"blib",L"rom = ROM_FULLDEBUG");
			}
			#else
			{
				#warning
			}
			#endif
		}

		{
			#if defined(ROM_64BIT)
			{
				TAGLOG(L"blib",L"ROM_64BIT");
			}
			#elif defined(ROM_32BIT)
			{
				TAGLOG(L"blib",L"ROM_32BIT");
			}
			#else
			{
				#warning
			}
			#endif
		}

		u32 t_list_form = 0x00000000;
		(reinterpret_cast<u8*>(&t_list_form))[0] = 0xFF;
		(reinterpret_cast<u8*>(&t_list_form))[1] = 0x00;
		(reinterpret_cast<u8*>(&t_list_form))[2] = 0x00;
		(reinterpret_cast<u8*>(&t_list_form))[3] = 0x00;

		if(t_list_form == 0x000000FF){
			//little endian
			TAGLOG(L"blib",L"{0xFF,0x00,0x00,0x00} == 0x000000FF : little endian");
		}else{
			//big endian
			TAGLOG(L"blib",L"{0xFF,0x00,0x00,0x00} == 0xFF000000 : big endian");
		}

		PerformanceCounter::InitPerformanceCounter();

		{
			AutoLock t_autolock(s_globalrand_lockobject);
			s_globalrand.SetSeedFromDevice();
		}

		return t_instance;
	}


	/** 初期化済みかどうか。
	*/
	bool IsBootInitialize()
	{
		return s_is_boot_initialize;
	}


	/** 終了時に呼び出す。
	*/
	void CallOnExit(const std::function<void(void)>& a_function)
	{
		sharedptr<Blib> t_instance = s_instance;
		if(t_instance){
			t_instance->call_list.push_back(a_function);
		}
	}


	/** グローバル固定長アロケータ。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	GlobalFixedAllocator_Type& GlobalFixedAllocator_Get()
	{
		return s_globalfixedallocator;
	}
	#endif


	/** グローバル固定長アロケータ。ロックオブジェクト。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	LockObject& GlobalFixedAllocator_LockObject()
	{
		return s_globalfixedallocator_lockobject;
	}
	#endif


	/** グローバル乱数。
	*/
	RandomTemplate<Random_LinearCongruentialGenerators>& GlobalRand_Get()
	{
		return s_globalrand;
	}


	/** グローバル乱数。ロックオブジェクト。
	*/
	LockObject& GlobalRand_LockObject()
	{
		return s_globalrand_lockobject;
	}


}

