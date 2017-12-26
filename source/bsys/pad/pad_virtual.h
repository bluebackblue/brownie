#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./pad_device_base.h"
#include "./pad_touchvalue.h"


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
namespace NBsys{namespace NPad
{
	/** Pad_Virtual
	*/
	class Pad_Virtual
	{
	public:

		/** constructor
		*/
		Pad_Virtual(s32 a_virtualpad_index);

		/** destructor
		*/
		virtual ~Pad_Virtual();

	public:

		/** ButtonType
		*/
		struct ButtonType
		{
			enum Id
			{
				None,

				X,
				Y,
				A,
				B,

				L,
				R,

				UP,
				DOWN,
				LEFT,
				RIGHT,

				START,
				ENTER,

				CTRL,
				SHIFT,

				MOUSEL,
				MOUSER,

				Max,
			};
		};

		/** AnalogType
		*/
		struct AnalogType
		{
			enum Id
			{
				None,

				LX,
				LY,
				RX,
				RY,

				Max,
			};
		};

		/** TouchType
		*/
		struct TouchType
		{
			enum Id
			{
				None,

				A,
				B,
				C,
				D,
				
				MOUSEL,
				MOUSER,

				Max,
			};
		};

	private:

		/** ButtonItem
		*/
		struct ButtonItem
		{
			Pad_Virtual::ButtonType::Id virtual_button;
			Pad_Device_Base::ButtonType::Id device_button;
			sharedptr<Pad_Device_Base> device;
		};

		/** AnalogItem
		*/
		struct AnalogItem
		{
			Pad_Virtual::AnalogType::Id virtual_analog;
			Pad_Device_Base::AnalogType::Id device_analog;
			sharedptr<Pad_Device_Base> device;
		};

		/** TouchItem
		*/
		struct TouchItem
		{
			Pad_Virtual::TouchType::Id virtual_touch;
			Pad_Device_Base::TouchType::Id device_touch;
			sharedptr<Pad_Device_Base> device;
		};

	private:

		/** virtualpad_index
		*/
		s32 virtualpad_index;

		/** enable
		*/
		bool enable;

		/** repeat
		*/
		s32 repeat_loopstart;
		s32 repeat_loopend;

		/** list_button
		*/
		STLList<ButtonItem>::Type list_button;

		/** list_analog
		*/
		STLList<AnalogItem>::Type list_analog;

		/** list_touch
		*/
		STLList<TouchItem>::Type list_touch;

		/** button
		*/
		bool button[ButtonType::Max];
		bool button_old[ButtonType::Max];
		s32  button_repeat[ButtonType::Max];

		/** analog
		*/
		f32 analog[AnalogType::Max];

		/** touch
		*/
		TouchValue touch[TouchType::Max];
		bool touch_flag_old[TouchType::Max];
		s32 touch_flag_repeat[TouchType::Max];

	public:

		/** AddButton
		*/
		void AddButton(Pad_Virtual::ButtonType::Id a_virtual_button,Pad_Device_Base::ButtonType::Id a_device_button,sharedptr<Pad_Device_Base> a_device);

		/** AddAnalog
		*/
		void AddAnalog(Pad_Virtual::AnalogType::Id a_virtual_analog,Pad_Device_Base::AnalogType::Id a_device_analog,sharedptr<Pad_Device_Base> a_device);

		/** AddTouch
		*/
		void AddTouch(Pad_Virtual::TouchType::Id a_virtual_touch,Pad_Device_Base::TouchType::Id a_device_touch,sharedptr<Pad_Device_Base> a_device);

		/** SetButton
		*/
		void SetButton(Pad_Virtual::ButtonType::Id a_virtual_button,Pad_Device_Base::ButtonType::Id a_device_button,sharedptr<Pad_Device_Base> a_device);

		/** SetAnalog
		*/
		void SetAnalog(Pad_Virtual::AnalogType::Id a_virtual_analog,Pad_Device_Base::AnalogType::Id a_device_analog,sharedptr<Pad_Device_Base> a_device);

		/** SetTouch
		*/
		void SetTouch(Pad_Virtual::TouchType::Id a_virtual_touch,Pad_Device_Base::TouchType::Id a_device_touch,sharedptr<Pad_Device_Base> a_device);

		/** Update
		*/
		void Update();

		/** SetEnable
		*/
		void SetEnable(bool a_flag);

		/** IsButtonOn
		*/
		bool IsButtonOn(Pad_Virtual::ButtonType::Id a_virtual_button) const;

		/** IsButtonDown
		*/
		bool IsButtonDown(Pad_Virtual::ButtonType::Id a_virtual_button) const;

		/** IsButtonUp
		*/
		bool IsButtonUp(Pad_Virtual::ButtonType::Id a_virtual_button) const;

		/** IsButtonRepeat
		*/
		bool IsButtonRepeat(Pad_Virtual::ButtonType::Id a_virtual_button) const;

		/** GetAnalogValue
		*/
		f32 GetAnalogValue(Pad_Virtual::AnalogType::Id a_virtual_analog) const;

		/** IsTouchDown
		*/
		bool IsTouchDown(Pad_Virtual::TouchType::Id a_virtual_touch) const;

		/** IsTouchOn
		*/
		bool IsTouchOn(Pad_Virtual::TouchType::Id a_virtual_touch) const;

		/** GetTouchValue
		*/
		const TouchValue& GetTouchValue(Pad_Virtual::TouchType::Id a_virtual_touch) const;

	};


}}
#endif

