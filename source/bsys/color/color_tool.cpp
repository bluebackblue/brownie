

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief êFÅB
*/


/** include
*/
#include <asys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./color.h"


/** NAsys::NColor
*/
namespace NAsys{namespace NColor
{

	/** [static]MakeColor_B
	*/
	void Color_Tool::MakeColor_B(Color_B* a_out,Type::Id a_type)
	{
		switch(a_type){

		case Type::BLACK:			a_out->B_Set(0x00,0x00,0x00,0xFF);	break;
		case Type::GRAY:			a_out->B_Set(0x80,0x80,0x80,0xFF);	break;
		case Type::WHITE:			a_out->B_Set(0xFF,0xFF,0xFF,0xFF);	break;
		case Type::RED:				a_out->B_Set(0xFF,0x00,0x00,0xFF);	break;
		case Type::GREEN:			a_out->B_Set(0x00,0xFF,0x00,0xFF);	break;
		case Type::BLUE:			a_out->B_Set(0x00,0x00,0xFF,0xFF);	break;
		case Type::YELLOW:			a_out->B_Set(0xFF,0xFF,0x00,0xFF);	break;
		case Type::MAGENTA:			a_out->B_Set(0xFF,0x00,0xFF,0xFF);	break;
		case Type::CYAN:			a_out->B_Set(0x00,0xFF,0xFF,0xFF);	break;

		default:
			{
			}break;
		}
	}

	/** [static]MakeColor_F
	*/
	void Color_Tool::MakeColor_F(Color_F* a_out,Type::Id a_type)
	{
		switch(a_type){

		case Type::BLACK:			a_out->F_Set(0.0f,0.0f,0.0f,1.0f);	break;
		case Type::GRAY:			a_out->F_Set(0.5f,0.5f,0.5f,1.0f);	break;
		case Type::WHITE:			a_out->F_Set(1.0f,1.0f,1.0f,1.0f);	break;
		case Type::RED:				a_out->F_Set(1.0f,0.0f,0.0f,1.0f);	break;
		case Type::GREEN:			a_out->F_Set(0.0f,1.0f,0.0f,1.0f);	break;
		case Type::BLUE:			a_out->F_Set(0.0f,0.0f,1.0f,1.0f);	break;
		case Type::YELLOW:			a_out->F_Set(1.0f,1.0f,0.0f,1.0f);	break;
		case Type::MAGENTA:			a_out->F_Set(1.0f,0.0f,1.0f,1.0f);	break;
		case Type::CYAN:			a_out->F_Set(0.0f,1.0f,1.0f,1.0f);	break;

		default:
			{
			}break;
		}
	}

	/** [static]MakeColor_B
	*/
	Color_B Color_Tool::MakeColor_B(Type::Id a_type)
	{
		Color_B t_color;

		Color_Tool::MakeColor_B(&t_color,a_type);

		return t_color;
	}

	/** [static]MakeColor_F
	*/
	Color_F Color_Tool::MakeColor_F(Type::Id a_type)
	{
		Color_F t_color;

		Color_Tool::MakeColor_F(&t_color,a_type);

		return t_color;
	}

	/** [static]MakeColor_B_FromARGB
	*/
	Color_B MakeColor_B_FromARGB(u32 a_argb)
	{
		return Color_B(((a_argb&0xFF000000)>>24),((a_argb&0x00FF0000)>>16),((a_argb&0x0000FF00)>>8),(a_argb&0x000000FF));
	}

	/** [static]MakeColor_B_FromRGBA
	*/
	Color_B MakeColor_B_FromRGBA(u32 a_rgba)
	{
		return Color_B(((a_rgba&0x00FF0000)>>16),((a_rgba&0x0000FF00)>>8),(a_rgba&0x000000FF),((a_rgba&0xFF000000)>>24));
	}

	/** [static]MakeColor_F_FromARGB
	*/
	Color_F MakeColor_F_FromARGB(u32 a_argb)
	{
		return Color_B(((a_argb&0xFF000000)>>24),((a_argb&0x00FF0000)>>16),((a_argb&0x0000FF00)>>8),(a_argb&0x000000FF));
	}

	/** [static]MakeColor_F_FromRGBA
	*/
	Color_F MakeColor_F_FromRGBA(u32 a_rgba)
	{
		return Color_B(((a_rgba&0x00FF0000)>>16),((a_rgba&0x0000FF00)>>8),(a_rgba&0x000000FF),((a_rgba&0xFF000000)>>24));
	}

}}

