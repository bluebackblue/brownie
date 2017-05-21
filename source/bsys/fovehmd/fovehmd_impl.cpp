

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD。
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
	/** constructor
	*/
	Fovehmd_Impl::Fovehmd_Impl() throw()
		:
		errorcode(ErrorCode::Success),
		headset(),
		compositor(),
		singleeye_resolution(0.0f,0.0f),
		//pose(),
		camera_position(NBsys::NGeometry::Geometry_Identity()),
		camera_quaternion(NBsys::NGeometry::Geometry_Identity())
	{
	}

	/** constructor
	*/
	Fovehmd_Impl::~Fovehmd_Impl() throw()
	{
		this->compositor.reset();
		this->headset.reset();
	}

	/** ResetErrorCode
	*/
	void Fovehmd_Impl::ResetErrorCode()
	{
		this->errorcode.code = ErrorCode::Success;
	}

	/** GetErrorCode
	*/
	ErrorCode Fovehmd_Impl::GetErrorCode()
	{
		return this->errorcode;
	}

	/** 接続開始。
	*/
	void Fovehmd_Impl::ConnectStart()
	{
		//インスタンス取得。
		this->headset.reset(Fove::GetFVRHeadset(),null_delete());

		if(this->headset){
			//ランタイム、コンポジター起動。
			bool t_ret_initialize = this->headset->Initialise(Fove::EFVR_ClientCapabilities::Orientation | Fove::EFVR_ClientCapabilities::Position);
			TAGLOG("fovehmd",VASTRING_DEBUG("ret_initialize = %s",t_ret_initialize ? "true" : "false"));
		}else{
			//失敗。
			//Unable to create headset connection.
			this->errorcode.code = ErrorCode::UnknownError;
			return;
		}

		//インスタンス取得。
		this->compositor.reset(Fove::GetFVRCompositor(),null_delete());

		if(this->compositor){
			//成功。
			return;
		}else{
			//失敗。
			//Unable to create compositor connection
			this->errorcode.code = ErrorCode::UnknownError;
			return;
		}
	}

	/** 接続中。
	*/
	bool Fovehmd_Impl::ConnectUpdate()
	{
		if(this->errorcode.code == ErrorCode::Success){

			if(this->compositor){
				const Fove::SFVR_Vec2i t_ret = this->compositor->GetSingleEyeResolution();
				if((t_ret.x > 0) && (t_ret.y > 0)){

					//成功。

					this->singleeye_resolution.x = static_cast< f32 >(t_ret.x);
					this->singleeye_resolution.y = static_cast< f32 >(t_ret.y);
					return true;

				}else{

					//取得失敗。

					return false;

				}
			}else{

				ASSERT(0);
				this->errorcode.code = ErrorCode::UnknownError;
				return true;

			}

		}else{

			//エラーが発生している。
			return true;

		}
		
		return false;
	}

	/** サイズ取得。
	*/
	NGeometry::Geometry_Vector2& Fovehmd_Impl::GetSingleEyeResolution()
	{
		return this->singleeye_resolution;
	}

	/** Update
	*/
	void Fovehmd_Impl::Update()
	{
		Fove::SFVR_Pose t_pose = this->compositor->WaitForRenderPose();

		this->pose = this->compositor->WaitForRenderPose();

		if(this->pose.error != Fove::EFVR_ErrorCode::None){
			return;
		}

		//camera_position
		this->camera_position.Set(this->pose.position.x,this->pose.position.y,this->pose.position.z);

		//camera_quaternion
		this->camera_quaternion = NBsys::NGeometry::Geometry_Quaternion(-pose.orientation.x,-pose.orientation.y,-pose.orientation.z,pose.orientation.w);
		this->camera_matrix = NBsys::NGeometry::Geometry_Matrix_44(this->camera_quaternion);

		//translate
		f32 t_iod = this->GetIOD();
		this->eye_translate_left = NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(-t_iod,0,0);
		this->eye_translate_right = NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_iod,0,0);
	}

	/** GetIOD
	*/
	f32 Fovehmd_Impl::GetIOD()
	{
		f32 t_half_iod = 0.064f;

		this->headset->GetIOD(t_half_iod);
		
		return t_half_iod;
	}

	/** SetTexture
	*/
	void Fovehmd_Impl::SetTexture(void* a_texture_pointer)
	{
		Fove::SFVR_CompositorTexture t_texture(a_texture_pointer);

		{
			Fove::SFVR_TextureBounds t_bounds;
			t_bounds.top = 0;
			t_bounds.bottom = 1;
			t_bounds.left = 0;
			t_bounds.right = 0.5f;
			this->compositor->Submit(Fove::EFVR_Eye::Left,t_texture,t_bounds,pose);
		}

		{
			Fove::SFVR_TextureBounds t_bounds;
			t_bounds.top = 0;
			t_bounds.bottom = 1;
			t_bounds.left = 0.5f;
			t_bounds.right = 1;
			this->compositor->Submit(Fove::EFVR_Eye::Right,t_texture,t_bounds,pose);

		}
	}

	/** GetCameraPosition
	*/
	NBsys::NGeometry::Geometry_Vector3& Fovehmd_Impl::GetCameraPosition()
	{
		return this->camera_position;
	}

	/** GetCameraQuaternion
	*/
	NBsys::NGeometry::Geometry_Quaternion& Fovehmd_Impl::GetCameraQuaternion()
	{
		return this->camera_quaternion;
	}

	/** GetLeftProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd_Impl::GetLeftProjection(f32 a_near,f32 a_far)
	{
		Fove::SFVR_Matrix44 t_projection = this->headset->GetProjectionMatrixLH(Fove::EFVR_Eye::Left,a_near,a_far);

		return NBsys::NGeometry::Geometry_Matrix_44(&t_projection.mat[0][0]);
	}

	/** GetRightProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd_Impl::GetRightProjection(f32 a_near,f32 a_far)
	{
		Fove::SFVR_Matrix44 t_projection = this->headset->GetProjectionMatrixLH(Fove::EFVR_Eye::Right,a_near,a_far);

		return NBsys::NGeometry::Geometry_Matrix_44(&t_projection.mat[0][0]);
	}

	/** GetLeftEyeTranslate
	*/
	NBsys::NGeometry::Geometry_Matrix_44& Fovehmd_Impl::GetLeftEyeTranslate()
	{
		return this->eye_translate_left;
	}

	/** GetRightEyeTranslate
	*/
	NBsys::NGeometry::Geometry_Matrix_44& Fovehmd_Impl::GetRightEyeTranslate()
	{
		return this->eye_translate_right;
	}

	/** GetLeftViewProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd_Impl::GetLeftViewProjection(f32 a_near,f32 a_far,float a_camera_y)
	{
		NBsys::NGeometry::Geometry_Matrix_44 t_camera_matrix = this->camera_matrix;
		{
			t_camera_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(this->camera_position.x,this->camera_position.y + a_camera_y,this->camera_position.z);
			t_camera_matrix *= this->eye_translate_left;
		}

		t_camera_matrix.Set_Inverse();
		t_camera_matrix *= this->GetLeftProjection(a_near,a_far);

		return t_camera_matrix;
	}

	/** GetRightViewProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd_Impl::GetRightViewProjection(f32 a_near,f32 a_far,float a_camera_y)
	{
		NBsys::NGeometry::Geometry_Matrix_44 t_camera_matrix = this->camera_matrix;
		{
			t_camera_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(this->camera_position.x,this->camera_position.y + a_camera_y,this->camera_position.z);
			t_camera_matrix *= this->eye_translate_right;
		}

		t_camera_matrix.Set_Inverse();
		t_camera_matrix *= this->GetRightProjection(a_near,a_far);

		return t_camera_matrix;
	}

}}
#endif

