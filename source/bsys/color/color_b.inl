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


/** NBsys::NColor
*/
namespace NBsys{namespace NColor
{

	/** constructor。
	*/
	inline Color_B::Color_B()
	{
	}

	/** constructor。
	*/
	inline Color_B::Color_B(u8 a_r,u8 a_g,u8 a_b,u8 a_a)
	{
		this->B_Set(a_r,a_g,a_b,a_a);
	}

	/** constructor。
	*/
	inline Color_B::Color_B(const Color_B& a_color)
	{
		this->B_SetColor(a_color);
	}

	/** constructor。
	*/
	inline Color_B::Color_B(const Color_F& a_color)
	{
		this->F_SetColor(a_color);
	}

	/** 代入。
	*/
	inline Color_B& Color_B::operator =(const Color_F& a_color)
	{
		this->F_SetColor(a_color);

		return *this;
	}

	/** B_SetColor
	*/
	inline void Color_B::B_SetColor(const Color_B& a_color)
	{
		this->B_Set(a_color.r,a_color.g,a_color.b,a_color.a);
	}

	/** F_SetColor
	*/
	inline void Color_B::F_SetColor(const Color_F& a_color)
	{
		this->F_Set(a_color.r,a_color.g,a_color.b,a_color.a);
	}

	/** Set8
	*/
	inline void Color_B::B_Set(u8 a_r,u8 a_g,u8 a_b,u8 a_a)
	{
		this->B_SetR(a_r);
		this->B_SetG(a_g);
		this->B_SetB(a_b);
		this->B_SetA(a_a);
	}

	/** SetF
	*/
	inline void Color_B::F_Set(f32 a_r,f32 a_g,f32 a_b,f32 a_a)
	{
		this->F_SetR(a_r);
		this->F_SetG(a_g);
		this->F_SetB(a_b);
		this->F_SetA(a_a);
	}

	/** B_GetR
	*/
	inline u8 Color_B::B_GetR() const
	{
		return this->r;
	}

	/** B_GetG
	*/
	inline u8 Color_B::B_GetG() const
	{
		return this->g;
	}

	/** B_GetB
	*/
	inline u8 Color_B::B_GetB() const
	{
		return this->b;
	}

	/** B_GetA
	*/
	inline u8 Color_B::B_GetA() const
	{
		return this->a;
	}

	/** F_GetR
	*/
	inline f32 Color_B::F_GetR() const
	{
		f32 t_r = static_cast<f32>(this->r / 255.0f);
		return t_r;
	}

	/** F_GetG
	*/
	inline f32 Color_B::F_GetG() const
	{
		f32 t_g = static_cast<f32>(this->g / 255.0f);
		return t_g;
	}

	/** F_GetB
	*/
	inline f32 Color_B::F_GetB() const
	{
		f32 t_b = static_cast<f32>(this->b / 255.0f);
		return t_b;
	}

	/** F_GetA
	*/
	inline f32 Color_B::F_GetA() const
	{
		f32 t_a = static_cast<f32>(this->a / 255.0f);
		return t_a;
	}

	/** B_SetR
	*/
	inline void Color_B::B_SetR(u8 a_r)
	{
		this->r = a_r;
	}

	/** B_SetG
	*/
	inline void Color_B::B_SetG(u8 a_g)
	{
		this->g = a_g;
	}

	/** B_SetB
	*/
	inline void Color_B::B_SetB(u8 a_b)
	{
		this->b = a_b;
	}

	/** B_SetA
	*/
	inline void Color_B::B_SetA(u8 a_a)
	{
		this->a = a_a;
	}

	/** F_SetR
	*/
	inline void Color_B::F_SetR(f32 a_r)
	{
		this->r = static_cast<u8>(255 * a_r);
	}

	/** F_SetG
	*/
	inline void Color_B::F_SetG(f32 a_g)
	{
		this->g = static_cast<u8>(255 * a_g);
	}

	/** F_SetB
	*/
	inline void Color_B::F_SetB(f32 a_b)
	{
		this->b = static_cast<u8>(255 * a_b);
	}

	/** F_SetA
	*/
	inline void Color_B::F_SetA(f32 a_a)
	{
		this->a = static_cast<u8>(255 * a_a);
	}

}}

