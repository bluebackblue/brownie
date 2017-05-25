

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief インクルード。
*/


/** include
*/
#include "../entry.h"


/** Test0_Main
*/
#if defined(DEF_TEST2)


/** include
*/
#include "./test2_main.h"


/** Test_Main
*/
void Test_Main()
{
	TAGLOG("main","DEF_TEST2");

	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"../../sdk/mmd");

	{
		sharedptr< NBsys::NFile::File_Object > t_pmx(new NBsys::NFile::File_Object(0,L"FL改_レミリア・スカーレット_v2.20/レミリア・スカーレット_2_20.pmx",-1,sharedptr< NBsys::NFile::File_Allocator >(),1));

		while(NBsys::NMmdPmx::Load(t_pmx) == false)
		{
			ThreadSleep(10);
		}

	}

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}

#endif

