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
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../geometry/geometry.h"
#pragma warning(pop)


/** include
*/
#include "./pad_touchvalue.h"


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
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

		/** デバイスの更新。
		*/
		virtual void DeviceUpdate() = 0;

		/** ボタン取得。
		*/
		virtual bool GetButton(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::ButtonType::Id a_device_button) const = 0;

		/** アナログ取得。
		*/
		virtual f32 GetAnalog(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::AnalogType::Id a_device_analog) const = 0;

		/** タッチ取得。
		*/
		virtual TouchValue GetTouch(s32 a_virtualpad_index,NBsys::NPad::Pad_Device_Base::TouchType::Id a_device_touch) const = 0;

	};


}}
#pragma warning(pop)
#endif

