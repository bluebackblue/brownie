#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メタ。
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
#pragma warning(push)
#pragma warning(disable:4710 4514)
namespace NBlib
{
	/** 削除子。
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


	/** 削除子。
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


	/** 削除子。なにもしない。
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


	/** 削除子。voidは禁止。
	*/
	template <> struct default_delete<void>
	{
	private:
		default_delete() noexcept = delete;
		void operator ()(void* a_instance) const noexcept = delete;
	};


	/** 削除子。placement_delete
	
	「placement new」によって確保されたクラスポインターは明示的にデストラクターを呼び出す必要があります。

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


	/** 削除子。release
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


	/** B==trueの場合のみtypeの宣言が確定する。
	*/
	template <bool B,class T=void> struct enable_if
	{
	};


	/** B==trueの場合のみtypeの宣言が確定する。
	*/
	template <class T> struct enable_if <true,T>
	{
		typedef T type;
	};


	/** 一方の型をもう一方の型に変換できるかどうかをテストします。
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

		/** この関数が使用されると成功。
		*/
		static SUCCESSTYPE ConvertibleProc(TO);

		/** この関数が使用されると失敗。
		*/
		static FAILEDTYPE ConvertibleProc(...);

		/** FROM型を返す関数。
		*/
		static FROM FromTypeProc();

	public:

		/** value
		*/
		static const bool value = sizeof(ConvertibleProc(FromTypeProc())) == sizeof(SUCCESSTYPE);

	};


	/** is_void
	*/
	template <typename T> struct is_void
	{
		static const bool value = false;
	};


	/** is_void
	*/
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


	/** reference_type
	*/
	template <typename T> struct reference_type<T,false>
	{
		typedef T& type;
	};


	/** get_last_iterator
	*/
	template <typename LIST> inline typename LIST::iterator get_last_iterator(LIST& a_list)
	{
		LIST::iterator t_it_last = a_list.end();
		if(a_list.size() > 0){
			--t_it_last;
		}
		return t_it_last;
	}


	/** get_last_const_iterator
	*/
	template <typename LIST> inline typename LIST::const_iterator get_last_const_iterator(const LIST& a_list)
	{
		LIST::const_iterator t_it_last = a_list.cend();
		if(a_list.size() > 0){
			--t_it_last;
		}
		return t_it_last;
	}


}
#pragma warning(pop)

