#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#include "../include.h"


/** NCommon
*/
#if(BSYS_PAD_ENABLE)
namespace NCommon
{
	/** Pad_Device
	*/
	class Pad_Device : public NBsys::NPad::Pad_Device_Base
	{
	public:
		/** Type
		*/
		struct Type
		{
			enum Id
			{
				Pad1 = 0,

				Max,
			};
		};

	private:
		/** window
		*/
		sharedptr<NBsys::NWindow::Window> window;

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

		/** mouse_x
		*/
		f32 mouse_x;

		/** mouse_y
		*/
		f32 mouse_y;

		/** mouse_l
		*/
		bool mouse_l;

		/** mouse_r
		*/
		bool mouse_r;

	public:
		/** constructor
		*/
		Pad_Device(sharedptr<NBsys::NWindow::Window>& a_window,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11);

		/** destructor
		*/
		virtual ~Pad_Device();

	public:
		/** デバイスの更新。
		*/
		virtual void DeviceUpdate();
		
		/** ボタン取得。
		*/
		virtual bool GetButton(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::ButtonType::Id a_device_button);

		/** アナログ取得。
		*/
		virtual f32 GetAnalog(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::AnalogType::Id a_device_analog);

		/** タッチ取得。
		*/
		virtual NBsys::NPad::TouchValue GetTouch(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::TouchType::Id a_device_touch);
	};
}
#endif

