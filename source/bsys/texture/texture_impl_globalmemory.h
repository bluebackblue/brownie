#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テクスチャー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#if(PLATFORM_VCWIN)
#include <brownie_config/windows_include.h>
#endif


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4514 4820)
namespace NBsys{namespace NTexture
{
	/** Texture_Impl_GlobalMemory
	*/
	class Texture_Impl_GlobalMemory
	{
	private:

		/** handle
		*/
		#if(PLATFORM_VCWIN)
		HGLOBAL handle;
		#endif

		/** pointer
		*/
		void* pointer;

	public:

		/** constructor
		*/
		Texture_Impl_GlobalMemory(s32 a_size)
			:
			#if(PLATFORM_VCWIN)
			handle(WIN_NULL),
			#endif
			pointer(nullptr)
		{
			ASSERT(a_size > 0);

			#if(PLATFORM_VCWIN)
			this->handle = ::GlobalAlloc(GMEM_MOVEABLE,static_cast<std::size_t>(a_size));
			#endif
		}

		/** destructor
		*/
		~Texture_Impl_GlobalMemory()
		{
			this->Unmap();

			#if(PLATFORM_VCWIN)
			if(this->handle){
				::GlobalFree(this->handle);
				this->handle = WIN_NULL;
			}
			#endif
		}

		/** IsEnable
		*/
		bool IsEnable()
		{
			#if(PLATFORM_VCWIN)
			if(this->handle != WIN_NULL){
				return true;
			}
			#endif

			return false;
		}

		/** GetHandle
		*/
		#if(PLATFORM_VCWIN)
		HGLOBAL GetHandle() const
		{
			return this->handle;
		}
		#endif

		/** Map
		*/
		void* Map()
		{
			#if(PLATFORM_VCWIN)
			if(this->pointer == nullptr){
				if(this->handle){
					this->pointer = ::GlobalLock(this->handle);
					ASSERT(this->pointer != nullptr);
					return this->pointer;
				}
			}
			#endif

			return this->pointer;
		}

		/** Unmap
		*/
		void Unmap()
		{
			#if(PLATFORM_VCWIN)
			if(this->handle){
				if(this->pointer){
					::GlobalUnlock(this->handle);
					this->pointer = nullptr;
				}
			}
			#endif
		}

	};


	/** Texture_Impl_GlobalMemory_Stream
	*/
	class Texture_Impl_GlobalMemory_Stream
	{
	private:

		/** handle
		*/
		#if(PLATFORM_VCWIN)
		IStream* stream;
		#endif

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
			#if(PLATFORM_VCWIN)
			stream(nullptr),
			#endif
			globalmemory(a_globalmemory)
		{
			#if(PLATFORM_VCWIN)

			HGLOBAL t_handle = this->globalmemory->GetHandle();
			if(t_handle){
				if(::CreateStreamOnHGlobal(t_handle,FALSE,&this->stream) == S_OK){
					ASSERT(this->stream != nullptr);
				}else{
					ASSERT(0);
					this->stream = nullptr;
				}
			}

			#endif
		}

		/** destructor
		*/
		~Texture_Impl_GlobalMemory_Stream()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream){
				this->stream->Release();
				this->stream = nullptr;
			}
			#endif
		}

		/** GetHandle
		*/
		#if(PLATFORM_VCWIN)
		IStream* GetHandle() const
		{
			return this->stream;
		}
		#endif

		/** IsEnable
		*/
		bool IsEnable()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream != nullptr){
				return true;
			}
			#endif

			return false;
		}

		/** シークを最初に設定。
		*/
		void SetSeekStart()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream != nullptr){
				LARGE_INTEGER t_pos = {0};
				this->stream->Seek(t_pos,STREAM_SEEK_SET,nullptr);
			}
			#endif
		}

		/** サイズをゼロに設定。
		*/
		void SetSizeZero()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream != nullptr){
				ULARGE_INTEGER t_size = {0};
				this->stream->SetSize(t_size);
			}
			#endif
		}

		/** ステース更新。
		*/
		void UpdateStatus()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream){
				this->stream->Stat(&this->statstg,STATFLAG_DEFAULT);
			}
			#endif
		}

		/** サイズ取得。
		*/
		s32 GetStatus_Size()
		{
			return static_cast<s32>(this->statstg.cbSize.QuadPart);
		}

	};


}}
#pragma warning(pop)
#endif

