#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest::NCommon
*/
#if(BSYS_PAD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NTest{namespace NCommon
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

		/** mouse_pos
		*/
		Position2DType<f32> mouse_pos;

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
		virtual bool GetButton(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::ButtonType::Id a_device_button) const;

		/** アナログ取得。
		*/
		virtual f32 GetAnalog(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::AnalogType::Id a_device_analog) const;

		/** タッチ取得。
		*/
		virtual NBsys::NPad::TouchValue GetTouch(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::TouchType::Id a_device_touch) const;

	};


}}
#pragma warning(pop)
#endif

