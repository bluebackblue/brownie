﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 中レベルライブラリー。
*/


/** include
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
#include "./actionbatching/actionbatching.h"
#endif


/** include
*/
#if(BSYS_COLOR_ENABLE)
#include "./color/color.h"
#endif


/** include
*/
#if(BSYS_FILE_ENABLE)
#include "./file/file.h"
#endif


/** include
*/
#if(BSYS_FOVEHMD_ENABLE)
#include "./fovehmd/fovehmd.h"
#endif


/** include
*/
#if(BSYS_GEOMETRY_ENABLE)
#include "./geometry/geometry.h"
#endif


/** include
*/
#if(BSYS_VERTEX_ENABLE)
#include "./vertex/vertex.h"
#endif


/** include
*/
#if(BSYS_WINDOW_ENABLE)
#include "./window/window.h"
#endif


/** include
*/
#if(BSYS_OPENGL_ENABLE)
#include "./opengl/opengl.h"
#endif


/** include
*/
#if(BSYS_D3D11_ENABLE)
#include "./d3d11/d3d11.h"
#endif


/** include
*/
#if(BSYS_MMD_ENABLE)
#include "./mmd/mmd.h"
#endif


/** include
*/
#if(BSYS_TEXTURE_ENABLE)
#include "./texture/texture.h"
#endif


/** include
*/
#if(BSYS_FONT_ENABLE)
#include "./font/font.h"
#endif


/** include
*/
#if(BSYS_PAD_ENABLE)
#include "./pad/pad.h"
#endif


/** include
*/
#if(BSYS_WINDOWMENU_ENABLE)
#include "./windowmenu/windowmenu.h"
#endif


/** include
*/
#if(BSYS_HTTP_ENABLE)
#include "./http/http.h"
#endif


/** include
*/
#if(BSYS_WINSOCK_ENABLE)
#include "./winsock/winsock.h"
#endif


/** include
*/
#if(BSYS_COMMANDLINE_ENABLE)
#include "./commandline/commandline.h"
#endif


/** include
*/
#if(BSYS_OPENSSL_ENABLE)
#include "./openssl/openssl.h"
#endif


/** include
*/
#if(BSYS_WAVE_ENABLE)
#include "./wave/wave.h"
#endif


/** include
*/
#if(BSYS_DSOUND_ENABLE)
#include "./dsound/dsound.h"
#endif


/**
*/
#if(BSYS_JOY_ENABLE)
#include "./joy/joy.h"
#endif

