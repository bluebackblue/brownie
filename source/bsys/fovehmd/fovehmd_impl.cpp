

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./fovehmd_impl.h"
#include "./fovehmd.h"
#include "./fovehmd_impl_include.h"


/** lib
*/
#if(BSYS_FOVEHMD_ENABLE)
	#if defined(ROM_32BIT)
		#error
	#else
		#pragma comment(lib, "hovehmd/FOVE SDK 0.11.4/lib/FoveClient.lib")
	#endif
#endif

/** NBsys::NFovehmd
*/
#if(BSYS_FOVEHMD_ENABLE)
namespace NBsys{namespace NFovehmd
{

	namespace NImpl
	{

	}

	/** constructor
	*/
	Fovehmd_Impl::Fovehmd_Impl() throw()
	{
		this->errorcode.id = ErrorCode::Success;
	}

	/** constructor
	*/
	Fovehmd_Impl::~Fovehmd_Impl() throw()
	{
	}

	/** ResetErrorCode
	*/
	void Fovehmd_Impl::ResetErrorCode()
	{
		this->errorcode.id = ErrorCode::Success;
	}

	/** GetErrorCode
	*/
	ErrorCode Fovehmd_Impl::GetErrorCode()
	{
		return this->errorcode;
	}

	/** �ڑ��J�n�B
	*/
	void Fovehmd_Impl::ConnectStart()
	{
		//�C���X�^���X�擾�B
		this->headset.reset(Fove::GetFVRHeadset(),null_delete());

		if(this->headset){
			//�����^�C���A�R���|�W�^�[�N���B
			bool t_ret_initialize = this->headset->Initialise(Fove::EFVR_ClientCapabilities::Orientation | Fove::EFVR_ClientCapabilities::Position);
			TAGLOG("fovehmd",VASTRING_DEBUG("ret_initialize = %s",t_ret_initialize?"true":"false"));
		}else{
			//���s�B
			//Unable to create headset connection.
			this->errorcode.id = ErrorCode::UnknownError;
			return;
		}

		//�C���X�^���X�擾�B
		this->compositor.reset(Fove::GetFVRCompositor(),null_delete());

		if(this->compositor){
			//�����B
			return;
		}else{
			//���s�B
			//Unable to create compositor connection
			this->errorcode.id = ErrorCode::UnknownError;
			return;
		}
	}

	/** �ڑ����B
	*/
	bool Fovehmd_Impl::ConnectUpdate()
	{
		if(this->errorcode.id == ErrorCode::Success){

			if(this->compositor){
				const Fove::SFVR_Vec2i t_ret = this->compositor->GetSingleEyeResolution();
				if((t_ret.x > 0) && (t_ret.y > 0)){

					//�����B

					this->singleeye_resolution.x = static_cast< f32 >(t_ret.x);
					this->singleeye_resolution.y = static_cast< f32 >(t_ret.y);
					return true;

				}else{

					//�擾���s�B

					return false;

				}
			}else{

				ASSERT(0);
				this->errorcode.id = ErrorCode::UnknownError;
				return true;

			}

		}else{

			//�G���[���������Ă���B
			return true;

		}
		
		return false;
	}

	/** �T�C�Y�擾�B
	*/
	NGeometry::Geometry_Vector2& Fovehmd_Impl::GetSingleEyeResolution()
	{
		return this->singleeye_resolution;
	}

	/**
	*/
	void Fovehmd_Impl::Update()
	{
		Fove::SFVR_Pose t_pose = this->compositor->WaitForRenderPose();

		this->camera_position.Set_Translate(-t_pose.position.x,-t_pose.position.y,-t_pose.position.z);
	}
}}
#endif

