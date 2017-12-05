#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �Œ蒷�A���P�[�^�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./debugassert.h"
#include "./debuglog.h"


/** NBlib
*/
namespace NBlib
{
	/** FixedAllocator
	*/
	template <s32 BLOCKSIZE,s32 BLOCKMAX> struct FixedAllocator
	{
	public:
		/** Config
		*/
		struct Config
		{
			/** Id
			*/
			enum Id
			{
				/** �u���b�N�T�C�Y���B
				*/
				BlockSize = BLOCKSIZE,

				/** �u���b�N���B
				*/
				BlockMax = BLOCKMAX,
			};
		};

	private:
		/** �f�[�^�z��B
		*/
		u8 data[Config::BlockSize * Config::BlockMax];

		/** �󂫁B�C���f�b�N�X�B
		*/
		s32 free_index[Config::BlockMax];

		/** �󂫃T�C�Y�B
		*/
		s32 free_size;


	public:
		/** constructor
		*/
		FixedAllocator()
		{
			this->Reset();
		}

		/** destructor
		*/
		nonvirtual ~FixedAllocator()
		{
		}

		/** ���Z�b�g�B
		*/
		void Reset()
		{
			for(s32 ii=0;ii<COUNTOF(this->free_index);ii++){
				this->free_index[ii] = ii;
			}
			this->free_size = COUNTOF(this->free_index);
		}

		/** �C���f�b�N�X�����B
		*/
		s32 GetMaxIndex() const
		{
			return COUNTOF(this->flag);
		}

		/** �C���f�b�N�X����|�C���^�[�擾�B
		*/
		void* GetPointerFromIndex(s32 a_index)
		{
			if((0<=a_index)&&(a_index<COUNTOF(this->free_index))){
				return &(this->data[a_index * Config::BlockSize]);
			}

			return nullptr;
		}

		/** �|�C���^�[����C���f�b�N�X���擾�B
		*/
		s32 GetIndexFromPointer(const void* a_pointer) const
		{
			s32 t_index = static_cast<s32>((reinterpret_cast<AddressType>(a_pointer)-reinterpret_cast<AddressType>(static_cast<const void*>(&this->data[0])))/Config::BlockSize);

			if((0 <= t_index)&&(t_index < COUNTOF(this->free_index))){
				ASSERT(reinterpret_cast<AddressType>(a_pointer) == (reinterpret_cast<AddressType>(static_cast<const void*>(&this->data[0]))+t_index*Config::BlockSize));
				return t_index;
			}

			//�Ǘ��O�|�C���^�B
			return -1;
		}

		/** �󂫃C���f�b�N�X���擾�B
		*/
		s32 PopFreeIndex()
		{
			if(this->free_size > 0){
				this->free_size--;
				return this->free_index[this->free_size];
			}

			TAGLOG("FixedAllocator::GetFreeIndex","-1");

			return -1;
		}

		/** �󂫃C���f�b�N�X��ݒ�B
		*/
		void PushFreeIndex(s32 a_index)
		{
			this->free_index[this->free_size] = a_index;
			this->free_size++;
		}

		/** �m�ہB
		*/
		void* Alloc()
		{
			//�󂫃C���f�b�N�X�̎擾�B
			s32 t_index = this->PopFreeIndex();
			
			//�m�ہB
			if(t_index >= 0){
				return this->GetPointerFromIndex(t_index);
			}

			//�󂫂Ȃ��B
			return nullptr;
		}

		/** ����B
		*/
		bool Free(void* a_pointer)
		{
			//�|�C���^�[����C���f�b�N�X�擾�B
			s32 t_index = this->GetIndexFromPointer(a_pointer);

			//����B
			if(t_index >= 0){
				//�󂫃C���f�b�N�X�̐ݒ�B
				this->PushFreeIndex(t_index);
				return true;
			}

			//�Ǘ��O�|�C���^�B
			return false;
		}
	};
}

