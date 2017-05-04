#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �R���t�B�O�B
*/


/*

	std atomic

*/
#define BLIB_STDATOMIC_ENABLE							(1)

/*

	�O���[�o���B�Œ蒷�A���P�[�^�B

*/
#define BLIB_GLOBALFIXEDALLOCATOR_ENABLE				(1)
#define BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE				(32)
#define BLIB_GLOBALFIXEDALLOCATOR_SIZE					(1 * 1024 * 1024)

/*

	�f�o�b�O�A�T�[�g�B

*/
#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)


/*

	�f�o�b�O�u���C�N�B

*/
#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)

/*

	�f�o�b�O���O�B

*/
#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)

/*

	�t�@�C���n���h���B�v���b�N�T�C�Y�B

*/
#define BLIB_FILEHANDLE_BLOCKSIZE						(4096)

/*

	�t�@�C���n���h���B���g���C�񐔁B

*/
#define BLIB_FILEHANDLE_RETRYMAX						(15)

/*

	std regex

*/
#define BLIB_STDREGEX_ENABLE							(1)

/*

	std mutex

*/
#define BLIB_STDMUTEX_ENABLE							(1)

/*

	Math::sin_fast / Math::cos_fast �̃e�[�u���T�C�Y�B

*/
#define BLIB_MATH_SINCOSFAST_TABLESIZE					(4096)

/*

	�������[�R���e�i�[�B

*/
#define BLIB_MEMORYCONTAINER_ENABLE						(1)

/*

	�������[�R���e�i�[�B�l�X�g�ő�l�B

*/
#define BLIB_MEMORYCONTAINER_NESTMAX					(16)

/*

	�������[�R���e�i�[�B�X���b�h���[�J���X���b�g�B

*/
#define BLIB_MEMORYCONTAINER_THREADLOCALSLOT			(0x01)

/*

	std random

*/
#define BLIB_STDRANDOM_ENABLE							(1)

/*

	std sharedptr

*/
#define BLIB_STDSHAREDPTR_ENABLE						(0)

/*

	�V�F�A�[�h�|�C���^�B�L���b�V���B

*/
#define BLIB_SHAREDPTR_CACHE_ENABLE						(1)

/*

	std nullptr

*/
#define BLIB_STDNULLPTR_ENABLE							(1)

/*

	�i�r�n�m�A�C�e���B

*/
#define BLIB_JSONITEM_ENABLE							(1)

/*

	�X�^�b�N�g���[�X�B

*/
#define BLIB_STACKTRACE_ENABLE							(1)

/*

	std thread

*/
#define BLIB_STDTHREAD_ENABLE							(1)

/*

	std threadlocal

*/
#define BLIB_STDTHREADLOCAL_ENABLE						(1)

/*

	�X���b�h���[�J���B�\���b�g���B

*/
#define BLIB_THREADLOCAL_SLOTMAX						(32)

/*

	�X���b�h���[�J���B

*/
#define BLIB_THREADLOCAL_ENABLE							(1)

/*

	�ψ��������񑀍�B�f�o�b�O�p�B�X���b�h���[�J���X���b�g�B

*/
#define BLIB_VASTRING_DEBUG_THREADLOCALSLOT				(0x00)

/*

	�ψ��������񑀍�B�f�o�b�O�p�B�T�C�Y�B

*/
#define BLIB_VASTRING_DEBUG_SIZE						(4 * 1024)

/*

	std unordered_map

*/
#define BLIB_STDUNORDEREDMAP_ENABLE						(1)

/*

	std alias template

*/
#define BLIB_STDALIASTEMPLATE_ENABLE					(1)















/*

	actionbatching

*/
#define BSYS_ACTIONBATCHING_ENABLE						(1)

/*

	color

*/
#define BSYS_COLOR_ENABLE								(1)

/*

	file

	BSYS_FILE_LISTSIZE	: �������N�G�X�g���B

*/
#define BSYS_FILE_ENABLE								(1)
#define BSYS_FILE_PACK_ENABLE							(1)
#define BSYS_FILE_MEMORYCONTAINER						(0x01)
#define BSYS_FILE_LISTSIZE								(512)

/*

	model

*/
#define BSYS_MODEL_ENABLE								(1)

/*

	opengl

*/
#define BSYS_OPENGL_ENABLE								(0)
#define BSYS_OPENGL_UPDATE_FPS							(60)
#define BSYS_OPENGL_WIDTH								(1440)
#define BSYS_OPENGL_HEIGHT								(810)
#define BSYS_OPENGL_SHADERIDMAX							(32)

/*

	geometry

*/
#define BSYS_GEOMETRY_ENABLE							(1)
#define BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE			(1)
#define BSYS_GEOMETRY_PERSPECTIVE_TYPE					(0x01)
#define BSYS_GEOMETRY_ROWCOLUMN_TYPE					(0x01)
#define BSYS_GEOMETRY_LEFTRIGHT_TYPE					(0x01)

/*

	fovehmd

*/
#define BSYS_FOVEHMD_ENABLE								(1)



/** user.h
*/
#include "./user_customize.h"

