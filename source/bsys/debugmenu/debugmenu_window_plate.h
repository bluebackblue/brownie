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
#include "./debugmenu.h"
#include "./debugmenu_window_base.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** �v���[�g�B
	*/
	class DebugMenu_Window_Plate : public DebugMenu_Window_Base
	{
	public:
		/** constructor
		*/
		DebugMenu_Window_Plate(DebugMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z);

		/** destructor
		*/
		virtual ~DebugMenu_Window_Plate();

		/** Draw
		*/
		virtual void Draw();
	};

}}

