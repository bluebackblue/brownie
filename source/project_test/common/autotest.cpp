

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 自動テスト。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./autotest.h"


/** NTest
*/
#if(DEF_TEST_AUTO)
namespace NTest
{
	/** constructor
	*/
	AutoTest::AutoTest()
		:
		action_start(false),
		action_end(false),
		#if(BSYS_D3D11_ENABLE)
		d3d11(),
		#endif

		capture_step(-1),
		#if(BSYS_TEXTURE_ENABLE)
		capture_texture(),
		#endif
		capture_jpg(),
		capture_jpg_size(0),
		send_step(-1),
		#if(BSYS_HTTP_ENABLE)
		send_http(),
		#endif
		send_recvbuffer()
	{
	}


	/** destructor
	*/
	AutoTest::~AutoTest()
	{
	}


	/** 更新。
	*/
	void AutoTest::Update()
	{
		if(this->capture_step == 0){
			//スクリーンショット。

			#if(BSYS_TEXTURE_ENABLE)
			this->capture_texture = this->d3d11->Render_ScreenShot();
			#endif

			this->capture_step++;
		}else if(this->capture_step == 1){
			//ＪＰＧエンコード。

			std::tuple<sharedptr<u8>,s32> t_jpg_data;
			#if(BSYS_TEXTURE_ENABLE)
			t_jpg_data = NBsys::NTexture::EncodeToJpg(this->capture_texture);
			#endif
			this->capture_jpg = std::get<0>(t_jpg_data);
			this->capture_jpg_size = std::get<1>(t_jpg_data);

			this->capture_step++;
		}else if(this->capture_step == 2){
			//送信リクエスト。

			this->capture_step = -1;
			this->send_step = 0;
		}

		if(this->send_step == 0){
			//通信開始。

			#if(BSYS_HTTP_ENABLE)
			this->send_http.reset(new NBsys::NHttp::Http());

			this->send_http->SetHost("bbbproject.sakura.ne.jp");
			this->send_http->SetPort(80);
			this->send_http->SetMode(NBsys::NHttp::Http_Mode::Post);
			this->send_http->SetUrl("/www/project_autotest/index.php?mode=upload");
			this->send_http->AddPostContent("upfile","filename",this->capture_jpg,this->capture_jpg_size);

			{
				char t_buffer[16];
				STLString t_index_string = VASTRING(t_buffer,sizeof(t_buffer),"%d",DEF_TEST_INDEX);
				this->send_http->AddPostContent("index",t_index_string);
			}

			{
				STLWString t_log;
				t_log += L"---";
				STLString t_log_utf8;
				WcharToChar(t_log,t_log_utf8);
				this->send_http->AddPostContent("log",t_log_utf8);
			}

			{
				STLWString t_title = DEF_TEST_STRING;
				STLString t_title_utf8;
				WcharToChar(t_title,t_title_utf8);
				this->send_http->AddPostContent("title",t_title_utf8);
			}

			this->send_recvbuffer.reset(new RingBuffer<u8,1*1024*1024,true>());
			this->send_http->ConnectStart(this->send_recvbuffer);
			#endif

			this->send_step++;
		}else if(this->send_step == 1){
			//通信中。

			#if(BSYS_HTTP_ENABLE)
			 bool t_ret = this->send_http->ConnectUpdate();
			 if((t_ret == true)||(this->send_recvbuffer->GetUseSize()>0)){

				u8* t_recv_data = this->send_recvbuffer->GetItemFromUseList(0);
				s32 t_recv_size = this->send_recvbuffer->GetUseSize();

				if(this->send_http->IsRecvHeader()){
					//ヘッダー読み込み済み。

					//リングバッファからデータを取得したことにする。
					this->send_recvbuffer->AddFree(this->send_recvbuffer->GetUseSize());
				}
			}else{
				this->send_http->ConnectEnd();
				this->send_http.reset();
				this->send_step++;
			}
			#else
			{
				this->send_step++;
			}
			#endif

		}else if(this->send_step == 2){
			//終了。

			this->action_end = true;
			this->send_step = -1;
		}
	}


}
#endif

