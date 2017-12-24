#pragma once
#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#if(PLATFORM_VCWIN)
#include <brownie_config/windows_include.h>
#endif


/** NBsys::NTexture
*/
#if(PLATFORM_VCWIN)
namespace NBsys{namespace NTexture
{
	/** Texture_Impl_GlobalMemory
	*/
	class Texture_Impl_GlobalMemory
	{
	private:

		/** handle
		*/
		HGLOBAL handle;

		/** pointer
		*/
		void* pointer;

	public:

		/** constructor
		*/
		Texture_Impl_GlobalMemory(s32 a_size)
			:
			handle(WIN_NULL),
			pointer(nullptr)
		{
			this->handle = ::GlobalAlloc(GMEM_MOVEABLE,a_size);
		}

		/** destructor
		*/
		~Texture_Impl_GlobalMemory()
		{
			this->Unmap();

			if(this->handle){
				::GlobalFree(this->handle);
				this->handle = WIN_NULL;
			}
		}

		/** IsEnable
		*/
		bool IsEnable()
		{
			if(this->handle != WIN_NULL){
				return true;
			}
			return false;
		}

		/** GetHandle
		*/
		HGLOBAL GetHandle() const
		{
			return this->handle;
		}

		/** Map
		*/
		void* Map()
		{
			if(this->pointer == nullptr){
				if(this->handle){
					this->pointer = ::GlobalLock(this->handle);
					return this->pointer;
				}
			}

			return this->pointer;
		}

		/** Unmap
		*/
		void Unmap()
		{
			if(this->handle){
				if(this->pointer){
					::GlobalUnlock(this->handle);
					this->pointer = nullptr;
				}
			}
		}

	};


	/** Texture_Impl_GlobalMemory_Stream
	*/
	class Texture_Impl_GlobalMemory_Stream
	{
	private:

		/** handle
		*/
		IStream* stream;

		/** globalmemory
		*/
		sharedptr<Texture_Impl_GlobalMemory> globalmemory;

		/** statstg
		*/
		STATSTG statstg;

	public:

		/** constructor
		*/
		Texture_Impl_GlobalMemory_Stream(const sharedptr<Texture_Impl_GlobalMemory>& a_globalmemory)
			:
			stream(nullptr),
			globalmemory(a_globalmemory)
		{
			HGLOBAL t_handle = this->globalmemory->GetHandle();
			if(t_handle){
				if(::CreateStreamOnHGlobal(t_handle,FALSE,&this->stream) == S_OK){
				}else{
					this->stream = nullptr;
				}
			}
		}

		/** destructor
		*/
		~Texture_Impl_GlobalMemory_Stream()
		{
			if(this->stream){
				this->stream->Release();
				this->stream = nullptr;
			}
		}

		/** GetHandle
		*/
		IStream* GetHandle() const
		{
			return this->stream;
		}

		/** IsEnable
		*/
		bool IsEnable()
		{
			if(this->stream != nullptr){
				return true;
			}
			return false;
		}

		/** シークを最初に設定。
		*/
		void SetSeekStart()
		{
			if(this->stream != nullptr){
				LARGE_INTEGER t_pos = {0};
				this->stream->Seek(t_pos,STREAM_SEEK_SET,nullptr);
			}
		}

		/** サイズをゼロに設定。
		*/
		void SetSizeZero()
		{
			if(this->stream != nullptr){
				ULARGE_INTEGER t_size = {0};
				this->stream->SetSize(t_size);
			}
		}

		/** ステース更新。
		*/
		void UpdateStatus()
		{
			if(this->stream){
				this->stream->Stat(&this->statstg,STATFLAG_DEFAULT);
			}
		}

		/** サイズ取得。
		*/
		s32 GetStatus_Size()
		{
			return static_cast<s32>(this->statstg.cbSize.QuadPart);
		}

	};


}}
#endif

