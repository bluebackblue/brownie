#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�o�b�O���j���[�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../color/color.h"


/** include
*/
#include "./debugmenu_callback_base.h"
#include "./debugmenu_window_base.h"
#include "./debugmenu_window_plate.h"
/*
#include "./debugmenu_window_button.h"
#include "./debugmenu_window_separate.h"
#include "./debugmenu_window_dragtitle.h"
*/


/** NBsys::NDebugMenu
*/
#if(BSYS_DEBUGMENU_ENABLE)
namespace NBsys{namespace NDebugMenu
{
	/** DebugMenu
	*/
	class DebugMenu
	{
	public:
		/** callback
		*/
		sharedptr<DebugMenu_Callback_Base> callback;

		/** list
		*/
		STLList<sharedptr<DebugMenu_Window_Base>>::Type list;

	public:
		/** constructor
		*/
		DebugMenu(sharedptr<DebugMenu_Callback_Base>& a_callback);

		/** destructor
		*/
		nonvirtual ~DebugMenu();

	public:
		/** Update
		*/
		void Update();

		/** Draw
		*/
		void Draw();

	public:
		/** �ǉ��B
		*/
		void Add(const sharedptr<DebugMenu_Window_Base>& a_window);

	};

	/** �V�X�e���̊J�n�B
	*/
	void StartSystem(sharedptr<DebugMenu_Callback_Base>& a_callback);

	/** �V�X�e���̏I���B
	*/
	void EndSystem();

	/** �V�X�e���̃C���X�^���X�擾�B
	*/
	sharedptr<DebugMenu>& GetSystemInstance();

}}
#endif

