#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief バーテックス。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NVertex
*/
#if(BSYS_VERTEX_ENABLE)
namespace NBsys{namespace NVertex
{
	/** Vertex_Data_Pos3
	*/
	struct Vertex_Data_Pos3
	{
		union
		{
			struct
			{
				f32 pos_xx;
				f32 pos_yy;
				f32 pos_zz;
			};
		};
	};


	/** Vertex_Data_Pos3Color4
	*/
	struct Vertex_Data_Pos3Color4
	{
		union
		{
			struct
			{
				f32 pos_xx;
				f32 pos_yy;
				f32 pos_zz;

				f32 color_rr;
				f32 color_gg;
				f32 color_bb;
				f32 color_aa;
			};
		};
	};


	/** Vertex_Data_Pos4Color3
	*/
	struct Vertex_Data_Pos4Color3
	{
		union
		{
			struct
			{
				f32 pos_xx;
				f32 pos_yy;
				f32 pos_zz;
				f32 pos_ww;

				f32 color_rr;
				f32 color_gg;
				f32 color_bb;
			};
		};
	};


	/** Vertex_Data_Pos3Uv2Color4
	*/
	struct Vertex_Data_Pos3Uv2Color4
	{
		union
		{
			struct
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
		};
	};


	/** Vertex_Data_Pos3Uv2Color4TextureIndex4
	*/
	struct Vertex_Data_Pos3Uv2Color4TextureIndex4
	{
		union
		{
			struct
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
		};
	};


	/** Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4
	*/
	struct Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4
	{
		union
		{
			struct
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
		};
	};


	namespace NImpl
	{
		/** Vertex_SetPos_XX
		*/
		template <typename T,bool EXIST> struct Vertex_SetPos_XX
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_pos_xx){}
		};


		/** Vertex_SetPos_XX<T,true>
		*/
		template <typename T> struct Vertex_SetPos_XX<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->pos_xx)));
			}
			static void Set(T& a_vertex,f32 a_pos_xx)
			{
				a_vertex.pos_xx = a_pos_xx;
			}
		};


		/** Vertex_SetPos_YY
		*/
		template <typename T,bool EXIST> struct Vertex_SetPos_YY
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_pos_yy){}
		};


		/** Vertex_SetPos_YY<T,true>
		*/
		template <typename T> struct Vertex_SetPos_YY<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->pos_yy)));
			}
			static void Set(T& a_vertex,f32 a_pos_yy)
			{
				a_vertex.pos_yy = a_pos_yy;
			}
		};


		/** Vertex_SetPos_ZZ
		*/
		template <typename T,bool EXIST> struct Vertex_SetPos_ZZ
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_pos_zz){}
		};

		
		/** Vertex_SetPos_ZZ<T,true>
		*/
		template <typename T> struct Vertex_SetPos_ZZ<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->pos_zz)));
			}
			static void Set(T& a_vertex,f32 a_pos_zz)
			{
				a_vertex.pos_zz = a_pos_zz;
			}
		};


		/** Vertex_SetPos_WW
		*/
		template <typename T,bool EXIST> struct Vertex_SetPos_WW
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& /*a_vertex*/,f32 /*a_pos_ww*/){}
		};


		/** Vertex_SetPos_WW<T,true>
		*/
		template <typename T> struct Vertex_SetPos_WW<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->pos_ww)));
			}
			static void Set(T& a_vertex,f32 a_pos_ww)
			{
				a_vertex.pos_ww = a_pos_ww;
			}
		};

		
		/** Vertex_SetColor_RR
		*/
		template <typename T,bool EXIST> struct Vertex_SetColor_RR
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_color_rr){}
		};


		/** Vertex_SetColor_RR
		*/
		template <typename T> struct Vertex_SetColor_RR<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->color_rr)));
			}
			static void Set(T& a_vertex,f32 a_color_rr)
			{
				a_vertex.color_rr = a_color_rr;
			}
		};


		//Vertex_SetColor_GG
		template <typename T,bool EXIST> struct Vertex_SetColor_GG
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_color_gg){}
		};


		/** Vertex_SetColor_GG
		*/
		template <typename T> struct Vertex_SetColor_GG<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->color_gg)));
			}
			static void Set(T& a_vertex,f32 a_color_gg)
			{
				a_vertex.color_gg = a_color_gg;
			}
		};


		/** Vertex_SetColor_BB
		*/
		template <typename T,bool EXIST> struct Vertex_SetColor_BB
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_color_bb){}
		};
		template <typename T> struct Vertex_SetColor_BB<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->color_bb)));
			}
			static void Set(T& a_vertex,f32 a_color_bb)
			{
				a_vertex.color_bb = a_color_bb;
			}
		};


		/** Vertex_SetColor_AA
		*/
		template <typename T,bool EXIST> struct Vertex_SetColor_AA
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_color_aa){}
		};


		/** Vertex_SetColor_AA
		*/
		template <typename T> struct Vertex_SetColor_AA<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->color_aa)));
			}
			static void Set(T& a_vertex,f32 a_color_aa)
			{
				a_vertex.color_aa = a_color_aa;
			}
		};


		/** Vertex_SetUv_XX
 		*/
		template <typename T,bool EXIST> struct Vertex_SetUv_XX
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_uv_xx){}
		};

		/** Vertex_SetUv_XX<T,true>
		*/
		template <typename T> struct Vertex_SetUv_XX<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->uv_xx)));
			}
			static void Set(T& a_vertex,f32 a_uv_xx)
			{
				a_vertex.uv_xx = a_uv_xx;
			}
		};


		/** Vertex_SetUv_YY
		*/
		template <typename T,bool EXIST> struct Vertex_SetUv_YY
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_uv_yy){}
		};

		/** Vertex_SetUv_YY<T,true>
		*/
		template <typename T> struct Vertex_SetUv_YY<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->uv_yy)));
			}
			static void Set(T& a_vertex,f32 a_uv_yy)
			{
				a_vertex.uv_yy = a_uv_yy;
			}
		};


		/** Vertex_SetMatrixindex4
		*/
		template <typename T,bool EXIST> struct Vertex_SetMatrixindex4
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3){}
		};


		/** Vertex_SetMatrixindex4<T,true>
		*/
		template <typename T> struct Vertex_SetMatrixindex4<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->matrix_index_0)));
			}
			static void Set(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3)
			{
				a_vertex.matrix_index_0 = a_matrix_index_0;
				a_vertex.matrix_index_1 = a_matrix_index_1;
				a_vertex.matrix_index_2 = a_matrix_index_2;
				a_vertex.matrix_index_3 = a_matrix_index_3;
			}
		};


		/** Vertex_SetMatrixweight4
		*/
		template <typename T,bool EXIST> struct Vertex_SetMatrixweight4
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3){}
		};


		/** Vertex_SetMatrixweight4<T,true>
		*/
		template <typename T> struct Vertex_SetMatrixweight4<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->matrix_weight_0)));
			}
			static void Set(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3)
			{
				a_vertex.matrix_weight_0 = a_matrix_weight_0;
				a_vertex.matrix_weight_1 = a_matrix_weight_1;
				a_vertex.matrix_weight_2 = a_matrix_weight_2;
				a_vertex.matrix_weight_3 = a_matrix_weight_3;
			}
		};


		/** Vertex_SetDummy
		*/
		template <typename T,bool EXIST> struct Vertex_SetDummy
		{
			static s32 GetOffset(){return 0;}
			static void Set(T& a_vertex,f32 a_dummy){}
		};


		/** Vertex_SetDummy<T,true>
		*/
		template <typename T> struct Vertex_SetDummy<T,true>
		{
			static s32 GetOffset()
			{
				return static_cast<s32>(reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(nullptr)->dummy)));
			}
			static void Set(T& a_vertex,f32 a_dummy)
			{
				a_vertex.dummy = a_dummy;
			}
		};


		/** Vertex_Convertible
		*/
		template <typename T> class Vertex_Convertible;


		/** Vertex_Convertible<Vertex_Data_Pos3>
		*/
		template <> class Vertex_Convertible<Vertex_Data_Pos3>
			:
			public Vertex_SetPos_XX<Vertex_Data_Pos3,true>,
			public Vertex_SetPos_YY<Vertex_Data_Pos3,true>,
			public Vertex_SetPos_ZZ<Vertex_Data_Pos3,true>
		{
		};


		/** Vertex_Convertible<Vertex_Data_Pos3Color4>
		*/
		template <> class Vertex_Convertible<Vertex_Data_Pos3Color4>
			:
			public Vertex_SetPos_XX<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetPos_YY<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetPos_ZZ<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetColor_RR<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetColor_GG<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetColor_BB<Vertex_Data_Pos3Color4,true>,
			public Vertex_SetColor_AA<Vertex_Data_Pos3Color4,true>
		{
		};


		/** Vertex_Convertible<Vertex_Data_Pos4Color3>
		*/
		template <> class Vertex_Convertible<Vertex_Data_Pos4Color3>
			:
			public Vertex_SetPos_XX<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetPos_YY<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetPos_ZZ<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetPos_WW<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetColor_RR<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetColor_GG<Vertex_Data_Pos4Color3,true>,
			public Vertex_SetColor_BB<Vertex_Data_Pos4Color3,true>
		{
		};


		/** Vertex_Convertible<Vertex_Data_Pos3Uv2Color4>
		*/
		template <> class Vertex_Convertible<Vertex_Data_Pos3Uv2Color4>
			:
			public Vertex_SetPos_XX<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetPos_YY<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetPos_ZZ<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetUv_XX<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetUv_YY<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetColor_RR<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetColor_GG<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetColor_BB<Vertex_Data_Pos3Uv2Color4,true>,
			public Vertex_SetColor_AA<Vertex_Data_Pos3Uv2Color4,true>
		{
		};


		/** Vertex_Convertible<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4>
		*/
		template <> class Vertex_Convertible<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4>
			:
			public Vertex_SetPos_XX<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetPos_YY<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetPos_ZZ<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetUv_XX<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetUv_YY<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetMatrixindex4<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>,
			public Vertex_SetMatrixweight4<Vertex_Data_Pos3Uv2Matrixindex4Matrixweight4,true>
		{
		};


	}


	/** SetPos_XX
	*/
	template <typename T> inline void SetPos_XX(T& a_vertex,f32 a_pos_xx)
	{
		NImpl::Vertex_SetPos_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_XX<T,true>*>::value>::Set(a_vertex,a_pos_xx);
	}


	/** GetPosOffset_XX
	*/
	template <typename T> inline s32 GetPosOffset_XX()
	{
		return NImpl::Vertex_SetPos_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_XX<T,true>*>::value>::GetOffset();
	}


	/** SetPos_YY
	*/
	template <typename T> inline void SetPos_YY(T& a_vertex,f32 a_pos_yy)
	{
		NImpl::Vertex_SetPos_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_YY<T,true>*>::value>::Set(a_vertex,a_pos_yy);
	}


	/** GetPosOffset_YY
	*/
	template <typename T> inline s32 GetPosOffset_YY()
	{
		return NImpl::Vertex_SetPos_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_YY<T,true>*>::value>::GetOffset();
	}


	/** SetPos_ZZ
	*/
	template <typename T> inline void SetPos_ZZ(T& a_vertex,f32 a_pos_zz)
	{
		NImpl::Vertex_SetPos_ZZ<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_ZZ<T,true>*>::value>::Set(a_vertex,a_pos_zz);
	}

	
	/** GetPosOffset_ZZ
	*/
	template <typename T> inline s32 GetPosOffset_ZZ()
	{
		return NImpl::Vertex_SetPos_ZZ<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_ZZ<T,true>*>::value>::GetOffset();
	}


	/** SetPos_WW
	*/
	template <typename T> inline void SetPos_WW(T& a_vertex,f32 a_pos_ww)
	{
		NImpl::Vertex_SetPos_WW<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_WW<T,true>*>::value>::Set(a_vertex,a_pos_ww);
	}


	/** GetPosOffset_WW
	*/
	template <typename T> inline s32 GetPosOffset_WW()
	{
		return NImpl::Vertex_SetPos_WW<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetPos_WW<T,true>*>::value>::GetOffset();
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


	/** SetColor_RR
	*/
	template <typename T> inline void SetColor_RR(T& a_vertex,f32 a_color_rr)
	{
		NImpl::Vertex_SetColor_RR<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_RR<T,true>*>::value>::Set(a_vertex,a_color_rr);
	}

	
	/** GetColorOffset_RR
	*/
	template <typename T> inline s32 GetColorOffset_RR()
	{
		return NImpl::Vertex_SetColor_RR<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_RR<T,true>*>::value>::GetOffset();
	}


	/** SetColor_GG
	*/
	template <typename T> inline void SetColor_GG(T& a_vertex,f32 a_color_gg)
	{
		NImpl::Vertex_SetColor_GG<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_GG<T,true>*>::value>::Set(a_vertex,a_color_gg);
	}

	
	/** GetColorOffset_GG
	*/
	template <typename T> inline s32 GetColorOffset_GG()
	{
		return NImpl::Vertex_SetColor_GG<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_GG<T,true>*>::value>::GetOffset();
	}


	/** SetColor_BB
	*/
	template <typename T> inline void SetColor_BB(T& a_vertex,f32 a_color_bb)
	{
		NImpl::Vertex_SetColor_BB<T,is_convertible<NImpl::Vertex_Convertible<T>*, NImpl::Vertex_SetColor_BB<T,true>*>::value>::Set(a_vertex,a_color_bb);
	}


	/** GetColorOffset_BB
	*/
	template <typename T> inline s32 GetColorOffset_BB()
	{
		return NImpl::Vertex_SetColor_BB<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_BB<T,true>*>::value>::GetOffset();
	}


	/** SetColor_AA
	*/
	template <typename T> inline void SetColor_AA(T& a_vertex,f32 a_color_aa)
	{
		NImpl::Vertex_SetColor_AA<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_AA<T,true>*>::value>::Set(a_vertex,a_color_aa);
	}

	
	/** GetColorOffset_AA
	*/
	template <typename T> inline s32 GetColorOffset_AA()
	{
		return NImpl::Vertex_SetColor_AA<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetColor_AA<T,true>*>::value>::GetOffset();
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


	/** SetUv_XX
	*/
	template <typename T> inline void SetUv_XX(T& a_vertex,f32 a_uv_xx)
	{
		NImpl::Vertex_SetUv_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_XX<T,true>*>::value>::Set(a_vertex,a_uv_xx);
	}

	
	/** GetUvOffset_XX
	*/
	template <typename T> inline s32 GetUvOffset_XX()
	{
		return NImpl::Vertex_SetUv_XX<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_XX<T,true>*>::value>::GetOffset();
	}


	/** SetUv_YY
	*/
	template <typename T> inline void SetUv_YY(T& a_vertex,f32 a_uv_yy)
	{
		NImpl::Vertex_SetUv_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_YY<T,true>*>::value>::Set(a_vertex,a_uv_yy);
	}


	/** GetUvOffset_YY
	*/
	template <typename T> inline s32 GetUvOffset_YY()
	{
		return NImpl::Vertex_SetUv_YY<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetUv_YY<T,true>*>::value>::GetOffset();
	}


	/** SetUv
	*/
	template <typename T> inline void SetUv(T& a_vertex,f32 a_uv_xx = 0.0f,f32 a_uv_yy = 0.0f)
	{
		SetUv_XX<T>(a_vertex,a_uv_xx);
		SetUv_YY<T>(a_vertex,a_uv_yy);
	}


	/** SetMatrixIndex
	*/
	template <typename T> inline void SetMatrixIndex(T& a_vertex,s32 a_matrix_index_0,s32 a_matrix_index_1,s32 a_matrix_index_2,s32 a_matrix_index_3)
	{
		NImpl::Vertex_SetMatrixindex4<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetMatrixindex4<T,true>*>::value>::Set(a_vertex,a_matrix_index_0,a_matrix_index_1,a_matrix_index_2,a_matrix_index_3);
	}
	template <typename T> inline s32 GetMatrixIndexOffset()
	{
		return NImpl::Vertex_SetMatrixindex4<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetMatrixindex4<T,true>*>::value>::GetOffset();
	}


	/** SetMatrixWeight
	*/
	template <typename T> inline void SetMatrixWeight(T& a_vertex,f32 a_matrix_weight_0,f32 a_matrix_weight_1,f32 a_matrix_weight_2,f32 a_matrix_weight_3)
	{
		NImpl::Vertex_SetMatrixweight4<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetMatrixweight4<T,true>*>::value>::Set(a_vertex,a_matrix_weight_0,a_matrix_weight_1,a_matrix_weight_2,a_matrix_weight_3);
	}


	/** GetMatrixWeightOffset
	*/
	template <typename T> inline s32 GetMatrixWeightOffset()
	{
		return NImpl::Vertex_SetMatrixweight4<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetMatrixweight4<T,true>*>::value>::GetOffset();
	}


	/** SetDummy
	*/
	template <typename T> inline void SetDummy(T& a_vertex,f32 a_dummy)
	{
		NImpl::Vertex_SetDummy<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetDummy<T,true>*>::value>::Set(a_vertex,a_dummy);
	}


	/** GetDummyOffset
	*/
	template <typename T> inline s32 GetDummyOffset()
	{
		return NImpl::Vertex_SetDummy<T,is_convertible<NImpl::Vertex_Convertible<T>*,NImpl::Vertex_SetDummy<T,true>*>::value>::GetOffset();
	}


}}
#endif


