#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief プロセス空間内でユニークなＩＤ。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"


/*

	ユニーク名が有効なのは「id」が生存している間。

*/


/** NBlib
*/
namespace NBlib
{
	/** Muid_Impl
	*/
	struct Muid_Impl
	{
	private:

		/** 確保。
		*/
		static void* Alloc(size_t a_size);

		/** 解放。
		*/
		static void Free(void* a_pointer);

	public:

		#if defined(new)
		#undef new
		#endif

		/** operator new
		*/
		static void* operator new(size_t a_size) noexcept
		{
			return Muid_Impl::Alloc(a_size);
		}
		
		#if defined(custom_new)
		#define new custom_new
		#endif

		/** operator delete
		*/
		static void operator delete(void* a_pointer)
		{
			Muid_Impl::Free(a_pointer);
		}

	};


	/** Muid
	*/
	class Muid
	{
	private:

		/** id
		*/
		sharedptr<Muid_Impl> id;

	public:

		/** UniqueNameType
		*/
		typedef AddressType UniqueNameType;

	private:

		/** constructor.
		*/
		Muid();

	public:

		/** constructor.
		*/
		explicit Muid(bool a_auto_create)
		{
			if(a_auto_create == true){

				#if defined(new)
				#undef new
				#endif

				this->id.reset(new Muid_Impl());

				#if defined(custom_new)
				#define new custom_new
				#endif

			}else{
				this->id.reset();
			}
		}

		/** copy constructor.
		*/
		Muid(const Muid& a_muid)
			:
			id(a_muid.id)
		{
		}

		/** destructor
		*/
		nonvirtual ~Muid()
		{
			this->id.reset();
		}

	public:

		/** operator ==
		*/
		bool operator ==(const Muid& a_muid) const
		{
			if((this->id.get() == nullptr)||(a_muid.id.get() == nullptr)){
				return false;
			}
			return (this->id.get() == a_muid.id.get());
		}

		/** operator !=
		*/
		bool operator !=(const Muid& a_muid) const
		{
			return !(*this==a_muid);
		}

		/** operator =
		*/
		Muid& operator =(const Muid& a_muid)
		{
			this->id = a_muid.id;

			return (*this);
		}

	public:

		/** 作成。
		*/
		void Create()
		{
			#if defined(new)
			#undef new
			#endif

			this->id.reset(new Muid_Impl());

			#if defined(custom_new)
			#define new custom_new
			#endif
		}

		/** 削除。
		*/
		void Delete()
		{
			this->id.reset();
		}

		/** リセット。
		*/
		void Reset()
		{
			this->id.reset();
		}

		/** 作成しているかどうか。
		*/
		bool IsCreate() const
		{
			if(this->id != nullptr){
				return true;
			}
			return false;
		}

		/** ユニーク名を取得。
		*/
		UniqueNameType GetName() const
		{
			return reinterpret_cast<UniqueNameType>(this->id.get());
		}

		/** 使用数取得。
		*/
		s32 GetUseCount() const
		{
			return this->id.use_count();
		}

	};


}

