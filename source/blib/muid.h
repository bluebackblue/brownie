#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �v���Z�X��ԓ��Ń��j�[�N�Ȃh�c�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"


/*

	���j�[�N�����L���Ȃ̂́uid�v���������Ă���ԁB

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

		/** �m�ہB
		*/
		static void* Alloc(size_t a_size);

		/** ����B
		*/
		static void Free(void* a_pointer);

	public:

		/** operator new
		*/
		static void* operator new(size_t a_size) noexcept
		{
			return Muid_Impl::Alloc(a_size);
		}
		
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
		sharedptr< Muid_Impl > id;

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
				this->id.reset(new Muid_Impl());
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
		/** �쐬�B
		*/
		void Create()
		{
			this->id.reset(new Muid_Impl());
		}

		/** �폜�B
		*/
		void Delete()
		{
			this->id.reset();
		}

		/** ���Z�b�g�B
		*/
		void Reset()
		{
			this->id.reset();
		}

		/** �쐬���Ă��邩�ǂ����B
		*/
		bool IsCreate() const
		{
			if(this->id != nullptr){
				return true;
			}
			return false;
		}

		/** ���j�[�N�����擾�B
		*/
		UniqueNameType GetName() const
		{
			return reinterpret_cast<UniqueNameType>(this->id.get());
		}

		/** �g�p���擾�B
		*/
		s32 GetUseCount() const
		{
			return this->id.use_count();
		}

	};
}

