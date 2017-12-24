#pragma once

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


/** AutoTest
*/
#if(DEF_TEST_AUTO)
struct AutoTest
{
public:

	/** d3d11
	*/
	sharedptr<NBsys::ND3d11::D3d11> d3d11; 

	/** capture_step
	*/
	s32 capture_step;

	/** capture_texture
	*/
	sharedptr<NBsys::NTexture::Texture> capture_texture;

	/** capture_jpg
	*/
	sharedptr<u8> capture_jpg;

	/** capture_jpg_size
	*/
	s32 capture_jpg_size;

	/** send_step
	*/
	#if(BSYS_HTTP_ENABLE)
	s32 send_step;
	#endif

	/** send_http
	*/
	#if(BSYS_HTTP_ENABLE)
	sharedptr<NBsys::NHttp::Http> send_http;
	#endif

	#if(BSYS_HTTP_ENABLE)
	sharedptr<RingBufferBase<u8>> send_recvbuffer;
	#endif

	/** send_end
	*/
	#if(BSYS_HTTP_ENABLE)
	bool send_end;
	#endif

public:
	/** constructor
	*/
	AutoTest();

	/** destructor
	*/
	nonvirtual ~AutoTest();

public:
	/** 更新。
	*/
	void Update();

};
#endif

