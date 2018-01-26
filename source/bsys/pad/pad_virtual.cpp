

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./pad_virtual.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBsys{namespace NPad
{
	/** constructor
	*/
	Pad_Virtual::Pad_Virtual(s32 a_virtualpad_index)
	{
		this->virtualpad_index = a_virtualpad_index;

		this->enable = true;

		this->repeat_loopstart = 11;
		this->repeat_loopend = 14;

		for(int ii=0;ii<COUNTOF(this->button);ii++){
			this->button[ii] = false;
		}
		for(int ii=0;ii<COUNTOF(this->button_old);ii++){
			this->button_old[ii] = false;
		}
		for(int ii=0;ii<COUNTOF(this->button_repeat);ii++){
			this->button_repeat[ii] = 0;
		}
		for(int ii=0;ii<COUNTOF(this->analog);ii++){
			this->analog[ii] = 0.0f;
		}
		for(int ii=0;ii<COUNTOF(this->touch);ii++){
			this->touch[ii].Set(Position2DType<f32>(),false);
		}
		for(int ii=0;ii<COUNTOF(this->touch_flag_old);ii++){
			this->touch_flag_old[ii] = false;
		}
		for(int ii=0;ii<COUNTOF(this->touch_flag_repeat);ii++){
			this->touch_flag_repeat[ii] = 0;
		}
	}


	/** destructor
	*/
	Pad_Virtual::~Pad_Virtual()
	{
	}


	/** AddButton
	*/
	void Pad_Virtual::AddButton(Pad_Virtual::ButtonType::Id a_virtual_button,Pad_Device_Base::ButtonType::Id a_device_button,sharedptr<Pad_Device_Base> a_device)
	{
		ButtonItem t_item;
		{
			t_item.virtual_button = a_virtual_button;
			t_item.device_button = a_device_button;
			t_item.device = a_device;
		}

		this->list_button.push_back(t_item);
	}


	/** AddAnalog
	*/
	void Pad_Virtual::AddAnalog(Pad_Virtual::AnalogType::Id a_virtual_analog,Pad_Device_Base::AnalogType::Id a_device_analog,sharedptr<Pad_Device_Base> a_device)
	{
		AnalogItem t_item;
		{
			t_item.virtual_analog = a_virtual_analog;
			t_item.device_analog = a_device_analog;
			t_item.device = a_device;
		}

		this->list_analog.push_back(t_item);

	}


	/** AddTouch
	*/
	void Pad_Virtual::AddTouch(Pad_Virtual::TouchType::Id a_virtual_touch,Pad_Device_Base::TouchType::Id a_device_touch,sharedptr<Pad_Device_Base> a_device)
	{
		TouchItem t_item;
		{
			t_item.virtual_touch = a_virtual_touch;
			t_item.device_touch = a_device_touch;
			t_item.device = a_device;
		}

		this->list_touch.push_back(t_item);
	}


	/** SetButton
	*/
	void Pad_Virtual::SetButton(Pad_Virtual::ButtonType::Id a_virtual_button,Pad_Device_Base::ButtonType::Id a_device_button,sharedptr<Pad_Device_Base> a_device)
	{
		for(auto t_it = this->list_button.begin();t_it != this->list_button.end();++t_it){
			if(t_it->virtual_button == a_virtual_button){
				t_it->device_button = a_device_button;
				t_it->device = a_device;
			}
		}
	}


	/** SetAnalog
	*/
	void Pad_Virtual::SetAnalog(Pad_Virtual::AnalogType::Id a_virtual_analog,Pad_Device_Base::AnalogType::Id a_device_analog,sharedptr<Pad_Device_Base> a_device)
	{
		for(auto t_it = this->list_analog.begin();t_it != this->list_analog.end();++t_it){
			if(t_it->virtual_analog == a_virtual_analog){
				t_it->device_analog = a_device_analog;
				t_it->device = a_device;
			}
		}
	}


	/** SetTouch
	*/
	void Pad_Virtual::SetTouch(Pad_Virtual::TouchType::Id a_virtual_touch,Pad_Device_Base::TouchType::Id a_device_touch,sharedptr<Pad_Device_Base> a_device)
	{
		for(auto t_it = this->list_touch.begin();t_it != this->list_touch.end();++t_it){
			if(t_it->virtual_touch == a_virtual_touch){
				t_it->device_touch = a_device_touch;
				t_it->device = a_device;
			}
		}
	}


	/** Update
	*/
	void Pad_Virtual::Update()
	{
		if(this->enable == true){
			{
				for(int ii=0;ii<COUNTOF(this->button_old);ii++){
					this->button_old[ii] = this->button[ii];
				}
			}

			{
				auto t_it_end = this->list_button.cend();
				for(auto t_it = this->list_button.cbegin();t_it!=t_it_end;++t_it){
					this->button[t_it->virtual_button] = t_it->device->GetButton(this->virtualpad_index,t_it->device_button);
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->button_repeat);ii++){
					if(this->button[ii] == true){
						this->button_repeat[ii]++;
						if(this->button_repeat[ii] > (this->repeat_loopend - 1)){
							this->button_repeat[ii] = this->repeat_loopstart;
						}
					}else{
						this->button_repeat[ii] = 0;
					}
				}
			}

			{
				auto t_it_end = this->list_analog.cend();
				for(auto t_it = this->list_analog.cbegin();t_it!=t_it_end;++t_it){
					this->analog[t_it->virtual_analog] = t_it->device->GetAnalog(this->virtualpad_index,t_it->device_analog);
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->touch_flag_old);ii++){
					this->touch_flag_old[ii] = this->touch[ii].flag;
				}
			}

			{
				auto t_it_end = this->list_touch.cend();
				for(auto t_it = this->list_touch.cbegin();t_it!=t_it_end;++t_it){
					this->touch[t_it->virtual_touch] = t_it->device->GetTouch(this->virtualpad_index,t_it->device_touch);
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->touch_flag_repeat);ii++){
					if(this->touch[ii].flag == true){
						this->touch_flag_repeat[ii] = (this->touch_flag_repeat[ii] + 1) % 3;
					}else{
						this->touch_flag_repeat[ii] = 0;
					}
				}
			}

		}else{
			{
				for(int ii=0;ii<COUNTOF(this->button_old);ii++){
					this->button_old[ii] = false;
				}
			}

			{
				auto t_it_end = this->list_button.cend();
				for(auto t_it = this->list_button.cbegin();t_it!=t_it_end;++t_it){
					this->button[t_it->virtual_button] = false;
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->button_repeat);ii++){
					this->button_repeat[ii] = 0;
				}
			}

			{
				auto t_it_end = this->list_analog.cend();
				for(auto t_it = this->list_analog.cbegin();t_it!=t_it_end;++t_it){
					this->analog[t_it->virtual_analog] = 0.0f;
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->touch_flag_old);ii++){
					this->touch_flag_old[ii] = false;
				}
			}

			{
				auto t_it_end = this->list_touch.cend();
				for(auto t_it = this->list_touch.cbegin();t_it!=t_it_end;++t_it){
					this->touch[t_it->virtual_touch].Set(Position2DType<f32>(),false);
				}
			}

			{
				for(int ii=0;ii<COUNTOF(this->touch_flag_old);ii++){
					this->touch_flag_repeat[ii] = 0;
				}
			}
		}
	}


	/** SetEnable
	*/
	void Pad_Virtual::SetEnable(bool a_flag)
	{
		this->enable = a_flag;
	}


	/** IsButtonOn
	*/
	bool Pad_Virtual::IsButtonOn(NPad::Pad_Virtual::ButtonType::Id a_virtual_button) const
	{
		if(this->enable == true){
			if(this->button[a_virtual_button] == true){
				return true;
			}
		}

		return false;
	}


	/** IsButtonDown
	*/
	bool Pad_Virtual::IsButtonDown(Pad_Virtual::ButtonType::Id a_virtual_button) const
	{
		if(this->enable == true){
			if((this->button[a_virtual_button] == true)&&(this->button_old[a_virtual_button] == false)){
				return true;
			}
		}

		return false;
	}


	/** IsButtonUp
	*/
	bool Pad_Virtual::IsButtonUp(Pad_Virtual::ButtonType::Id a_virtual_button) const
	{
		if(this->enable == true){
			if((this->button[a_virtual_button] == false)&&(this->button_old[a_virtual_button] == true)){
				return true;
			}
		}

		return false;
	}


	/** IsButtonRepeat
	*/
	bool Pad_Virtual::IsButtonRepeat(Pad_Virtual::ButtonType::Id a_virtual_button) const
	{
		if(this->enable == true){
			if(this->IsButtonDown(a_virtual_button)||(this->button_repeat[a_virtual_button] >= (this->repeat_loopend - 1))){
				return true;
			}
		}

		return false;
	}


	/** GetAnalogValue
	*/
	f32 Pad_Virtual::GetAnalogValue(NPad::Pad_Virtual::AnalogType::Id a_virtual_analog) const
	{
		if(this->enable == true){
			return this->analog[a_virtual_analog];
		}

		return false;
	}


	/** GetTouchValue
	*/
	bool Pad_Virtual::IsTouchDown(NPad::Pad_Virtual::TouchType::Id a_virtual_touch) const
	{
		if(this->enable == true){
			if((this->touch[a_virtual_touch].flag == true)&&(this->touch_flag_old[a_virtual_touch] == false)){
				return true;
			}
		}

		return false;
	}


	/** IsTouchOn
	*/
	bool Pad_Virtual::IsTouchOn(Pad_Virtual::TouchType::Id a_virtual_touch) const
	{
		if(this->enable == true){
			if(this->touch[a_virtual_touch].flag == true){
				return true;
			}
		}

		return false;
	}


	/** GetTouchValue
	*/
	const TouchValue& Pad_Virtual::GetTouchValue(Pad_Virtual::TouchType::Id a_virtual_touch) const
	{
		if(this->enable == true){
			return this->touch[a_virtual_touch];
		}

		return TouchValue::Zero();
	}


}}
#pragma warning(pop)
#endif

