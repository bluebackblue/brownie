

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
#include "../entry.h"
#pragma warning(pop)


/** NTest
*/
#if(DEF_TEST_INDEX == 3)
namespace NTest
{
	/** Test_Main
	*/
	void Test_Main()
	{
		//ウィンドウ作成。
		sharedptr<NBsys::NWindow::Window> t_window(new NBsys::NWindow::Window());
		t_window->Create(L"TEST " DEF_TEST_STRING,100,100);

		while(true){
			//s_window
			t_window->Update();
			if(t_window->IsEnd() == true){
				break;
			}
		}

		//ウィンドウ削除。
		t_window->Delete();
		t_window.reset();

		return;
	}


}
#endif

