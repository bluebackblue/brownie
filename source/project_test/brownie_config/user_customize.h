#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ���[�U�[�J�X�^�}�C�Y�p�w�b�_�[�B
*/


/** DEF_TEST

	DEF_TEST0	:	�f�o�b�O���O�A�f�o�b�O�u���C�N�A�A�T�[�g�B
	DEF_TEST1	:	�^�A���X�g�B
	DEF_TEST2	:	�t�@�C���A�i�r�n�m�B

	DEF_TEST10	:	�c�R�c�P�P�B
	DEF_TEST11	:	�_�C�N�X�g���@�B
	DEF_TEST12	:	�f�o�b�O���j���[�B

*/
#define DEF_TEST12


#if defined(DEF_TEST0)

#elif defined(DEF_TEST1)

#elif defined(DEF_TEST2)

#elif defined(DEF_TEST3)

#elif defined(DEF_TEST10)

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)

#elif defined(DEF_TEST11)

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_ROOTSEARCH_ENABLE							(1)

#elif defined(DEF_TEST12)

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FONT_ENABLE								(1)
	#define BSYS_PAD_ENABLE									(1)

#elif defined(DEF_TEST22)

	#define BSYS_MMD_PMX_ENABLE								(1)
	#define BSYS_MMD_VMD_ENABLE								(1)
	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FOVEHMD_ENABLE								(1)
	#define BSYS_TEXTURE_ENABLE								(1)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)

#endif

