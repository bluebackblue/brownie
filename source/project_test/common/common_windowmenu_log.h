#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �e�X�g�B
*/


/** include
*/
#include "../include.h"


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** Common_WindowMenu_Log
	*/
	class Common_WindowMenu_Log : public NBsys::NWindowMenu::WindowMenu_Window_Base
	{
	private:

		/** endrequest
		*/
		bool endrequest;

		/** logtext
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> window_logtext[16];

		/** debuglog_counter
		*/
		s32 debuglog_counter;

	public:

		/** constructor
		*/
		Common_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y);

		/** destructor
		*/
		virtual ~Common_WindowMenu_Log();

	public:

		/** �폜���N�G�X�g�B�擾�B
		*/
		virtual bool CallBack_GetDeleteRequest();

		/** �폜���N�G�X�g�B�ݒ�B
		*/
		virtual void CallBack_SetDeleteRequest();

		/** �X�V�����B
		*/
		virtual void CallBack_Update();

	};


}}
#endif

