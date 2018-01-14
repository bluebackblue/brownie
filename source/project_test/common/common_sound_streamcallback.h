#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。ストリーミング再生。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest::NCommon
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710 4820)
namespace NTest{namespace NCommon
{
	/** SoundStreamCallback_Ogg
	*/
	class SoundStreamCallback_Ogg : public NBsys::NDsound::Dsound_StreamCallback_Base
	{
	private:

		/** lockobject
		*/
		LockObject lockobject;

		/** ogg_file
		*/
		sharedptr<NBsys::NFile::File_Object> ogg_file;

		/** stream
		*/
		sharedptr<NBsys::NWave::Wave_Stream> stream;

		/** playend
		*/
		bool playend;

	public:

		/** constructor
		*/
		SoundStreamCallback_Ogg(const sharedptr<NBsys::NFile::File_Object>& a_ogg_file)
			:
			//lockobject(),
			ogg_file(a_ogg_file),
			stream()
		{
		}

		/** destructor
		*/
		virtual ~SoundStreamCallback_Ogg()
		{
		}

	public:

		/** 初期化。
		*/
		virtual NBsys::NWave::WaveType::Id Callback_Initialize()
		{
			AutoLock t_autolock(this->lockobject);

			this->stream = NBsys::NWave::CreateStream_Ogg(this->ogg_file->GetLoadData(),static_cast<s32>(this->ogg_file->GetLoadSize()));

			s32 t_channel = this->stream->GetChannel();
			s32 t_bit = this->stream->GetBit();
			s32 t_rate = this->stream->GetRate();

			NBsys::NWave::WaveType::Id t_wavetype = NBsys::NWave::WaveType::None;
			if(t_rate == 44100){
				if(t_bit == 8){
					if(t_channel == 1){
						t_wavetype = NBsys::NWave::WaveType::Mono_8_44100;
					}else if(t_channel == 2){
						t_wavetype = NBsys::NWave::WaveType::Stereo_8_44100;
					}
				}else if(t_bit == 16){
					if(t_channel == 1){
						t_wavetype = NBsys::NWave::WaveType::Mono_16_44100;
					}else if(t_channel == 2){
						t_wavetype = NBsys::NWave::WaveType::Stereo_16_44100;
					}
				}
			}

			return t_wavetype;
		}

		/** 再生。
		*/
		virtual void Callback_Play()
		{
			this->stream->SeekStart();
			this->playend = false;
		}

		/** データ取得。
		*/
		virtual void Callback_GetData(RingBufferBase<u8>& a_buffer,s32 a_need_size,bool a_is_loop)
		{
			AutoLock t_autolock(this->lockobject);

			while(a_buffer.GetUseSize() < a_need_size){
				bool t_ret = this->stream->Stream(a_buffer,a_is_loop);
				if(t_ret == false){
					//終端。

					this->playend = true;

					//残りの必要サイズ。
					s32 t_need_size = a_need_size - a_buffer.GetUseSize();

					s32 t_free_size = a_buffer.GetContinuousFreeSize();
					if(t_free_size > t_need_size){
						t_free_size = t_need_size;
					}

					if(t_free_size > 0){
						NMemory::Set(a_buffer.GetItemFromFreeList(0),0,t_free_size);
						a_buffer.AddUse(t_free_size);
					}
				}
			}
		}

		/** 再生終了チェック。
		*/
		virtual bool Callback_IsPlayEnd()
		{
			return this->playend;
		}

	};


}}
#pragma warning(pop)
#endif

