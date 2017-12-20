#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 色。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./color_decl.h"


/** NBsys::NColor
*/
#if(BSYS_COLOR_ENABLE)
namespace NBsys{namespace NColor
{
	/** Color_F_Raw
	*/
	struct Color_F_Raw
	{
		union
		{
			struct
			{
				f32 r;
				f32 g;
				f32 b;
				f32 a;
			};

			f32 p[4];
		};
	};


	/** Color_F_Raw is POD
	*/
	STATIC_ASSERT(std::is_pod<Color_F_Raw>::value == true);


	/** Color_F
	*/
	struct Color_F : public Color_F_Raw
	{

		/** constructor
		*/
		inline Color_F();

		/** constructor
		*/
		inline Color_F(f32 a_r,f32 a_g,f32 a_b,f32 a_a);

		/** constructor
		*/
		inline Color_F(const Color_F& a_color);

		/** constructor
		*/
		inline Color_F(const Color_B& a_color);

		/** 代入。
		*/
		inline Color_F& operator =(const Color_B& a_color);

		/** F_SetColor
		*/
		inline void F_SetColor(const Color_F& a_color);

		/** B_SetColor
		*/
		inline void B_SetColor(const Color_B& a_color);

		/** F_Set
		*/
		inline void F_Set(f32 a_r,f32 a_g,f32 a_b,f32 a_a);

		/** B_Set
		*/
		inline void B_Set(u8 a_r,u8 a_g,u8 a_b,u8 a_a);

		/** F_GetR
		*/
		inline f32 F_GetR() const;

		/** F_GetG
		*/
		inline f32 F_GetG() const;

		/** F_GetB
		*/
		inline f32 F_GetB() const;

		/** F_GetA
		*/
		inline f32 F_GetA() const;

		/** B_GetR
		*/
		inline u8 B_GetR() const;

		/** B_GetG
		*/
		inline u8 B_GetG() const;

		/** B_GetB
		*/
		inline u8 B_GetB() const;

		/** B_GetA
		*/
		inline u8 B_GetA() const;

		/** F_SetR
		*/
		inline void F_SetR(f32 a_r);

		/** F_SetG
		*/
		inline void F_SetG(f32 a_g);

		/** F_SetB
		*/
		inline void F_SetB(f32 a_b);

		/** F_SetA
		*/
		inline void F_SetA(f32 a_a);

		/** B_SetR
		*/
		inline void B_SetR(u8 a_r);

		/** B_SetG
		*/
		inline void B_SetG(u8 a_g);

		/** B_SetB
		*/
		inline void B_SetB(u8 a_b);

		/** B_SetA
		*/
		inline void B_SetA(u8 a_a);

	};


}}
#endif

