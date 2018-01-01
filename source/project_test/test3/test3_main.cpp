

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
		t_window->Create(L"TEST " DEF_TEST_STRING,100,100);

		//Winsock開始。
		NBsys::NWinsock::StartSystem();

		//SSL開始。
		NBsys::NOpenSsl::StartSystem();

		//SSL終了。
		NBsys::NOpenSsl::EndSystem();

		{
			sharedptr<NBsys::NHttp::Http> t_http(new NBsys::NHttp::Http());
			{
				t_http->SetHost("bbbproject.sakura.ne.jp");
				t_http->SetPort(80);
				t_http->SetSsl(false);
				t_http->SetMode(NBsys::NHttp::Http_Mode::Get);
				t_http->SetUrl("/");
			}

			sharedptr<RingBuffer<u8,1*1024*1024,true>> t_recvbuffer(new RingBuffer<u8,1*1024*1024,true>());

			t_http->ConnectStart(t_recvbuffer);
			while(1){
				 bool t_ret = t_http->ConnectUpdate();
				 if((t_ret == true)||(t_recvbuffer->GetUseSize()>0)){

					//u8* t_recv_data = t_recvbuffer->GetItemFromUseList(0);
					//s32 t_recv_size = t_recvbuffer->GetUseSize();

					if(t_http->IsRecvHeader()){
						//ヘッダー読み込み済み。

						//リングバッファからデータを取得したことにする。
						t_recvbuffer->AddFree(t_recvbuffer->GetUseSize());
					}
				}else{
					t_http->ConnectEnd();
					t_http.reset();
					break;
				}
			}


		}

		//Winsock終了。
		NBsys::NWinsock::EndSystem();

		while(true){
			//s_window
			t_window->Update();
			if(t_window->IsEnd() == true){
				break;
			}
		}

		//ウィンドウ削除。
		t_window->Delete();
		t_window.reset();

		return;
	}


}
#endif

