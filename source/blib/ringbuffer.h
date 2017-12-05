#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �����O�o�b�t�@�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./memory.h"


/** NBlib
*/
namespace NBlib
{
	/** RingBufferCopy
	*/
	template <typename R,bool RAWCOPYMODE> class RingBufferCopy;

	/** RingBufferCopy<RAWCOPYMODE=true>
	*/
	template <typename R> class RingBufferCopy<R,true>
	{
	public:
		typedef typename R::RingBufferItemType T;

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyToBuffer_Raw(R& a_to_ringbuffer,T* a_from_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			Memory::memcpy(a_to_ringbuffer.GetItemFromFreeList(0),a_copycount * sizeof(T),&a_from_data[a_copy_fixcount],a_copycount * sizeof(T));
		}

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyFromBuffer_Raw(R& a_from_ringbuffer,T* a_to_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			Memory::memcpy(&a_to_data[a_copy_fixcount],a_copycount * sizeof(T),a_from_ringbuffer.GetItemFromUseList(0),a_copycount * sizeof(T));
		}
	};

	/** RingBufferCopy<RAWCOPYMODE=false>
	*/
	template <typename R> class RingBufferCopy<R,false>
	{
	public:
		typedef typename R::RingBufferItemType T;

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyToBuffer_Raw(R& a_to_ringbuffer,T* a_from_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			T* t_to = a_to_ringbuffer.GetItemFromFreeList(0);
			for(s32 ii=0;ii<a_copycount;ii++){
				t_to[ii] = a_from_data[a_copy_fixcount + ii];
			}
		}

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyFromBuffer_Raw(R& a_from_ringbuffer,T* a_to_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			T* t_from = a_from_ringbuffer.GetItemFromUseList(0);
			for(s32 ii=0;ii<a_copycount;ii++){
				a_to_data[a_copy_fixcount + ii] = t_from[ii];
			}
		}
	};

	/** �����O�o�b�t�@�B�x�[�X�B
	*/
	template <typename T> class RingBufferBase
	{
	public:
		/** �g�p�T�C�Y�擾�B
		*/
		virtual s32 GetUseSize() const = 0;

		/** �󂫃T�C�Y�擾�B
		*/
		virtual s32 GetFreeSize() const = 0;

		/** �S�T�C�Y���擾�B
		*/
		virtual s32 GetTotalSize() const = 0;

		/** �A�������g�p�T�C�Y�B
		*/
		virtual s32 GetContinuousUseSize() const = 0;

		/** �A�������󂫃T�C�Y�B
		*/
		virtual s32 GetContinuousFreeSize() const = 0;

	public:

		/** ���X�g�̐擪����A�C�e�����擾����B
		*/
		virtual T* GetItemFromListStart() = 0;

		/** �g�p���X�g����̃A�C�e�����擾����B
		*/
		virtual T* GetItemFromUseList(s32 a_offset) = 0;

		/** �󂫃��X�g����A�C�e�����擾����B
		*/
		virtual T* GetItemFromFreeList(s32 a_offset) = 0;

	public:

		/** �g�p�̈�擪���󂫗̈�ɂ���B
		*/
		virtual void AddFree(s32 a_count) = 0;

		/** �󂫗̈�擪���g�p�̈�ɂ���B
		*/
		virtual void AddUse(s32 a_count) = 0;

		/** �����O�o�b�t�@�ɃR�s�[�B
		*/
		virtual void CopyToBuffer(T* a_from_data,s32 a_from_count) = 0;

		/** �����O�o�b�t�@����R�s�[�B
		*/
		virtual void CopyFromBuffer(T* a_to_data,s32 a_to_count) = 0;
	};

	/** �����O�o�b�t�@�B
	*/
	template <typename T,s32 SIZE,bool RAWCOPYMODE> class RingBuffer : public RingBufferBase<T>
	{
	public:
		typedef T RingBufferItemType;

	private:

		/** list
		*/
		T list[SIZE];

		/** �g�p�̈�J�n�C���f�b�N�X�B
		*/
		s32 index_usestart;

		/** �󂫗̈�J�n�C���f�b�N�X�B
		*/
		s32 index_freestart;

		/** �g�p�T�C�Y�B
		*/
		s32 usesize;

	public:
		/** constructor.
		*/
		RingBuffer()
			:
			index_usestart(0),
			index_freestart(0),
			usesize(0)
		{
		}

		/** destructor
		*/
		nonvirtual ~RingBuffer()
		{
		}

		/** Reset
		*/
		void Reset()
		{
			this->index_usestart = 0;
			this->index_freestart = 0;
			this->usesize = 0;
		}

	public:

		/** �g�p�T�C�Y�擾�B
		*/
		s32 GetUseSize() const
		{
			return this->usesize;
		}

		/** �󂫃T�C�Y�擾�B
		*/
		s32 GetFreeSize() const
		{
			return COUNTOF(this->list) - this->usesize;
		}

		/** �S�T�C�Y���擾�B
		*/
		s32 GetTotalSize() const
		{
			return COUNTOF(this->list);
		}

		/** �A�������g�p�T�C�Y�B
		*/
		s32 GetContinuousUseSize() const
		{
			if(this->usesize <= 0){
				//��������������������
				return 0;
			}else if(this->index_usestart < this->index_freestart){
				//    u2      f6
				//��������������������
				return this->index_freestart - this->index_usestart;
			}else{
				//        uf4
				//��������������������

				//    f2      u6
				//��������������������
				return COUNTOF(this->list) - this->index_usestart;
			}
		}

		/** �A�������󂫃T�C�Y�B
		*/
		s32 GetContinuousFreeSize() const
		{
			if(this->usesize >= COUNTOF(this->list)){
				//��������������������
				return 0;
			}else if(this->index_freestart < this->index_usestart){
				//    f2      u6
				//��������������������
				return this->index_usestart - this->index_freestart;
			}else{
				//        uf4
				//��������������������

				//    u2      f6
				//��������������������
				return COUNTOF(this->list) - this->index_freestart;
			}
		}

	public:

		/** ���X�g�̐擪����A�C�e�����擾����B
		*/
		T* GetItemFromListStart()
		{
			return &this->list[0];
		}

		/** �g�p���X�g����̃A�C�e�����擾����B
		*/
		T* GetItemFromUseList(s32 a_offset)
		{
			s32 t_index = ((this->index_usestart + a_offset) % COUNTOF(this->list));
			return &this->list[t_index];
		}

		/** �󂫃��X�g����A�C�e�����擾����B
		*/
		T* GetItemFromFreeList(s32 a_offset)
		{
			s32 t_index = ((this->index_freestart + a_offset) % COUNTOF(this->list));
			return &this->list[t_index];
		}

	public:

		/** �g�p�̈�擪���󂫗̈�ɂ���B
		*/
		void AddFree(s32 a_count)
		{
			this->usesize -= a_count;
			ASSERT(this->usesize >= 0);

			this->index_usestart = (this->index_usestart + a_count) % COUNTOF(this->list);

			if(this->index_freestart == this->index_usestart){
				this->index_freestart = 0;
				this->index_usestart = 0;
			}
		}

		/** �󂫗̈�擪���g�p�̈�ɂ���B
		*/
		void AddUse(s32 a_count)
		{
			this->usesize += a_count;
			ASSERT(this->usesize <= COUNTOF(this->list));

			this->index_freestart = (this->index_freestart + a_count) % COUNTOF(this->list);
		}

		/** �����O�o�b�t�@�ɃR�s�[�B
		*/
		void CopyToBuffer(T* a_from_data,s32 a_from_count)
		{
			s32 t_copy_fixcount = 0;
			while(t_copy_fixcount < a_from_count){
				s32 t_copycount = this->GetContinuousFreeSize();
				if(t_copycount > 0){
					if(t_copycount > (a_from_count - t_copy_fixcount)){
						t_copycount = a_from_count - t_copy_fixcount;
					}

					RingBufferCopy<RingBuffer<T,SIZE,RAWCOPYMODE>,RAWCOPYMODE>::CopyToBuffer_Raw(*this,a_from_data,t_copy_fixcount,t_copycount);

					this->AddUse(t_copycount);
					t_copy_fixcount += t_copycount;
				}else{
					//�R�s�[�悪�Ȃ��B
					ASSERT(0);
					break;
				}
			}
		}

		/** �����O�o�b�t�@����R�s�[�B
		*/
		void CopyFromBuffer(T* a_to_data,s32 a_to_count)
		{
			s32 t_copy_fixcount = 0;
			while(t_copy_fixcount < a_to_count){
				s32 t_copycount = this->GetContinuousUseSize();
				if(t_copycount > 0){
					if(t_copycount > (a_to_count - t_copy_fixcount)){
						t_copycount = a_to_count - t_copy_fixcount;
					}

					RingBufferCopy<RingBuffer<T,SIZE,RAWCOPYMODE>,RAWCOPYMODE>::CopyFromBuffer_Raw(*this,a_to_data,t_copy_fixcount,t_copycount);

					this->AddFree(t_copycount);
					t_copy_fixcount += t_copycount;
				}else{
					//�R�s�[�����Ȃ��B
					ASSERT(0);
					break;
				}
			}
		}

	};
}

