#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コンフィグ。
*/


/** lib
*/
#if defined(ROM_MASTER)
	#if defined(ROM_32BIT)
		#pragma comment(lib, "png/lpng/projects/visualc71/Win32_LIB_Release/ZLib/zlib.lib")
		#pragma comment(lib, "png/lpng/projects/visualc71/Win32_LIB_Release/libpngd.lib")
	#else
		#pragma comment(lib, "png/lpng/projects/visualc71/x64/LIB Release/zlib64.lib")
		#pragma comment(lib, "png/lpng/projects/visualc71/x64/LIB Release/libpng64.lib")
	#endif
#else
	#if defined(ROM_32BIT)
	#pragma comment(lib, "png/lpng/projects/visualc71/Win32_LIB_Debug/ZLib/zlibd.lib")
	#pragma comment(lib, "png/lpng/projects/visualc71/Win32_LIB_Debug/libpng.lib")
	#else
	#pragma comment(lib, "png/lpng/projects/visualc71/x64/LIB Debug/zlib64d.lib")
	#pragma comment(lib, "png/lpng/projects/visualc71/x64/LIB Debug/libpng64d.lib")
	#endif
#endif


