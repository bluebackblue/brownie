#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 色。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./color_b.h"
#include "./color_f.h"


/** NBsys::NColor
*/
#if(BSYS_COLOR_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NColor
{
	/** r
	*/
	inline const f32& Color_F::r() const
	{
		return this->raw.c.r;
	}


	/** r
	*/
	inline f32& Color_F::r(){
		return this->raw.c.r;
	}


	/** g
	*/
	inline const f32& Color_F::g() const
	{
		return this->raw.c.g;
	}


	/** g
	*/
	inline f32& Color_F::g()
	{
		return this->raw.c.g;
	}


	/** b
	*/
	inline const f32& Color_F::b() const
	{
		return this->raw.c.b;
	}


	/** b
	*/
	inline f32& Color_F::b(){
		return this->raw.c.b;
	}


	/** a
	*/
	inline const f32& Color_F::a() const
	{
		return this->raw.c.a;
	}


	/** a
	*/
	inline f32& Color_F::a()
	{
		return this->raw.c.a;
	}


	/** constructor
	*/
	inline Color_F::Color_F()
	{
	}


	/** constructor
	*/
	inline Color_F::Color_F(f32 a_r,f32 a_g,f32 a_b,f32 a_a)
	{
		this->F_Set(a_r,a_g,a_b,a_a);
	}


	/** constructor
	*/
	inline Color_F::Color_F(const Color_F& a_color)
	{
		this->F_SetColor(a_color);
	}


	/** constructor
	*/
	inline Color_F::Color_F(const Color_B& a_color)
	{
		this->B_SetColor(a_color);
	}


	/** 代入。
	*/
	inline Color_F& Color_F::operator =(const Color_B& a_color)
	{
		this->B_SetColor(a_color);

		return *this;
	}


	/** SetColorF
	*/
	inline void Color_F::F_SetColor(const Color_F& a_color)
	{
		this->F_Set(a_color.r(),a_color.g(),a_color.b(),a_color.a());
	}


	/** SetColorB
	*/
	inline void Color_F::B_SetColor(const Color_B& a_color)
	{
		this->B_Set(a_color.r(),a_color.g(),a_color.b(),a_color.a());
	}


	/** SetF
	*/
	inline void Color_F::F_Set(f32 a_r,f32 a_g,f32 a_b,f32 a_a)
	{
		this->F_SetR(a_r);
		this->F_SetG(a_g);
		this->F_SetB(a_b);
		this->F_SetA(a_a);
	}


	/** SetB
	*/
	inline void Color_F::B_Set(u8 a_r,u8 a_g,u8 a_b,u8 a_a)
	{
		this->B_SetR(a_r);
		this->B_SetG(a_g);
		this->B_SetB(a_b);
		this->B_SetA(a_a);
	}


	/** F_GetR
	*/
	inline f32 Color_F::F_GetR() const
	{
		return this->r();
	}


	/** F_GetG
	*/
	inline f32 Color_F::F_GetG() const
	{
		return this->g();
	}


	/** F_GetB
	*/
	inline f32 Color_F::F_GetB() const
	{
		return this->b();
	}


	/** F_GetA
	*/
	inline f32 Color_F::F_GetA() const
	{
		return this->a();
	}


	/** B_GetR
	*/
	inline u8 Color_F::B_GetR() const
	{
		u8 t_r = static_cast<u8>(255 * this->r());
		return t_r;
	}


	/** B_GetG
	*/
	inline u8 Color_F::B_GetG() const
	{
		u8 t_g = static_cast<u8>(255 * this->g());
		return t_g;
	}


	/** B_GetB
	*/
	inline u8 Color_F::B_GetB() const
	{
		u8 t_b = static_cast<u8>(255 * this->b());
		return t_b;
	}


	/** B_GetA
	*/
	inline u8 Color_F::B_GetA() const
	{
		u8 t_a = static_cast<u8>(255 * this->a());
		return t_a;
	}


	/** F_SetR
	*/
	inline void Color_F::F_SetR(f32 a_r)
	{
		this->r() = a_r;
	}


	/** F_SetG
	*/
	inline void Color_F::F_SetG(f32 a_g)
	{
		this->g() = a_g;
	}


	/** F_SetB
	*/
	inline void Color_F::F_SetB(f32 a_b)
	{
		this->b() = a_b;
	}


	/** F_SetA
	*/
	inline void Color_F::F_SetA(f32 a_a)
	{
		this->a() = a_a;
	}


	/** B_SetR
	*/
	inline void Color_F::B_SetR(u8 a_r)
	{
		this->r() = (static_cast<f32>(a_r) / 255.0f);
	}


	/** B_SetG
	*/
	inline void Color_F::B_SetG(u8 a_g)
	{
		this->g() = (static_cast<f32>(a_g) / 255.0f);
	}


	/** B_SetB
	*/
	inline void Color_F::B_SetB(u8 a_b)
	{
		this->b() = (static_cast<f32>(a_b) / 255.0f);
	}


	/** B_SetA
	*/
	inline void Color_F::B_SetA(u8 a_a)
	{
		this->a() = (static_cast<f32>(a_a) / 255.0f);
	}


}}
#pragma warning(pop)
#endif

