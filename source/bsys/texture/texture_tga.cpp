

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �e�N�X�`���[�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_tga.h"
#include "./texture.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** HEADER_TGA
	*/
	#pragma pack(1)
	struct HEADER_TGA
	{
		/** ID�t�B�[���h���B
		*/
		u8	h_IDLength;

		/** �J���[�}�b�v�^�C�v(�J���[�}�b�v�̗L��)�B
		*/
		u8	h_colorMap;

		/** �摜�^�C�v�B

		0	: �C���[�W�f�[�^����
		1	: �J���[�}�b�v�C���[�W
		2	: RGB�J���[�C���[�W
		3	: �����C���[�W
		9	: ���������O�X���k�J���[�}�b�v�C���[�W
		10	: ���������O�X���kRGB�J���[�C���[�W
		11	: ���������O�X���k�����C���[�W
		32	: �J���[�}�b�v�f�[�^���n�t�}��/�f���^/���������O�X���k
		33	: �J���[�}�b�v�f�[�^���n�t�}��/�f���^/���������O�X���k 4�p�X4���؏���

		*/
		u8	h_imgType;

		/** �J���[�}�b�v���_�B
		*/
		u16	h_colorMapEntry;

		/** �J���[�}�b�v���B
		*/
		u16	h_colorMapLength;

		/** �J���[�}�b�v�[�x(�J���[�}�b�v�G���g���[�T�C�Y)�B
		*/
		u8	h_colorMapSize;

		/** �摜X�������_�B
		*/
		u16	h_x;

		/** �摜Y�������_�B
		*/
		u16	h_y;

		/** �摜���B
		*/
		u16	h_w;

		/** �摜�����B
		*/
		u16	h_h;

		/** �摜�[�x(�摜�s�N�Z���T�C�Y)�B
		*/
		u8	h_bitDepth;

		/** �摜�f�X�N���v�^�B

		00001111 & 0x0F : �A���t�@�`�����l���[�x
		00010000 & 0x10 : X�����i�[���@ / 0: ������E���� / 1: �E���牺����
		00100000 & 0x20 : Y�����i�[���@ / 0: ���������� / 1: �ォ�牺����
		11000000 & 0xC0 : �C���^�[���[�u�t���O

		*/
		u8	h_img;
	};
	#pragma pack()


	/** CreateTexture_FromTga
	*/
	sharedptr< Texture > CreateTexture_FromTga(const sharedptr< u8 >& a_data,s32 a_size,const STLWString& a_name)
	{
		const HEADER_TGA* t_header = reinterpret_cast< const HEADER_TGA* >(a_data.get());

		sharedptr< u8 > t_pixel(new u8[t_header->h_w * t_header->h_h * 4],default_delete< u8[] >());
		{
			const u8* t_src = a_data.get() + (sizeof(HEADER_TGA) + t_header->h_IDLength);
			u32* t_dst = reinterpret_cast< u32* >(t_pixel.get());
			u32* t_dst_end = t_dst + (t_header->h_w * t_header->h_h);

			s32 stride = t_header->h_bitDepth / 8;
			while(t_dst != t_dst_end){
				u8 val = *t_src;
				t_src++;

				u8 num = (val & 0x7f) + 1;
				if(val & 0x80){
					u32 t_color = 0xffffffff;
					if(stride == 3){
						u32 b = *t_src;
						t_src++;
						u32 g = *t_src;
						t_src++;
						u32 r = *t_src;
						t_src++;
						u32 a = 0xff;

						t_color = (a<<24) | (b<<16) |( g<<8) |(r);
					}else if(stride == 4){
						u32 b = *t_src;
						t_src++;
						u32 g = *t_src;
						t_src++;
						u32 r = *t_src;
						t_src++;
						u32 a = *t_src;
						t_src++;

						t_color = (a<<24) | (b<<16) |( g<<8) |(r);
					}
					for(s32 i=0; i<num; i++){
						*t_dst = t_color;
						t_dst++;
					}
				}else{
					for(s32 i=0; i<num; i++){
						if(stride == 3){
							u32 b = *t_src;
							t_src++;
							u32 g = *t_src;
							t_src++;
							u32 r = *t_src;
							t_src++;
							u32 a = 0xff;

							u32 col = (a<<24) | (b<<16) |( g<<8) |(r);
							*t_dst = col;
							t_dst++;
						}else if(stride == 4){
							u32 b = *t_src;
							t_src++;
							u32 g = *t_src;
							t_src++;
							u32 r = *t_src;
							t_src++;
							u32 a = *t_src;
							t_src++;

							u32 t_color = (a<<24) | (b<<16) |( g<<8) |(r);
							*t_dst = t_color;
							t_dst++;
						}
					}
				}
			}
		}

		sharedptr< Texture > t_texture(new Texture(t_pixel,t_header->h_w,t_header->h_h,t_header->h_w * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}

}}

