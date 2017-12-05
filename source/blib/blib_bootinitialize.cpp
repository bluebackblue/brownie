

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �������B
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


/** NBlib
*/
namespace NBlib
{

	/** �������ς݃t���O�B
	*/
	static bool s_is_boot_initialize = false;

	/** �O���[�o���Œ蒷�A���P�[�^�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	static GlobalFixedAllocator_Type s_globalfixedallocator;
	#endif

	/** �O���[�o���Œ蒷�A���P�[�^�B���b�N�I�u�W�F�N�g�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	static LockObject s_globalfixedallocator_lockobject;
	#endif

	/** �O���[�o�������B
	*/
	static RandomTemplate<Random_LinearCongruentialGenerators> s_globalrand;

	/** �O���[�o�������B���b�N�I�u�W�F�N�g�B
	*/
	static LockObject s_globalrand_lockobject;


	/** �N�����������B
	*/
	void BootInitialize()
	{
		//�O���[�o���Œ蒷�A���P�[�^�̏������B
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		{
			AutoLock t_autolock(s_globalfixedallocator_lockobject);
			s_globalfixedallocator.Reset();
		}
		#endif

		Math::Initialize();

		{
			#if defined(PLATFORM_VCWIN)
			{
				TAGLOG("blib","platform = PLATFORM_VCWIN");
			}
			#else
			{
				TAGLOG("blib","platform = PLATFORM_XX");
			}
			#endif
		}

		{
			#if defined(ROM_MASTER)
			{
				TAGLOG("blib","rom = ROM_MASTER");
			}
			#elif defined(ROM_DEVELOP)
			{
				TAGLOG("blib","rom = ROM_DEVELOP");
			}
			#elif defined(ROM_DEEPDEBUG)
			{
				TAGLOG("blib","rom = ROM_DEEPDEBUG");
			}
			#elif defined(ROM_FULLDEBUG)
			{
				TAGLOG("blib","rom = ROM_FULLDEBUG");
			}
			#else
			{
				TAGLOG("blib","rom = ROM_XX");
			}
			#endif
		}

		{
			#if defined(ROM_64BIT)
			{
				TAGLOG("blib","ROM_64BIT");
			}
			#elif defined(ROM_32BIT)
			{
				TAGLOG("blib","ROM_32BIT");
			}
			#else
			{
				TAGLOG("blib","ROM_XXBIT");
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
			TAGLOG("blib","{0xFF,0x00,0x00,0x00} == 0x000000FF : little endian");
		}else{
			//big endian
			TAGLOG("blib","{0xFF,0x00,0x00,0x00} == 0xFF000000 : big endian");
		}

		PerformanceCounter::InitPerformanceCounter();

		{
			AutoLock t_autolock(s_globalrand_lockobject);
			s_globalrand.SetSeedFromDevice();
		}

		s_is_boot_initialize = true;
	}

	/** �������ς݂��ǂ����B
	*/
	bool IsBootInitialize()
	{
		return s_is_boot_initialize;
	}

	/** �O���[�o���Œ蒷�A���P�[�^�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	GlobalFixedAllocator_Type& GlobalFixedAllocator_Get()
	{
		return s_globalfixedallocator;
	}
	#endif

	/** �O���[�o���Œ蒷�A���P�[�^�B���b�N�I�u�W�F�N�g�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	LockObject& GlobalFixedAllocator_LockObject()
	{
		return s_globalfixedallocator_lockobject;
	}
	#endif

	/** �O���[�o�������B
	*/
	RandomTemplate<Random_LinearCongruentialGenerators>& GlobalRand_Get()
	{
		return s_globalrand;
	}

	/** �O���[�o�������B���b�N�I�u�W�F�N�g�B
	*/
	LockObject& GlobalRand_LockObject()
	{
		return s_globalrand_lockobject;
	}

}

