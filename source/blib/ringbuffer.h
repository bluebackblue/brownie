#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief リングバッファ。
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

		/** T
		*/
		typedef typename R::RingBufferItemType T;

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyToBuffer_Raw(R& a_to_ringbuffer,T* a_from_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			NMemory::Copy(a_to_ringbuffer.GetItemFromFreeList(0),(a_copycount * sizeof(T)),&a_from_data[static_cast<std::size_t>(a_copy_fixcount)],(a_copycount * sizeof(T)));
		}

		/** [static]CopyToBuffer_Raw
		*/
		static void CopyFromBuffer_Raw(R& a_from_ringbuffer,T* a_to_data,s32 a_copy_fixcount,s32 a_copycount)
		{
			NMemory::Copy(&a_to_data[static_cast<std::size_t>(a_copy_fixcount)],(a_copycount * sizeof(T)),a_from_ringbuffer.GetItemFromUseList(0),(a_copycount * sizeof(T)));
		}

	};


	/** RingBufferCopy<RAWCOPYMODE=false>
	*/
	template <typename R> class RingBufferCopy<R,false>
	{
	public:

		/** T
		*/
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


	/** リングバッファ。ベース。
	*/
	template <typename T> class RingBufferBase
	{
	public:

		/** 使用サイズ取得。
		*/
		virtual s32 GetUseSize() const = 0;

		/** 空きサイズ取得。
		*/
		virtual s32 GetFreeSize() const = 0;

		/** 全サイズを取得。
		*/
		virtual s32 GetTotalSize() const = 0;

		/** 連続した使用サイズ。
		*/
		virtual s32 GetContinuousUseSize() const = 0;

		/** 連続した空きサイズ。
		*/
		virtual s32 GetContinuousFreeSize() const = 0;

	public:

		/** リストの先頭からアイテムを取得する。
		*/
		virtual T* GetItemFromListStart() = 0;

		/** 使用リストからのアイテムを取得する。
		*/
		virtual T* GetItemFromUseList(s32 a_offset) = 0;

		/** 空きリストからアイテムを取得する。
		*/
		virtual T* GetItemFromFreeList(s32 a_offset) = 0;

	public:

		/** 使用領域先頭を空き領域にする。
		*/
		virtual void AddFree(s32 a_count) = 0;

		/** 空き領域先頭を使用領域にする。
		*/
		virtual void AddUse(s32 a_count) = 0;

		/** リングバッファにコピー。
		*/
		virtual void CopyToBuffer(T* a_from_data,s32 a_from_count) = 0;

		/** リングバッファからコピー。
		*/
		virtual void CopyFromBuffer(T* a_to_data,s32 a_to_count) = 0;

	};


	/** リングバッファ。
	*/
	template <typename T,s32 SIZE,bool RAWCOPYMODE> class RingBuffer : public RingBufferBase<T>
	{
	public:

		/** RingBufferItemType
		*/
		typedef T RingBufferItemType;

	private:

		/** 使用領域開始インデックス。
		*/
		s32 index_usestart;

		/** 空き領域開始インデックス。
		*/
		s32 index_freestart;

		/** 使用サイズ。
		*/
		s32 usesize;

		/** padding
		*/
		padding64(0,4);

		/** list
		*/
		T list[SIZE];

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
		virtual ~RingBuffer()
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

		/** 使用サイズ取得。
		*/
		s32 GetUseSize() const
		{
			return this->usesize;
		}

		/** 空きサイズ取得。
		*/
		s32 GetFreeSize() const
		{
			return COUNTOF(this->list) - this->usesize;
		}

		/** 全サイズを取得。
		*/
		s32 GetTotalSize() const
		{
			return COUNTOF(this->list);
		}

		/** 連続した使用サイズ。
		*/
		s32 GetContinuousUseSize() const
		{
			if(this->usesize <= 0){
				//□□□□□□□□□□
				return 0;
			}else if(this->index_usestart < this->index_freestart){
				//    u2      f6
				//□□■■■■□□□□
				return this->index_freestart - this->index_usestart;
			}else{
				//        uf4
				//■■■■■■■■■■

				//    f2      u6
				//■■□□□□■■■■
				return COUNTOF(this->list) - this->index_usestart;
			}
		}

		/** 連続した空きサイズ。
		*/
		s32 GetContinuousFreeSize() const
		{
			if(this->usesize >= COUNTOF(this->list)){
				//■■■■■■■■■■
				return 0;
			}else if(this->index_freestart < this->index_usestart){
				//    f2      u6
				//■■□□□□■■■■
				return this->index_usestart - this->index_freestart;
			}else{
				//        uf4
				//□□□□□□□□□□

				//    u2      f6
				//□□■■■■□□□□
				return COUNTOF(this->list) - this->index_freestart;
			}
		}

	public:

		/** リストの先頭からアイテムを取得する。
		*/
		T* GetItemFromListStart()
		{
			return &this->list[0];
		}

		/** 使用リストからのアイテムを取得する。
		*/
		T* GetItemFromUseList(s32 a_offset)
		{
			s32 t_index = ((this->index_usestart + a_offset) % COUNTOF(this->list));
			return &this->list[t_index];
		}

		/** 空きリストからアイテムを取得する。
		*/
		T* GetItemFromFreeList(s32 a_offset)
		{
			s32 t_index = ((this->index_freestart + a_offset) % COUNTOF(this->list));
			return &this->list[t_index];
		}

	public:

		/** 使用領域先頭を空き領域にする。
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

		/** 空き領域先頭を使用領域にする。
		*/
		void AddUse(s32 a_count)
		{
			this->usesize += a_count;
			ASSERT(this->usesize <= COUNTOF(this->list));

			this->index_freestart = (this->index_freestart + a_count) % COUNTOF(this->list);
		}

		/** リングバッファにコピー。
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
					//コピー先がない。
					ASSERT(0);
					break;
				}
			}
		}

		/** リングバッファからコピー。
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
					//コピー元がない。
					ASSERT(0);
					break;
				}
			}
		}

	};


}

