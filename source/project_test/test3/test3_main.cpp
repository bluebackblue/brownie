

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(DEF_TEST_INDEX == 3)
namespace NTest
{
	/** Test_Main
	*/
	void Test_Main()
	{
		//ファイル。
		NBsys::NFile::StartSystem(1);
		NBsys::NFile::SetRoot(0,L"../../brownie_testdata");

		//ウィンドウ作成。
		sharedptr<NBsys::NWindow::Window> t_window(new NBsys::NWindow::Window());
		t_window->Create(L"TEST " DEF_TEST_STRING,100,100);

		//DirectSound。
		NBsys::NDsound::StartSystem(t_window);

		//パック読み込み。
		sharedptr<NBsys::NFile::File_Pack_Object> t_pack(new NBsys::NFile::File_Pack_Object(0,L"data/秋山裕和n77.pac",L"sound"));
		while(t_pack->IsBusy()){
			ThreadSleep(1);
		}

		if(t_pack->GetErrorCode() == ErrorCode::Success){
		}else{
			ASSERT(0);
		}

		//ＷＡＶファイル読み込み。
		sharedptr<NBsys::NFile::File_Object> t_wav_file(new NBsys::NFile::File_Object(0,L"sound/n77.wav",-1,nullptr,0));

		while(t_wav_file->IsBusy()){
			ThreadSleep(1);
		}

		if(t_wav_file->GetErrorCode() == ErrorCode::Success){
		}else{
			ASSERT(0);
		}

		//ＷＡＶファイル解析。
		sharedptr<NBsys::NWave::Wave> t_wav = NBsys::NWave::CreateWave_Wav(t_wav_file->GetLoadData(),static_cast<s32>(t_wav_file->GetLoadSize()),L"n77");

		s32 t_id = NBsys::NDsound::CreateSoundBuffer(t_wav,false);

		s32 t_time = 0;

		u64 t_pcounter = PerformanceCounter::GetPerformanceCounter();
		while(true){
			{
				u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
				u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
				float t_delta = static_cast<float>(t_pcounter_now - t_pcounter) / t_pcounter_sec;
				if(t_delta <= 1.0f / 60){
					continue;
				}
				t_pcounter = t_pcounter_now;
			}

			//s_window
			t_window->Update();
			if(t_window->IsEnd() == true){
				break;
			}

			NBsys::NDsound::Update();

			if(t_time % (60 * 3) == 0){
				


				NBsys::NDsound::Play(t_id,true,false,true);
				t_time = 0;
			}
			t_time++;
		}

		{
			NBsys::NDsound::DeleteSoundBuffer(t_id);
			NBsys::NDsound::Update();
		}

		NBsys::NDsound::EndSystemRequest();
		NBsys::NDsound::EndSystem();

		//ウィンドウ削除。
		t_window->Delete();
		t_window.reset();

		//ファイル。
		NBsys::NFile::EndSystemRequest();
		NBsys::NFile::EndWaitSystem();

		#if(0)

		//Winsock開始。
		NBsys::NWinsock::StartSystem();

		//SSL開始。
		NBsys::NOpenSsl::StartSystem();

		{
			sharedptr<NBsys::NHttp::Http> t_http(new NBsys::NHttp::Http());
			{
				t_http->SetHost("127.0.0.1");
				t_http->SetPort(443);
				t_http->SetSsl(true);
				t_http->SetMode(NBsys::NHttp::Http_Mode::Get);
				t_http->SetUrl("/");
			}

			sharedptr<RingBuffer<u8,1*1024*1024,true>> t_recvbuffer(new RingBuffer<u8,1*1024*1024,true>());

			t_http->ConnectStart(t_recvbuffer);
			while(1){
				 bool t_ret = t_http->ConnectUpdate();
				 if((t_ret == true)||(t_recvbuffer->GetUseSize()>0)){
					if(t_http->IsRecvHeader()){
						//ヘッダー読み込み済み。

						char t_buffer[16] = {0};
						s32 t_copysize = t_recvbuffer->GetUseSize();
						if(t_copysize > sizeof(t_buffer) - 1){
							t_copysize = sizeof(t_buffer) - 1;
						}

						t_recvbuffer->CopyFromBuffer(reinterpret_cast<u8*>(t_buffer),t_copysize);

						DEBUGLOG("%s",t_buffer);
						//std::cout << t_buffer << std::endl;
					}
				}else{
					t_http->ConnectEnd();
					t_http.reset();
					break;
				}
			}
		}

		//スレッド関連ステートの削除。
		NBsys::NOpenSsl::SslDeleteThreadState();

		//SSL終了。
		NBsys::NOpenSsl::EndSystem();

		//Winsock終了。
		NBsys::NWinsock::EndSystem();

		#endif

		return;
	}


}
#endif

