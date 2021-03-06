﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 自動テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest
*/
#if(DEF_TEST_AUTO)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NTest{namespace NCommon
{
	/** AutoTest
	*/
	struct AutoTest
	{
	public:

		/** action_start
		*/
		bool action_start;

		/** action_end
		*/
		bool action_end;

		/** d3d11
		*/
		#if(BSYS_D3D11_ENABLE)
		sharedptr<NBsys::ND3d11::D3d11> d3d11; 
		#endif

	public:

		/** capture_step
		*/
		s32 capture_step;

		#if(BSYS_TEXTURE_ENABLE)

		/** capture_texture
		*/
		sharedptr<NBsys::NTexture::Texture> capture_texture;

		#endif

		/** capture_jpg
		*/
		sharedptr<u8> capture_jpg;

		/** capture_jpg_size
		*/
		s32 capture_jpg_size;

		/** send_step
		*/
		s32 send_step;

		/** send_http
		*/
		#if(BSYS_HTTP_ENABLE)
		sharedptr<NBsys::NHttp::Http> send_http;
		#endif

		/** send_recvbuffer
		*/
		sharedptr<RingBufferBase<u8>> send_recvbuffer;

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


}}
#pragma warning(pop)
#endif

