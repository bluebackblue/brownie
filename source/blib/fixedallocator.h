#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 固定長アロケータ。
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
				/** ブロックサイズ長。
				*/
				BlockSize = BLOCKSIZE,

				/** ブロック数。
				*/
				BlockMax = BLOCKMAX,
			};
		};

	private:

		/** データ配列。
		*/
		u8 data[Config::BlockSize * Config::BlockMax];

		/** 空き。インデックス。
		*/
		s32 free_index[Config::BlockMax];

		/** 空きサイズ。
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

		/** リセット。
		*/
		void Reset()
		{
			for(s32 ii=0;ii<COUNTOF(this->free_index);ii++){
				this->free_index[ii] = ii;
			}
			this->free_size = COUNTOF(this->free_index);
		}

		/** インデックス総数。
		*/
		s32 GetMaxIndex() const
		{
			return COUNTOF(this->flag);
		}

		/** インデックスからポインター取得。
		*/
		void* GetPointerFromIndex(s32 a_index)
		{
			if((0<=a_index)&&(a_index<COUNTOF(this->free_index))){
				return &(this->data[a_index * Config::BlockSize]);
			}

			return nullptr;
		}

		/** ポインターからインデックスを取得。
		*/
		s32 GetIndexFromPointer(const void* a_pointer) const
		{
			s32 t_index = static_cast<s32>((reinterpret_cast<AddressType>(a_pointer)-reinterpret_cast<AddressType>(static_cast<const void*>(&this->data[0])))/Config::BlockSize);

			if((0 <= t_index)&&(t_index < COUNTOF(this->free_index))){
				ASSERT(reinterpret_cast<AddressType>(a_pointer) == (reinterpret_cast<AddressType>(static_cast<const void*>(&this->data[0]))+t_index*Config::BlockSize));
				return t_index;
			}

			//管理外ポインタ。
			return -1;
		}

		/** 空きインデックスを取得。
		*/
		s32 PopFreeIndex()
		{
			if(this->free_size > 0){
				this->free_size--;
				return this->free_index[this->free_size];
			}

			TAGLOG(L"FixedAllocator::GetFreeIndex","-1");

			return -1;
		}

		/** 空きインデックスを設定。
		*/
		void PushFreeIndex(s32 a_index)
		{
			this->free_index[this->free_size] = a_index;
			this->free_size++;
		}

		/** 確保。
		*/
		void* Alloc()
		{
			//空きインデックスの取得。
			s32 t_index = this->PopFreeIndex();
			
			//確保。
			if(t_index >= 0){
				return this->GetPointerFromIndex(t_index);
			}

			//空きなし。
			return nullptr;
		}

		/** 解放。
		*/
		bool Free(void* a_pointer)
		{
			//ポインターからインデックス取得。
			s32 t_index = this->GetIndexFromPointer(a_pointer);

			//解放。
			if(t_index >= 0){
				//空きインデックスの設定。
				this->PushFreeIndex(t_index);
				return true;
			}

			//管理外ポインタ。
			return false;
		}

	};


}

