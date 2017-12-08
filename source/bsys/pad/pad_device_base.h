#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�b�h�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../geometry/geometry.h"
#include "./pad_touchvalue.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** Pad_Device_Base
	*/
	class Pad_Device_Base
	{
	public:
		/** constructor
		*/
		Pad_Device_Base()
		{
		}

		/** destructor
		*/
		virtual ~Pad_Device_Base()
		{
		}

	public:
		/** ButtonType
		*/
		struct ButtonType
		{
			enum Id
			{
				None = 0,

				DeviceButton_1,
				DeviceButton_2,
				DeviceButton_3,
				DeviceButton_4,
				DeviceButton_5,
				DeviceButton_6,
				DeviceButton_7,
				DeviceButton_8,
				DeviceButton_9,
				DeviceButton_10,
				DeviceButton_11,
				DeviceButton_12,
				DeviceButton_13,
				DeviceButton_14,
				DeviceButton_15,

				Max,
			};
		};

		/** AnalogType
		*/
		struct AnalogType
		{
			enum Id
			{
				None = 0,

				DeviceAnalog_1,
				DeviceAnalog_2,
				DeviceAnalog_3,
				DeviceAnalog_4,
				DeviceAnalog_5,
				DeviceAnalog_6,
				DeviceAnalog_7,
				DeviceAnalog_8,
				DeviceAnalog_9,
				DeviceAnalog_10,

				Max,
			};
		};

		/** TouchType
		*/
		struct TouchType
		{
			enum Id
			{
				None = 0,

				DeviceTouch_1,
				DeviceTouch_2,
				DeviceTouch_3,
				DeviceTouch_4,
				DeviceTouch_5,
				DeviceTouch_6,
				DeviceTouch_7,
				DeviceTouch_8,
				DeviceTouch_9,
				DeviceTouch_10,

				Max,
			};
		};

	public:
		/** �f�o�C�X�̍X�V�B
		*/
		virtual void DeviceUpdate() = 0;

		/** �{�^���擾�B
		*/
		virtual bool GetButton(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::ButtonType::Id a_device_button) = 0;

		/** �A�i���O�擾�B
		*/
		virtual f32 GetAnalog(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::AnalogType::Id a_device_analog) = 0;

		/** �^�b�`�擾�B
		*/
		virtual TouchValue GetTouch(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::TouchType::Id a_device_touch) = 0;
	};
}}

