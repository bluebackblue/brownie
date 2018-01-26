﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief gdiplus
*/


/** include
*/
#include <brownie_config/windows_include.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4514 4365 4263 4264 4458 4061 4820)

#if defined(new)
#undef new
#endif

#include <gdiplus.h>

#if defined(custom_new)
#define new custom_new
#endif

#pragma warning(pop)

