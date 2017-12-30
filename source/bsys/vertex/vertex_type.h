#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief バーテックス。
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


/** NBsys::NVertex
*/
#if(BSYS_VERTEX_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace NVertex
{
	/** DEF_VERTEX_MEMBER

	XXX			: メンバ変数名
	TTT			: メンバ変数タイプ	
	INVALID		: メンバ変数が存在しない場合のGetValue戻り値

	*/
	#define DEF_VERTEX_MEMBER(XXX,TTT,INVALID)													\
	template <typename V,bool> struct XXX ## _setget											\
	{																							\
		static void SetValue(V& /*a_vertex*/,TTT /*a_value*/){}									\
		static TTT GetValue(V& /*a_vertex*/){return INVALID;}									\
	};																							\
	template <typename V> struct XXX ## _setget<V,true>											\
	{																							\
		static void SetValue(V& a_vertex,TTT a_value)											\
		{																						\
			a_vertex.XXX = a_value;																\
		}																						\
		static TTT GetValue(V& a_vertex)														\
		{																						\
			return 0.0f;																		\
		}																						\
	};																							\
	struct XXX ## _check																		\
	{																							\
		template <class T> static std::true_type check(decltype(T::XXX)*);						\
		template <class T> static std::false_type check(...);									\
	}


	/** CALL_GET_MEMBER

	XXX			: メンバ変数名
	VERTEX		: バーテックス

	*/
	#define CALL_GET_MEMBER(XXX,VERTEX)															\
	NImpl::XXX ## _setget<T,decltype(NImpl::XXX ## _check::check<T>(nullptr))::value>::GetValue(VERTEX)

	/** CALL_SET_MEMBER

	XXX			: メンバ変数名
	VERTEX		: バーテックス
	VALUE		: 値

	*/
	#define CALL_SET_MEMBER(XXX,VERTEX,VALUE)													\
	NImpl::XXX ## _setget<T,decltype(NImpl::XXX ## _check::check<T>(nullptr))::value>::SetValue(VERTEX,VALUE)


	/** Vertex_Data_Pos3
	*/
	struct Vertex_Data_Pos3
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;
	};


	/** Vertex_Data_Pos3Color4
	*/
	struct Vertex_Data_Pos3Color4
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;

		f32 color_rr;
		f32 color_gg;
		f32 color_bb;
		f32 color_aa;
	};


	/** Vertex_Data_Pos4Color3
	*/
	struct Vertex_Data_Pos4Color3
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;
		f32 pos_ww;

		f32 color_rr;
		f32 color_gg;
		f32 color_bb;
	};


	/** Vertex_Data_Pos3Uv2Color4
	*/
	struct Vertex_Data_Pos3Uv2Color4
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;

		f32 uv_xx;
		f32 uv_yy;

		f32 color_rr;
		f32 color_gg;
		f32 color_bb;
		f32 color_aa;
	};


	/** Vertex_Data_Pos3Uv2Color4TextureIndex4
	*/
	struct Vertex_Data_Pos3Uv2Color4TextureIndex4
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;

		f32 uv_xx;
		f32 uv_yy;

		f32 color_rr;
		f32 color_gg;
		f32 color_bb;
		f32 color_aa;

		u8 texture_index_00;
		u8 texture_index_01;
		u8 texture_index_02;
		u8 texture_index_03;
	};


	/** Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4
	*/
	struct Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4
	{
		f32 pos_xx;
		f32 pos_yy;
		f32 pos_zz;

		f32 uv_xx;
		f32 uv_yy;

		s32 matrix_index_00;
		s32 matrix_index_01;
		s32 matrix_index_02;
		s32 matrix_index_03;

		f32 matrix_weight_00;
		f32 matrix_weight_01;
		f32 matrix_weight_02;
		f32 matrix_weight_03;
	};


	namespace NImpl
	{
		/** 定義列挙。
		*/
		DEF_VERTEX_MEMBER(pos_xx,f32,0.0f);
		DEF_VERTEX_MEMBER(pos_yy,f32,0.0f);
		DEF_VERTEX_MEMBER(pos_zz,f32,0.0f);
		DEF_VERTEX_MEMBER(pos_ww,f32,0.0f);

		DEF_VERTEX_MEMBER(uv_xx,f32,0.0f);
		DEF_VERTEX_MEMBER(uv_yy,f32,0.0f);

		DEF_VERTEX_MEMBER(color_rr,f32,0.0f);
		DEF_VERTEX_MEMBER(color_gg,f32,0.0f);
		DEF_VERTEX_MEMBER(color_bb,f32,0.0f);
		DEF_VERTEX_MEMBER(color_aa,f32,0.0f);

		DEF_VERTEX_MEMBER(texture_index_00,u8,0);
		DEF_VERTEX_MEMBER(texture_index_01,u8,0);
		DEF_VERTEX_MEMBER(texture_index_02,u8,0);
		DEF_VERTEX_MEMBER(texture_index_03,u8,0);

		DEF_VERTEX_MEMBER(matrix_index_00,s32,0);
		DEF_VERTEX_MEMBER(matrix_index_01,s32,0);
		DEF_VERTEX_MEMBER(matrix_index_02,s32,0);
		DEF_VERTEX_MEMBER(matrix_index_03,s32,0);

		DEF_VERTEX_MEMBER(matrix_weight_00,f32,0.0f);
		DEF_VERTEX_MEMBER(matrix_weight_01,f32,0.0f);
		DEF_VERTEX_MEMBER(matrix_weight_02,f32,0.0f);
		DEF_VERTEX_MEMBER(matrix_weight_03,f32,0.0f);

	}


	/** SetPos_XX
	*/
	template <typename T> inline void SetPos_XX(T& a_vertex,f32 a_pos_xx)
	{
		CALL_SET_MEMBER(pos_xx,a_vertex,a_pos_xx);
	}


	/** SetPos_YY
	*/
	template <typename T> inline void SetPos_YY(T& a_vertex,f32 a_pos_yy)
	{
		CALL_SET_MEMBER(pos_yy,a_vertex,a_pos_yy);
	}

	
	/** SetPos_ZZ
	*/
	template <typename T> inline void SetPos_ZZ(T& a_vertex,f32 a_pos_zz)
	{
		CALL_SET_MEMBER(pos_zz,a_vertex,a_pos_zz);
	}


	/** SetPos_WW
	*/
	template <typename T> inline void SetPos_WW(T& a_vertex,f32 a_pos_ww)
	{
		CALL_SET_MEMBER(pos_ww,a_vertex,a_pos_ww);
	}


	/** SetUv_XX
	*/
	template <typename T> inline void SetUv_XX(T& a_vertex,f32 a_uv_xx)
	{
		CALL_SET_MEMBER(uv_xx,a_vertex,a_uv_xx);
	}


	/** SetUv_YY
	*/
	template <typename T> inline void SetUv_YY(T& a_vertex,f32 a_uv_yy)
	{
		CALL_SET_MEMBER(uv_yy,a_vertex,a_uv_yy);
	}


	/** SetColor_RR
	*/
	template <typename T> inline void SetColor_RR(T& a_vertex,f32 a_color_rr)
	{
		CALL_SET_MEMBER(color_rr,a_vertex,a_color_rr);
	}


	/** SetColor_GG
	*/
	template <typename T> inline void SetColor_GG(T& a_vertex,f32 a_color_gg)
	{
		CALL_SET_MEMBER(color_gg,a_vertex,a_color_gg);
	}

	
	/** SetColor_BB
	*/
	template <typename T> inline void SetColor_BB(T& a_vertex,f32 a_color_bb)
	{
		CALL_SET_MEMBER(color_bb,a_vertex,a_color_bb);
	}


	/** SetColor_AA
	*/
	template <typename T> inline void SetColor_AA(T& a_vertex,f32 a_color_aa)
	{
		CALL_SET_MEMBER(color_aa,a_vertex,a_color_aa);
	}

	
	/** SetMatrixIndex
	*/
	template <typename T> inline void SetMatrixIndex(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3)
	{
		CALL_SET_MEMBER(texture_index_00,a_vertex,a_matrix_index_0);
		CALL_SET_MEMBER(texture_index_01,a_vertex,a_matrix_index_1);
		CALL_SET_MEMBER(texture_index_02,a_vertex,a_matrix_index_2);
		CALL_SET_MEMBER(texture_index_03,a_vertex,a_matrix_index_3);
	}


	/** SetMatrixWeight
	*/
	template <typename T> inline void SetMatrixWeight(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3)
	{
		CALL_SET_MEMBER(matrix_weight_00,a_vertex,a_matrix_weight_0);
		CALL_SET_MEMBER(matrix_weight_01,a_vertex,a_matrix_weight_1);
		CALL_SET_MEMBER(matrix_weight_02,a_vertex,a_matrix_weight_2);
		CALL_SET_MEMBER(matrix_weight_03,a_vertex,a_matrix_weight_3);
	}


	/** SetPos
	*/
	template <typename T> inline void SetPos(T& a_vertex,f32 a_pos_xx = 0.0f,f32 a_pos_yy = 0.0f,f32 a_pos_zz = 0.0f,f32 a_pos_ww = 0.0f)
	{
		SetPos_XX<T>(a_vertex,a_pos_xx);
		SetPos_YY<T>(a_vertex,a_pos_yy);
		SetPos_ZZ<T>(a_vertex,a_pos_zz);
		SetPos_WW<T>(a_vertex,a_pos_ww);
	}


	/** SetUv
	*/
	template <typename T> inline void SetUv(T& a_vertex,f32 a_uv_xx = 0.0f,f32 a_uv_yy = 0.0f)
	{
		SetUv_XX<T>(a_vertex,a_uv_xx);
		SetUv_YY<T>(a_vertex,a_uv_yy);
	}


	/** SetColor
	*/
	template <typename T> inline void SetColor(T& a_vertex,f32 a_color_rr = 0.0f,f32 a_color_gg = 0.0f,f32 a_color_bb = 0.0f,f32 a_color_aa = 0.0f)
	{
		SetColor_RR<T>(a_vertex,a_color_rr);
		SetColor_GG<T>(a_vertex,a_color_gg);
		SetColor_BB<T>(a_vertex,a_color_bb);
		SetColor_AA<T>(a_vertex,a_color_aa);
	}


	/** SetPos
	*/
	template <typename T> inline void SetPos(T& a_vertex,const NBsys::NGeometry::Geometry_Vector2& a_vector)
	{
		SetPos<T>(a_vertex,a_vector.Get_X(),a_vertex,a_vector.Get_Y());
	}


	/** SetPos
	*/
	template <typename T> inline void SetPos(T& a_vertex,const NBsys::NGeometry::Geometry_Vector3& a_vector)
	{
		SetPos<T>(a_vertex,a_vector.Get_X(),a_vertex,a_vector.Get_Y(),a_vertex,a_vector.Get_Z());
	}


	/** SetPos
	*/
	template <typename T> inline void SetPos(T& a_vertex,const NBsys::NGeometry::Geometry_Vector4& a_vector)
	{
		SetPos<T>(a_vertex,a_vector.Get_X(),a_vertex,a_vector.Get_Y(),a_vertex,a_vector.Get_Z(),a_vertex,a_vector.Get_W());
	}


	/** SetUv
	*/
	template <typename T> inline void SetUv(T& a_vertex,const NBsys::NGeometry::Geometry_Vector2& a_vector)
	{
		SetUv_XX<T>(a_vertex,a_vector.Get_X());
		SetUv_YY<T>(a_vertex,a_vector.Get_Y());
	}


	/** SetColor
	*/
	template <typename T> inline void SetColor(T& a_vertex,const NBsys::NGeometry::Geometry_Vector3& a_vector)
	{
		SetColor<T>(a_vertex,a_vector.Get_X(),a_vertex,a_vector.Get_Y(),a_vertex,a_vector.Get_Z());
	}


	/** SetColor
	*/
	template <typename T> inline void SetColor(T& a_vertex,const NBsys::NGeometry::Geometry_Vector4& a_vector)
	{
		SetColor<T>(a_vertex,a_vector.Get_X(),a_vertex,a_vector.Get_Y(),a_vertex,a_vector.Get_Z(),a_vertex,a_vector.Get_W());
	}



	//TODO:シェーダ用の変数オフセット。

	/** GetPosOffset_XX
	*/
	//template <typename T> inline s32 GetPosOffset_XX()
	//{
	//	return NImpl::Vertex_SetPos_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_XX<T,true>*>::value>::GetOffset();
	//}

	/** GetPosOffset_YY
	*/
	//template <typename T> inline s32 GetPosOffset_YY()
	//{
	//	return NImpl::Vertex_SetPos_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_YY<T,true>*>::value>::GetOffset();
	//}

	/** GetPosOffset_ZZ
	*/
	//template <typename T> inline s32 GetPosOffset_ZZ()
	//{
	//	return NImpl::Vertex_SetPos_ZZ<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_ZZ<T,true>*>::value>::GetOffset();
	//}

	/** GetPosOffset_WW
	*/
	//template <typename T> inline s32 GetPosOffset_WW()
	//{
	//	return NImpl::Vertex_SetPos_WW<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_WW<T,true>*>::value>::GetOffset();
	//}

	/** GetColorOffset_RR
	*/
	//template <typename T> inline s32 GetColorOffset_RR()
	//{
	//	return NImpl::Vertex_SetColor_RR<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_RR<T,true>*>::value>::GetOffset();
	//}

	//** GetColorOffset_GG
	//*/
	//template <typename T> inline s32 GetColorOffset_GG()
	//{
	//	return NImpl::Vertex_SetColor_GG<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_GG<T,true>*>::value>::GetOffset();
	//}

	//** GetColorOffset_BB
	//*/
	//template <typename T> inline s32 GetColorOffset_BB()
	//{
	//	return NImpl::Vertex_SetColor_BB<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_BB<T,true>*>::value>::GetOffset();
	//}

	//** GetColorOffset_AA
	//*/
	//template <typename T> inline s32 GetColorOffset_AA()
	//{
	//	return NImpl::Vertex_SetColor_AA<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_AA<T,true>*>::value>::GetOffset();
	//}

	/** GetUvOffset_XX
	*/
	//template <typename T> inline s32 GetUvOffset_XX()
	//{
	//	return NImpl::Vertex_SetUv_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_XX<T,true>*>::value>::GetOffset();
	//}

	/** GetUvOffset_YY
	*/
	//template <typename T> inline s32 GetUvOffset_YY()
	//{
	//	return NImpl::Vertex_SetUv_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_YY<T,true>*>::value>::GetOffset();
	//}

	//template <typename T> inline s32 GetMatrixIndexOffset()
	//{
	//	CALL_SET_MEMBER(uv_xx,a_vertex,a_uv_xx);
	//}

	/** GetMatrixWeightOffset
	*/
	//template <typename T> inline s32 GetMatrixWeightOffset()
	//{
	//	return NImpl::Vertex_SetMatrixweight4<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetMatrixweight4<T,true>*>::value>::GetOffset();
	//}


}}
#pragma warning(pop)
#endif

