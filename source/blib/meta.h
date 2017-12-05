#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ���^�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./staticassert.h"


/** NBlib
*/
namespace NBlib
{
	/** �폜�q�B
	*/
	template <typename T> struct default_delete
	{
		default_delete() noexcept
		{
		}
		void operator ()(T* a_instance) const noexcept
		{
			STATIC_ASSERT(0<sizeof(T));

			delete a_instance;
		}
	};

	/** �폜�q�B
	*/
	template <typename T> struct default_delete<T[]>
	{
		default_delete() noexcept
		{
		}
		void operator ()(T* a_instance) const noexcept
		{
			delete [] a_instance;
		}
	};

	/** �폜�q�B�Ȃɂ����Ȃ��B
	*/
	struct null_delete
	{
		null_delete() noexcept
		{
		}
		void operator ()(void* /*a_instance*/) const noexcept
		{
			//NOP.
		}
	};


	/** �폜�q�Bvoid�͋֎~�B
	*/
	template <> struct default_delete<void>
	{
	private:
		default_delete() noexcept = delete;
		void operator ()(void* a_instance) const noexcept = delete;
	};

	/** �폜�q�Bplacement_delete
	
	�uplacement new�v�ɂ���Ċm�ۂ��ꂽ�N���X�|�C���^�[�͖����I�Ƀf�X�g���N�^�[���Ăяo���K�v������܂��B

	*/
	template <class T> struct placement_delete
	{
		placement_delete() noexcept
		{
		}
		void operator ()(T* a_pointer) const throw ()
		{
			a_pointer->~T();
		}
	};

	/** �폜�q�Brelease
	*/
	template <class T> struct release_delete
	{
		release_delete() noexcept
		{
		}
		void operator ()(T* a_instance) const noexcept
		{
			a_instance->Release();
		}
	};

	/** B==true�̏ꍇ�̂�type�̐錾���m�肷��B
	*/
	template <bool B,class T=void> struct enable_if
	{
	};
	template <class T> struct enable_if <true,T>
	{
		typedef T type;
	};

	/** ����̌^����������̌^�ɕϊ��ł��邩�ǂ������e�X�g���܂��B
	*/
	template <class FROM,class TO> struct is_convertible
	{
	private:

		/** SUCCESSTYPE
		*/
		typedef char SUCCESSTYPE;

		/** FAILEDTYPE
		*/
		struct FAILEDTYPE{
			char dummy[2];
		};

		/** ���̊֐����g�p�����Ɛ����B
		*/
		static SUCCESSTYPE ConvertibleProc(TO);

		/** ���̊֐����g�p�����Ǝ��s�B
		*/
		static FAILEDTYPE ConvertibleProc(...);

		/** FROM�^��Ԃ��֐��B
		*/
		static FROM FromTypeProc();

	public:

		static const bool value = sizeof(ConvertibleProc(FromTypeProc())) == sizeof(SUCCESSTYPE);

	};

	/** is_void
	*/
	template <typename T> struct is_void
	{
		static const bool value = false;
	};
	template <> struct is_void<void>
	{
		static const bool value = true;
	};

	/** reference_type
	*/
	template <typename T,bool=(is_void<T>::value)> struct reference_type
	{
		typedef T type;
	};

	template <typename T> struct reference_type<T,false>
	{
		typedef T& type;
	};

}

