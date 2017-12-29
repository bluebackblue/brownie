

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


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../bsys/window/window_impl.h"
#pragma warning(pop)


/** include
*/
#include "./common_pad_device.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** VK
*/
#if defined(PLATFORM_VCWIN)
	#define VK_A	0x41
	#define VK_B	0x42
	#define VK_C	0x43
	#define VK_D	0x44
	#define VK_E	0x45
	#define VK_F	0x46
	#define VK_G	0x47
	#define VK_H	0x48
	#define VK_I	0x49
	#define VK_J	0x4A
	#define VK_K	0x4B
	#define VK_L	0x4C
	#define VK_M	0x4D
	#define VK_N	0x4E
	#define VK_O	0x4F
	#define VK_P	0x50
	#define VK_Q	0x51
	#define VK_R	0x52
	#define VK_S	0x53
	#define VK_T	0x54
	#define VK_U	0x55
	#define VK_V	0x56
	#define VK_W	0x57
	#define VK_X	0x58
	#define VK_Y	0x59
	#define VK_Z	0x50
#endif


/** NTest::NCommon
*/
#if(BSYS_PAD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NTest{namespace NCommon
{
	/** constructor
	*/
	Pad_Device::Pad_Device(sharedptr<NBsys::NWindow::Window>& a_window,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
		:
		window(a_window),
		d3d11(a_d3d11),
		mouse_x(0.0f),
		mouse_y(0.0f),
		mouse_l(false),
		mouse_r(false)
	{
	}

	/** destructor
	*/
	Pad_Device::~Pad_Device()
	{
	}

	/** デバイスの更新。
	*/
	void Pad_Device::DeviceUpdate()
	{
		this->mouse_x = static_cast<f32>(this->window->GetImpl()->GetMouseX() * this->d3d11->GetWidth()) / this->window->GetImpl()->GetClientWidth();
		this->mouse_y = static_cast<f32>(this->window->GetImpl()->GetMouseY() * this->d3d11->GetHeight()) / this->window->GetImpl()->GetClientHeight();

		this->mouse_l = false;
		#if defined(PLATFORM_VCWIN)
		if(::GetAsyncKeyState(VK_LBUTTON) != 0){
			this->mouse_l = true;
		}
		#endif

		this->mouse_r = false;
		#if defined(PLATFORM_VCWIN)
		if(::GetAsyncKeyState(VK_RBUTTON) != 0){
			this->mouse_r = true;
		}
		#endif
	}

	/** ボタン取得。
	*/
	bool Pad_Device::GetButton(s32 /*a_virtualpad_index*/,NBsys::NPad::Pad_Device_Base::ButtonType::Id a_device_button) const
	{
		switch(a_device_button){
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_14:
			{
				//mouse l
				return this->mouse_l;
			}break;
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_15:
			{
				//mouse r
				return this->mouse_r;
			}break;
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_1:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_2:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_3:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_4:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_5:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_6:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_7:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_8:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_9:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_10:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_11:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_12:
		case NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_13:
		case NBsys::NPad::Pad_Device_Base::ButtonType::None:
		case NBsys::NPad::Pad_Device_Base::ButtonType::Max:
		default:
			{
			}break;
		}

		return false;
	}

	/** アナログ取得。
	*/
	f32 Pad_Device::GetAnalog(s32 /*a_virtualpad_index*/,NBsys::NPad::Pad_Device_Base::AnalogType::Id /*a_device_analog*/) const
	{
		return 0.0f;
	}

	/** タッチ取得。
	*/
	NBsys::NPad::TouchValue Pad_Device::GetTouch(s32 /*a_virtualpad_index*/,NBsys::NPad::Pad_Device_Base::TouchType::Id a_device_touch) const
	{
		switch(a_device_touch){
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_1:
			{
				//mouse l

				return NBsys::NPad::TouchValue(this->mouse_x,this->mouse_y,this->mouse_l);
			}break;
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_2:
			{
				//mouse r

				return NBsys::NPad::TouchValue(this->mouse_x,this->mouse_y,this->mouse_r);
			}break;
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_3:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_4:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_5:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_6:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_7:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_8:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_9:
		case NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_10:
		case NBsys::NPad::Pad_Device_Base::TouchType::Max:
		case NBsys::NPad::Pad_Device_Base::TouchType::None:
			{
			}break;
		}

		return NBsys::NPad::TouchValue::Zero();
	}
}}
#pragma warning(pop)
#endif

