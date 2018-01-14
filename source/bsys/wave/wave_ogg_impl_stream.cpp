

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＷＡＶＥ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** lib
*/
#if(BSYS_WAVE_ENABLE)
	#include <brownie_config/wave_ogg_lib.h>
#endif


/** include
*/
#if(BSYS_WAVE_ENABLE)
	#include <brownie_config/wave_ogg_include.h>
#endif


/** include
*/
#include "./wave.h"


/** include
*/
#include "./wave_ogg_impl_stream.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NWave
{
	/** NImpl
	*/
	namespace NImpl
	{
		/** CallBack_Read
		*/
		static std::size_t CallBack_Read(void* a_ptr,std::size_t a_size,std::size_t a_nmemb,void* a_datasource)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if(t_data == nullptr){
				ASSERT(0);
				return -1;
			}

			if((t_data->offset >= t_data->size)||(t_data->offset == -1)){
				return 0;
			}

			if(static_cast<s32>(t_data->offset + a_size * a_nmemb) >= t_data->size){
				int t_copy_size = (t_data->size - t_data->offset);
				NMemory::Copy(a_ptr,t_copy_size,&t_data->data[t_data->offset],t_copy_size);
				
				int t_ret_size = static_cast<s32>(t_copy_size / a_size);
				t_data->offset = t_data->size;

				return t_ret_size;
			}

			int t_copy_size = static_cast<s32>(a_nmemb * a_size);
			NMemory::Copy(a_ptr,t_copy_size,&t_data->data[t_data->offset],t_copy_size);

			DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","copy_size = %d",t_copy_size);

			t_data->offset += t_copy_size;

			return a_nmemb;
		}


		/** CallBack_Seek
		*/
		static int CallBack_Seek(void* a_datasource,ogg_int64_t a_offset,int a_whence)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if((t_data == nullptr)||(t_data->offset<0)){
				return -1;
			}

			if(a_offset < 0){
				t_data->offset = -1;
				return -1;
			}

			int t_new_offset;
			switch(a_whence){
			case SEEK_SET:
				{
					t_new_offset = static_cast<s32>(a_offset);
				}break;
			case SEEK_CUR:
				{
					t_new_offset = static_cast<s32>(t_data->offset + a_offset);
				}break;
			case SEEK_END:
				{
					t_new_offset = static_cast<s32>(t_data->size + a_offset);
				}break;
			default:
				{
					return -1;
				}
			}
			if(t_new_offset < 0){
				return -1;
			}

			t_data->offset = t_new_offset;

			return 0;
		}


		/** CallBack_Close
		*/
		static int CallBack_Close(void* /*a_datasource*/)
		{
			return 0;
		}


		/** CallBack_Tell
		*/
		static long CallBack_Tell(void* a_datasource)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if(t_data == nullptr){
				return -1;
			}

			return t_data->offset;
		}
	}


	/** constructor
	*/
	Wave_Ogg_Impl_Stream::Wave_Ogg_Impl_Stream()
		:
		ogg_data(),
		ogg_size(0),
		virtual_filehandle_enable(false),
		//virtual_filehandle(),
		countof_sample(0),
		channel(0),
		bit(0),
		wavetype(WaveType::None)
	{
	}


	/** destructor
	*/
	Wave_Ogg_Impl_Stream::~Wave_Ogg_Impl_Stream()
	{
		this->Delete();
	}


	/** 作成。
	*/
	void Wave_Ogg_Impl_Stream::Create(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size)
	{
		//コールバック関数を指定。
		ov_callbacks t_callback;
		{
			t_callback.read_func = NImpl::CallBack_Read;
			t_callback.seek_func = NImpl::CallBack_Seek;
			t_callback.close_func = NImpl::CallBack_Close;
			t_callback.tell_func = NImpl::CallBack_Tell;
		}

		//データを指定。
		{
			this->data.data = a_ogg_data.get();
			this->data.size = a_ogg_size;
			this->data.offset = 0;
		}

		//仮想ファイルハンドル作成。
		int t_ret = ::ov_open_callbacks(&this->data,&this->virtual_filehandle,NULL,0,t_callback);
		switch(t_ret){
		case OV_EREAD:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","OV_EREAD");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_ENOTVORBIS:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","OV_ENOTVORBIS");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EVERSION:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","OV_EVERSION");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EBADHEADER:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","OV_EBADHEADER");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EFAULT:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","OV_EFAULT");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		default:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","ok");
			}break;
		}

		//ov_pcm_total
		this->countof_sample = static_cast<s32>(::ov_pcm_total(&this->virtual_filehandle,-1));

		//bit
		this->bit = 16;

		//ov_info
		vorbis_info* t_info = ::ov_info(&this->virtual_filehandle,-1);

		this->wavetype = WaveType::None;
		{
			this->channel = t_info->channels;
			this->rate = t_info->rate;

			if(this->channel == 1){
				//モノラル。
				if(this->rate == 44100){
					//44.1kHz。
					if(this->bit == 8){
						//8bit。
						this->wavetype = WaveType::Mono_8_44100;
					}else if(this->bit == 16){
						//16bit。
						this->wavetype = WaveType::Mono_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				}
			}else if(this->channel == 2){
				//ステレオ。
				if(this->rate == 44100){
					//44.1kHz。
					if(this->bit == 8){
						//8bit。
						this->wavetype = WaveType::Stereo_8_44100;
					}else if(this->bit == 16){
						//16bit。
						this->wavetype = WaveType::Stereo_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				}
			}
		}
	}
	

	/** 削除。
	*/
	void Wave_Ogg_Impl_Stream::Delete()
	{
		if(this->virtual_filehandle_enable == true){
			this->virtual_filehandle_enable = false;
			::ov_clear(&this->virtual_filehandle);
		}
	}


	/** GetWaveType
	*/
	WaveType::Id Wave_Ogg_Impl_Stream::GetWaveType()
	{
		return this->wavetype;
	}


	/** GetCountOfSample
	*/
	s32 Wave_Ogg_Impl_Stream::GetCountOfSample()
	{
		return this->countof_sample;
	}


	/** GetChannel
	*/
	s32 Wave_Ogg_Impl_Stream::GetChannel()
	{
		return this->channel;
	}


	/** GetBit
	*/
	s32 Wave_Ogg_Impl_Stream::GetBit()
	{
		return this->bit;
	}

	
	/** GetRate
	*/
	s32 Wave_Ogg_Impl_Stream::GetRate()
	{
		return this->rate;
	}


	/** ストリーム。

		a_seek < 0 : 自動シーク。

	*/
	bool Wave_Ogg_Impl_Stream::Stream(RingBufferBase<u8>& a_buffer,bool a_loop)
	{
		sharedptr<char> t_temp;

		char* t_buffer = reinterpret_cast<char*>(a_buffer.GetItemFromFreeList(0));
		s32 t_buffer_size = a_buffer.GetContinuousFreeSize();
		if(t_buffer_size <= 1024 * 16){

			if(a_buffer.GetFreeSize() < 1024 * 16){
				//継続。空き容量不足。
				return true;
			}

			t_buffer_size = 1024 * 16;
			t_buffer = new char[1024 * 16];
			t_temp.reset(t_buffer);
		}

		s32 t_endian = 0;
		s32 t_word_size = this->bit / 8;
		s32 t_sgned = 1;
		int t_current_section = 0;
		long t_ret_size = ::ov_read(&this->virtual_filehandle,t_buffer,t_buffer_size,t_endian,t_word_size,t_sgned,&t_current_section);
		if(t_ret_size < 0){
			//エラー中断終了。
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return false;
		}else if(t_ret_size == 0){
			if(a_loop == true){

				if(::ov_pcm_seek(&this->virtual_filehandle,0) != 0){
					//エラー中断。
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					return false;
				}

				//継続。
				return true;
			}

			//完了。
			return false;
		}else{
			//s32 t_seek = ::ov_pcm_tell(&this->virtual_filehandle);

			if(t_temp){
				a_buffer.CopyToBuffer(reinterpret_cast<u8*>(t_temp.get()),t_ret_size);
				t_temp.reset();
			}else{
				a_buffer.AddUse(t_ret_size);
			}
		}

		if(t_current_section != 0){
			//エラー中断終了。
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return false;
		}

		//継続。
		return true;
	}


}}
#pragma warning(pop)
#endif

