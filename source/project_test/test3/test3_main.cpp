

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
		//ウィンドウ作成。
		sharedptr<NBsys::NWindow::Window> t_window(new NBsys::NWindow::Window());
		t_window->Create(L"TEST " DEF_TEST_STRING,Size2DType<f32>(100.0f,100.0f));

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

		return;
	}


}
#endif

