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
#include "./windowmenu.h"
#include "./windowmenu_window_base.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** �v���[�g�B
	*/
	class WindowMenu_Window_Area : public WindowMenu_Window_Base
	{
	public:
		/** InitItem
		*/
		struct InitItem : public WindowMenu_Window_Base::InitItem
		{
			/** constructor
			*/
			InitItem()
				:
				WindowMenu_Window_Base::InitItem()
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	public:

	public:
		/** constructor
		*/
		WindowMenu_Window_Area();

		/** destructor
		*/
		virtual ~WindowMenu_Window_Area();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);
	};

}}

