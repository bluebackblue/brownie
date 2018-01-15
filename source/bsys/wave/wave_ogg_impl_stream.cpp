

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

			if(t_data != nullptr){
				
				s64 t_copy_size = a_nmemb * a_size;

				if(t_data->ogg_offset + t_copy_size >= t_data->ogg_size){
					t_copy_size = t_data->ogg_size - t_data->ogg_offset;
				}

				NMemory::Copy(a_ptr,t_copy_size,&t_data->ogg_data[t_data->ogg_offset],t_copy_size);

				t_data->ogg_offset += t_copy_size;

				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","CallBack_Read : %d",t_copy_size);

				s64 t_ret_size = t_copy_size / a_size;

				return static_cast<std::size_t>(t_ret_size);

			}

			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return 0;
		}


		/** CallBack_Seek
		*/
		static int CallBack_Seek(void* a_datasource,ogg_int64_t a_offset,int a_whence)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if(t_data != nullptr){

				switch(a_whence){
				case SEEK_SET:
					{
						t_data->ogg_offset = a_offset;
					}break;
				case SEEK_CUR:
					{
						t_data->ogg_offset = t_data->ogg_offset + a_offset;
					}break;
				case SEEK_END:
					{
						t_data->ogg_offset = t_data->ogg_size + a_offset;
					}break;
				default:
					{
						t_data->ogg_offset = -1;
					}break;
				}

				if((0<=t_data->ogg_offset)&&(t_data->ogg_offset<=t_data->ogg_size)){
					return 0;
				}
			}

			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return OV_FALSE;
		}


		/** CallBack_Close
		*/
		static int CallBack_Close(void* a_datasource)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if(t_data != nullptr){
			}else{
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}

			return 0;
		}


		/** CallBack_Tell
		*/
		static long CallBack_Tell(void* a_datasource)
		{
			Wave_Ogg_Impl_Stream::DataType* t_data = reinterpret_cast<Wave_Ogg_Impl_Stream::DataType*>(a_datasource);

			if(t_data != nullptr){
				return static_cast<long>(t_data->ogg_offset);
			}

			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return OV_FALSE;
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
		bit(0)
	{
	}


	/** destructor
	*/
	Wave_Ogg_Impl_Stream::~Wave_Ogg_Impl_Stream()
	{
		this->Delete();
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


	/** シーク。
	*/
	void Wave_Ogg_Impl_Stream::SeekStart()
	{
		if(this->virtual_filehandle_enable == true){
			int t_ret = ::ov_pcm_seek(&this->virtual_filehandle,0);
			if(t_ret != 0){
				DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","ov_pcm_seek : %d",t_ret);
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			}
		}else{
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
		}
	}


	/** ストリーム。
	*/
	bool Wave_Ogg_Impl_Stream::Stream(RingBufferBase<u8>& a_buffer,bool a_is_loop)
	{
		sharedptr<char> t_temp;

		static const s32 BUFFER_SIZE = 16 * 1024;

		char* t_buffer = reinterpret_cast<char*>(a_buffer.GetItemFromFreeList(0));
		s32 t_buffer_size = a_buffer.GetContinuousFreeSize();
		if(t_buffer_size <= BUFFER_SIZE){

			if(a_buffer.GetFreeSize() < BUFFER_SIZE){
				//継続。空き容量不足。
				DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
				return true;
			}

			t_buffer_size = BUFFER_SIZE;
			t_buffer = new char[BUFFER_SIZE];
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
			if(a_is_loop == true){

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


	/** 作成。
	*/
	void Wave_Ogg_Impl_Stream::Create(const sharedptr<u8>& a_ogg_data,s64 a_ogg_size)
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
			this->data.ogg_data = a_ogg_data.get();
			this->data.ogg_size = a_ogg_size;
			this->data.ogg_offset = 0;
		}

		//仮想ファイルハンドル作成。
		int t_ret = ::ov_open_callbacks(&this->data,&this->virtual_filehandle,NULL,0,t_callback);
		if(t_ret == 0){
			this->virtual_filehandle_enable = true;
		}else{
			DEEPDEBUG_TAGLOG(BSYS_WAVE_DEBUG_ENABLE,L"wave_ogg_impl_stream","ov_open_callbacks : %d",t_ret);
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
		}

		//ov_pcm_total
		this->countof_sample = static_cast<s32>(::ov_pcm_total(&this->virtual_filehandle,-1));

		//量子化ビット数。
		this->bit = 16;

		//ov_info
		vorbis_info* t_info = ::ov_info(&this->virtual_filehandle,-1);

		//チャンネル。
		this->channel = t_info->channels;
		this->rate = t_info->rate;
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


	/** GetCountOfSample
	*/
	s32 Wave_Ogg_Impl_Stream::GetCountOfSample()
	{
		return this->countof_sample;
	}


}}
#pragma warning(pop)
#endif

