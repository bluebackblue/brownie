

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


#if(DEF_TEST_AUTO)

/** constructor
*/
AutoTest::AutoTest()
	:
	d3d11(),
	capture_step(-1),
	capture_texture(),
	capture_jpg(),
	capture_jpg_size(0),

	#if(BSYS_HTTP_ENABLE)
	send_step(-1),
	send_http(),
	send_recvbuffer(),
	send_end(false)
	#endif
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
		this->capture_texture = this->d3d11->Render_ScreenShot();
		this->capture_step++;
	}else if(this->capture_step == 1){
		//ＪＰＧエンコード。
		std::tuple<sharedptr<u8>,s32> t_jpg_data = NBsys::NTexture::EncodeToJpg(this->capture_texture);
		this->capture_jpg = std::get<0>(t_jpg_data);
		this->capture_jpg_size = std::get<1>(t_jpg_data);
		this->capture_step++;
	}else if(this->capture_step == 2){
		this->capture_step = -1;
		this->send_step = 0;
	}

	#if(BSYS_HTTP_ENABLE)
	if(this->send_step == 0){
		//通信開始。
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

		this->send_step++;
	}else if(this->send_step == 1){
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
	}else if(this->send_step == 2){

		this->send_end = true;

		this->send_step = -1;
	}
	#endif
}

#endif

