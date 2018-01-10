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
	/** SoundStreamCallback
	*/
	class SoundStreamCallback : public NBsys::NDsound::Dsound_StreamCallback_Base
	{
	private:

		/** lockobject
		*/
		LockObject lockobject;

		/** ogg_file
		*/
		sharedptr<NBsys::NFile::File_Object> ogg_file;

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave;

		/** seek
		*/
		s32 seek;

	public:

		/** constructor
		*/
		SoundStreamCallback(const sharedptr<NBsys::NFile::File_Object>& a_ogg_file)
			:
			ogg_file(a_ogg_file),
			seek(0)
		{
		}

		/** destructor
		*/
		virtual ~SoundStreamCallback()
		{
		}

	public:

		/** タイプ取得。
		*/
		virtual NBsys::NWave::WaveType::Id Callback_GetWaveType()
		{
			AutoLock t_autolock(this->lockobject);

			this->wave = NBsys::NWave::CreateWave_Ogg(this->ogg_file->GetLoadData(),static_cast<s32>(this->ogg_file->GetLoadSize()),L"ogg");

			return this->wave->GetWaveType();
		}

		/** データ取得。
		*/
		virtual void Callback_GetData(RingBufferBase<u8>& a_buffer,s32 a_need_size)
		{
			AutoLock t_autolock(this->lockobject);

			s32 t_copy_size = 0;

			while(t_copy_size < a_need_size){
				s32 t_continuous_size = this->wave->GetSampleSize() - this->seek;

				if(t_continuous_size > a_need_size){
					t_continuous_size = a_need_size;
				}

				if(t_continuous_size > 0){

					a_buffer.CopyToBuffer(&this->wave->GetSample().get()[this->seek],t_continuous_size);
					
					this->seek += t_continuous_size;
					t_copy_size += t_continuous_size;
				}else{
					this->seek = 0;
				}
			}
		}

	};


}}
#pragma warning(pop)
#endif

