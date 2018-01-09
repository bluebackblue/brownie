

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
		/** DataType
		*/
		struct DataType
		{
			const u8* data;
		
			/** サイズ。
			*/
			s32 size;

			/** 現在位置。
			*/
			s32 offset;
		};


		/** CallBack_Read
		*/
		static size_t CallBack_Read(void* a_ptr,size_t a_size,size_t a_nmemb,void* a_datasource)
		{
			DataType* t_data = reinterpret_cast<DataType*>(a_datasource);

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
			t_data->offset += t_copy_size;

			return a_nmemb;
		}


		/** CallBack_Seek
		*/
		static int CallBack_Seek(void* a_datasource,ogg_int64_t a_offset,int a_whence)
		{
			DataType* t_data = reinterpret_cast<DataType*>(a_datasource);

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
			DataType* t_data = reinterpret_cast<DataType*>(a_datasource);

			if(t_data == nullptr){
				return -1;
			}

			return t_data->offset;
		}
	}


	/** CreateWave_Ogg
	*/
	sharedptr<Wave> CreateWave_Ogg(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		//コールバック関数を指定。
		ov_callbacks t_callback;
		{
			t_callback.read_func = NImpl::CallBack_Read;
			t_callback.seek_func = NImpl::CallBack_Seek;
			t_callback.close_func = NImpl::CallBack_Close;
			t_callback.tell_func = NImpl::CallBack_Tell;
		}


		//コールバック関数内で使用するデータ。
		NImpl::DataType t_data;
		{
			t_data.data = a_data.get();
			t_data.size = a_size;
			t_data.offset = 0;
		}


		//仮想ファイル反動作成。
		OggVorbis_File t_virtual_filehandle;
		int t_ret = ::ov_open_callbacks(&t_data,&t_virtual_filehandle,NULL,0,t_callback);
		switch(t_ret){
		case OV_EREAD:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","OV_EREAD");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_ENOTVORBIS:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","OV_ENOTVORBIS");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EVERSION:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","OV_EVERSION");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EBADHEADER:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","OV_EBADHEADER");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		case OV_EFAULT:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","OV_EFAULT");
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}break;
		default:
			{
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"CreateWave_FromOgg","ok");
			}break;
		}

		vorbis_info* t_info = ::ov_info(&t_virtual_filehandle,-1);

		int t_bits_per_sample = 16;
		s32 t_countof_sample = static_cast<s32>(::ov_pcm_total(&t_virtual_filehandle,-1));
		s32 t_buffer_size = t_info->channels * (t_bits_per_sample / 8) * t_countof_sample;
		sharedptr<u8> t_sample(new u8[t_buffer_size],default_delete<u8[]>());

		WaveType::Id t_wavetype = WaveType::None;
		{
			if(t_info->channels == 1){
				//モノラル。
				if(t_info->rate == 44100){
					//44.1kHz。
					if(t_bits_per_sample == 8){
						//8bit。
						t_wavetype = WaveType::Mono_8_44100;
					}else if(t_bits_per_sample == 16){
						//16bit。
						t_wavetype = WaveType::Mono_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				}
			}else if(t_info->channels == 2){
				//ステレオ。
				if(t_info->rate == 44100){
					//44.1kHz。
					if(t_bits_per_sample == 8){
						//8bit。
						t_wavetype = WaveType::Stereo_8_44100;
					}else if(t_bits_per_sample == 16){
						//16bit。
						t_wavetype = WaveType::Stereo_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				}
			}
		}
  
		{
			s32 t_offset = 0;
			while(1){
				s32 t_req_size = t_buffer_size - t_offset;

				int current_section = 0;
				int t_ret_size = ::ov_read(&t_virtual_filehandle,reinterpret_cast<char*>(&t_sample.get()[t_offset]),t_req_size,0,2,1,&current_section);

				if(current_section != 0){
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				}

				if(t_ret_size > 0){
					t_offset += t_ret_size;
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,(t_offset == t_buffer_size));
					break;
				}
			}
		}

		{
			::ov_clear(&t_virtual_filehandle);
		}

		sharedptr<Wave> t_wave(new Wave(t_sample,t_buffer_size,t_countof_sample,t_wavetype,a_name));
		return t_wave;
	}


}}
#pragma warning(pop)
#endif

