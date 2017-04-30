#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÉÇÉfÉãÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./model_vertex.h"
#include "./model_presest.h"
//#include "./model_bone.h"


/** NBsys::NModel
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NModel
{
	/** Model_Vertex_Data_Pos

	pos_x pos_y pos_z

	*/
	struct Model_Vertex_Data_Pos
	{
		union
		{
			struct
			{
				f32 pos_x;
				f32 pos_y;
				f32 pos_z;
			};
		};
	};

	/** Model_Vertex_Data_PosColor

	pos_x pos_y pos_z
	color_r color_g color_b color_a

	*/
	struct Model_Vertex_Data_PosColor
	{
		union
		{
			struct
			{
				f32 pos_x;
				f32 pos_y;
				f32 pos_z;

				f32 color_r;
				f32 color_g;
				f32 color_b;
				f32 color_a;
			};
		};
	};

	/** Model_Vertex_Data_PosUvColor

	pos_x pos_y pos_z
	uv_x uv_y
	color_r color_g color_b color_a

	*/
	struct Model_Vertex_Data_PosUvColor
	{
		union
		{
			struct
			{
				f32 pos_x;
				f32 pos_y;
				f32 pos_z;

				f32 uv_x;
				f32 uv_y;

				f32 color_r;
				f32 color_g;
				f32 color_b;
				f32 color_a;
			};
		};
	};

	/** Model_Vertex_Data_PosUvMatrixindexMatrixweight

	pos_x pos_y pos_z
	uv_x uv_y
	matrix_index_0 matrix_index_1 matrix_index_2 matrix_index_3
	matrix_weight_0 matrix_weight_1 matrix_weight_2 matrix_weight_3

	*/
	struct Model_Vertex_Data_PosUvMatrixindexMatrixweight
	{
		union
		{
			struct
			{
				f32 pos_x;
				f32 pos_y;
				f32 pos_z;

				f32 uv_x;
				f32 uv_y;

				s32 matrix_index_0;
				s32 matrix_index_1;
				s32 matrix_index_2;
				s32 matrix_index_3;

				f32 matrix_weight_0;
				f32 matrix_weight_1;
				f32 matrix_weight_2;
				f32 matrix_weight_3;
			};
		};
	};

	namespace NImpl
	{
		//Model_Vertex_SetPos
		template < typename T , bool EXIST > struct Model_Vertex_SetPos
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_pos_x,f32 a_pos_y,f32 a_pos_z){}
		};
		template < typename T > struct Model_Vertex_SetPos< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->pos_x)));
			}
			static void Set(T& a_vertex,f32 a_pos_x,f32 a_pos_y,f32 a_pos_z)
			{
				a_vertex.pos_x = a_pos_x;
				a_vertex.pos_y = a_pos_y;
				a_vertex.pos_z = a_pos_z;
			}
		};

		//Model_Vertex_SetColor
		template < typename T , bool EXIST > struct Model_Vertex_SetColor
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_color_r,f32 a_color_g,f32 a_color_b,f32 a_color_a){}
		};
		template < typename T > struct Model_Vertex_SetColor< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->color_r)));
			}
			static void Set(T& a_vertex,f32 a_color_r,f32 a_color_g,f32 a_color_b,f32 a_color_a)
			{
				a_vertex.color_r = a_color_r;
				a_vertex.color_g = a_color_g;
				a_vertex.color_b = a_color_b;
				a_vertex.color_a = a_color_a;
			}
		};

		//Model_Vertex_SetUv
		template < typename T , bool EXIST > struct Model_Vertex_SetUv
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_uv_x,f32 a_uv_y){}
		};
		template < typename T > struct Model_Vertex_SetUv< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->uv_x)));
			}
			static void Set(T& a_vertex,f32 a_uv_x,f32 a_uv_y)
			{
				a_vertex.uv_x = a_uv_x;
				a_vertex.uv_y = a_uv_y;
			}
		};

		//Model_Vertex_SetMatrixindex
		template < typename T , bool EXIST > struct Model_Vertex_SetMatrixindex
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3){}
		};
		template < typename T > struct Model_Vertex_SetMatrixindex< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->matrix_index_0)));
			}
			static void Set(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3)
			{
				a_vertex.matrix_index_0 = a_matrix_index_0;
				a_vertex.matrix_index_1 = a_matrix_index_1;
				a_vertex.matrix_index_2 = a_matrix_index_2;
				a_vertex.matrix_index_3 = a_matrix_index_3;
			}
		};

		//Model_Vertex_SetMatrixweight
		template < typename T , bool EXIST > struct Model_Vertex_SetMatrixweight
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3){}
		};
		template < typename T > struct Model_Vertex_SetMatrixweight< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->matrix_weight_0)));
			}
			static void Set(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3)
			{
				a_vertex.matrix_weight_0 = a_matrix_weight_0;
				a_vertex.matrix_weight_1 = a_matrix_weight_1;
				a_vertex.matrix_weight_2 = a_matrix_weight_2;
				a_vertex.matrix_weight_3 = a_matrix_weight_3;
			}
		};

		//Model_Vertex_SetDummy
		template < typename T , bool EXIST > struct Model_Vertex_SetDummy
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_dummy){}
		};
		template < typename T > struct Model_Vertex_SetDummy< T , true >
		{
			static s32 GetOffset()
			{
				return static_cast< s32 >(reinterpret_cast< std::size_t >(&(reinterpret_cast< T* >(nullptr)->dummy)));
			}
			static void Set(T& a_vertex,f32 a_dummy)
			{
				a_vertex.dummy = a_dummy;
			}
		};

		/** Model_Vertex_Convertible
		*/
		template < typename T > class Model_Vertex_Convertible;

		/** Model_Vertex_Data_Pos
		*/
		template < > class Model_Vertex_Convertible< Model_Vertex_Data_Pos >
			:
				public Model_Vertex_SetPos< Model_Vertex_Data_Pos , true >
		{
		};

		/** Model_Vertex_Data_PosColor
		*/
		template < > class Model_Vertex_Convertible< Model_Vertex_Data_PosColor >
			:
				public Model_Vertex_SetPos< Model_Vertex_Data_PosColor , true >,
				public Model_Vertex_SetColor< Model_Vertex_Data_PosColor , true >
		{
		};

		/** Model_Vertex_Data_PosUvColor
		*/
		template < > class Model_Vertex_Convertible< Model_Vertex_Data_PosUvColor >
			:
				public Model_Vertex_SetPos< Model_Vertex_Data_PosUvColor , true >,
				public Model_Vertex_SetUv< Model_Vertex_Data_PosUvColor , true >,
				public Model_Vertex_SetColor< Model_Vertex_Data_PosUvColor , true >
		{
		};

		/** Model_Vertex_Data_PUMIMW
		*/
		template < > class Model_Vertex_Convertible< Model_Vertex_Data_PosUvMatrixindexMatrixweight >
			:
				public Model_Vertex_SetPos< Model_Vertex_Data_PosUvMatrixindexMatrixweight , true >,
				public Model_Vertex_SetUv< Model_Vertex_Data_PosUvMatrixindexMatrixweight , true >,
				public Model_Vertex_SetMatrixindex< Model_Vertex_Data_PosUvMatrixindexMatrixweight , true >,
				public Model_Vertex_SetMatrixweight< Model_Vertex_Data_PosUvMatrixindexMatrixweight , true >
		{
		};
	}
		
	/** SetPos
	*/
	template < typename T > inline void SetPos(T& a_vertex,f32 a_pos_x,f32 a_pos_y,f32 a_pos_z)
	{
		NImpl::Model_Vertex_SetPos< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetPos< T , true >* >::value >::Set(a_vertex,a_pos_x,a_pos_y,a_pos_z);
	}
	template < typename T > inline s32 GetPosOffset()
	{
		return NImpl::Model_Vertex_SetPos< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetPos< T , true >* >::value >::GetOffset();
	}

	/** SetColor
	*/
	template < typename T > inline void SetColor(T& a_vertex,f32 a_color_r,f32 a_color_g,f32 a_color_b,f32 a_color_a)
	{
		NImpl::Model_Vertex_SetColor< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetColor< T , true >* >::value >::Set(a_vertex,a_color_r,a_color_g,a_color_b,a_color_a);
	}
	template < typename T > inline s32 GetColorOffset()
	{
		return NImpl::Model_Vertex_SetColor< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetColor< T , true >* >::value >::GetOffset();
	}

	/** SetUv
	*/
	template < typename T > inline void SetUv(T& a_vertex,f32 a_uv_x,f32 a_uv_y)
	{
		NImpl::Model_Vertex_SetUv< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetUv< T , true >* >::value >::Set(a_vertex,a_uv_x,a_uv_y);
	}
	template < typename T > inline s32 GetUvOffset()
	{
		return NImpl::Model_Vertex_SetUv< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetUv< T , true >* >::value >::GetOffset();
	}

	/** SetMatrixIndex
	*/
	template < typename T > inline void SetMatrixIndex(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3)
	{
		NImpl::Model_Vertex_SetMatrixIndex< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetMatrixIndex< T , true >* >::value >::Set(a_vertex,a_matrix_index_0,a_matrix_index_1,a_matrix_index_2,a_matrix_index_3);
	}
	template < typename T > inline s32 GetMatrixIndexOffset()
	{
		return NImpl::Model_Vertex_SetMatrixIndex< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetMatrixIndex< T , true >* >::value >::GetOffset();
	}

	/** SetMatrixWeight
	*/
	template < typename T > inline void SetMatrixWeight(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3)
	{
		NImpl::Model_Vertex_SetMatrixWeight< T , is_convertible< NImpl::Model_Vertex_Convertible< T >* , NImpl::Model_Vertex_SetMatrixWeight< T , true >* >::value >::Set(a_vertex,a_matrix_weight_0,a_matrix_weight_1,a_matrix_weight_2,a_matrix_weight_3);
	}
	template < typename T > inline s32 GetMatrixWeightOffset()
	{
		return NImpl::Model_Vertex_SetMatrixWeight< T , is_convertible< NImpl::Model_Vertex_Convertible< T >* , NImpl::Model_Vertex_SetMatrixWeight< T , true >* >::value >::GetOffset();
	}

	/** SetDummy
	*/
	template < typename T > inline void SetDummy(T& a_vertex , f32 a_dummy)
	{
		NImpl::Model_Vertex_SetDummy< T , is_convertible< NImpl::Model_Vertex_Convertible< T >* , NImpl::Model_Vertex_SetDummy< T , true >* >::value >::Set(a_vertex,a_dummy);
	}
	template < typename T > inline s32 GetDummyOffset()
	{
		return NImpl::Model_Vertex_SetDummy< T , is_convertible< NImpl::Model_Vertex_Convertible< T >*, NImpl::Model_Vertex_SetDummy< T , true >* >::value >::GetOffset();
	}
}}
#endif


/** include
*/
#include "./model.inl"

