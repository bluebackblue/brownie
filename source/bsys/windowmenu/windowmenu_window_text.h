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
	/** �e�L�X�g�B
	*/
	class WindowMenu_Window_Text: public WindowMenu_Window_Base
	{
	public:
		/** InitItem
		*/
		struct InitItem
		{
			/** mode
			*/
			WindowMenu_Mode::Id mode;

			/** name
			*/
			STLString name;
			
			/** offset
			*/
			WindowMenu_Offset offset;
			
			/** size
			*/
			WindowMenu_Size size;

			/** �F�B
			*/
			NBsys::NColor::Color_F color;

			/** �����B
			*/
			STLWString string;

			/** constructor
			*/
			InitItem(WindowMenu_Mode::Id a_mode,const STLString& a_name,const WindowMenu_Offset& a_offset,const WindowMenu_Size& a_size)
				:
				mode(a_mode),
				name(a_name),
				offset(a_offset),
				size(a_size)
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	public:
		/** color
		*/
		NBsys::NColor::Color_F color;

		/** string
		*/
		STLWString string;

	public:
		/** constructor
		*/
		WindowMenu_Window_Text(const InitItem& a_inititem);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Text();

		/** �`�揈���B
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

	};

}}

