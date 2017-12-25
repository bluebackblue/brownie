#pragma once
#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �e�N�X�`���[�B
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
#if(BSYS_TEXTURE_ENABLE)
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
			this->handle = ::GlobalAlloc(GMEM_MOVEABLE,a_size);
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
				}else{
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

		/** �V�[�N���ŏ��ɐݒ�B
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

		/** �T�C�Y���[���ɐݒ�B
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

		/** �X�e�[�X�X�V�B
		*/
		void UpdateStatus()
		{
			#if(PLATFORM_VCWIN)
			if(this->stream){
				this->stream->Stat(&this->statstg,STATFLAG_DEFAULT);
			}
			#endif
		}

		/** �T�C�Y�擾�B
		*/
		s32 GetStatus_Size()
		{
			return static_cast<s32>(this->statstg.cbSize.QuadPart);
		}

	};


}}
#endif

