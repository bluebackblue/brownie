

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
#if(DEF_TEST_INDEX == 3)


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

	t_window->Delete();
	t_window.reset();

	return;
}

#endif

