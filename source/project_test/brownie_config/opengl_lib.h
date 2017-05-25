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

		#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN32/lib-vc2015/glfw3.lib")
		#pragma comment(lib,"glew-2.0.0/lib/Release/Win32/glew32s.lib")
		#pragma comment(lib,"opengl32.lib")

	#else

		#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.lib")
		#pragma comment(lib,"glew-2.0.0/lib/Release/x64/glew32s.lib")
		#pragma comment(lib,"opengl32.lib")

	#endif
#else
	#if defined(ROM_32BIT)

		#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN32/lib-vc2015/glfw3.lib")
		#pragma comment(lib,"glew-2.0.0/lib/Release/Win32/glew32s.lib")
		#pragma comment(lib,"opengl32.lib")

	#else

		#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.lib")
		#pragma comment(lib,"glew-2.0.0/lib/Release/x64/glew32s.lib")
		#pragma comment(lib,"opengl32.lib")

	#endif
#endif


