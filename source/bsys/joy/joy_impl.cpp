

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジョイスティック。
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
#include "./joy_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NHttp
*/
#if(BSYS_JOY_ENABLE)
namespace NBsys{namespace NJoy
{
	/** constructor
	*/
	Joy_Impl::Joy_Impl(s32 a_index)
		:
		#if defined(PLATFORM_VCWIN)

		connected(false),
		id(JOYSTICKID1 + a_index)
		//caps(),
		//info()

		#endif
	{
		#if defined(PLATFORM_VCWIN)
		{
			NMemory::ZeroClear(this->caps);
			NMemory::ZeroClear(this->info);

			this->info.dwSize = sizeof(this->info);
			this->info.dwFlags = JOY_RETURNALL;
		}
		#endif
	}


	/** destructor
	*/
	Joy_Impl::~Joy_Impl()
	{
	}


	/** 更新。
	*/
	void Joy_Impl::Update()
	{
		#if defined(PLATFORM_VCWIN)
		{
			MMRESULT t_ret_getpos = ::joyGetPosEx(this->id,&this->info);
			if(t_ret_getpos == JOYERR_NOERROR){
				if(this->connected == false){
					MMRESULT t_ret_getdevcaps = ::joyGetDevCapsW(JOYSTICKID1,&this->caps,sizeof(this->caps));
					if(t_ret_getdevcaps == JOYERR_NOERROR){
						this->connected = true;
					}
				}
			}else{
				this->connected = false;
			}
		}
		#endif
	}


	/** 接続確認。
	*/
	bool Joy_Impl::IsConnected() const
	{
		return this->connected;
	}


	/** 上。
	*/
	bool Joy_Impl::Up() const
	{
		#if defined(PLATFORM_VCWIN)
		{
			if(this->connected == true){
				s32 t_index = this->info.dwPOV / 4500;
				if((t_index == 0)||(t_index == 1)||(t_index == 7)){
					return true;
				}
			}
		}
		#endif

		return false;
	}


	/** 下。
	*/
	bool Joy_Impl::Down() const
	{
		#if defined(PLATFORM_VCWIN)
		{
			if(this->connected == true){
				s32 t_index = this->info.dwPOV / 4500;
				if((t_index == 3)||(t_index == 4)||(t_index == 5)){
					return true;
				}
			}
		}
		#endif

		return false;
	}


	/** 左。
	*/
	bool Joy_Impl::Left() const
	{
		#if defined(PLATFORM_VCWIN)
		{
			if(this->connected == true){
				s32 t_index = this->info.dwPOV / 4500;
				if((t_index == 5)||(t_index == 6)||(t_index == 7)){
					return true;
				}
			}
		}
		#endif

		return false;
	}


	/** 左。
	*/
	bool Joy_Impl::Right() const
	{
		#if defined(PLATFORM_VCWIN)
		{
			if(this->connected == true){
				s32 t_index = this->info.dwPOV / 4500;
				if((t_index == 1)||(t_index == 2)||(t_index == 3)){
					return true;
				}
			}
		}
		#endif

		return false;
	}


}}
#endif

