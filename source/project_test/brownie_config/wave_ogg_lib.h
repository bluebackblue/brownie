#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief fovehmd
*/


#if defined(ROM_MASTER)
	#if defined(ROM_32BIT)

		/** lib
		*/
		#pragma comment(lib,"ogg/Win32/Release/libogg_static.lib")
		#pragma comment(lib,"ogg/Win32/Release/libvorbis_static.lib")
		#pragma comment(lib,"ogg/Win32/Release/libvorbisfile_static.lib")

	#elif defined(ROM_64BIT)

		/** lib
		*/
		#pragma comment(lib,"ogg/x64/Release/libogg_static.lib")
		#pragma comment(lib,"ogg/x64/Release/libvorbis_static.lib")
		#pragma comment(lib,"ogg/x64/Release/libvorbisfile_static.lib")

	#endif
#else
	#if defined(ROM_32BIT)

		/** lib
		*/
		#pragma comment(lib,"ogg/Win32/Debug/libogg_static.lib")
		#pragma comment(lib,"ogg/Win32/Debug/libvorbis_static.lib")
		#pragma comment(lib,"ogg/Win32/Debug/libvorbisfile_static.lib")

	#elif defined(ROM_64BIT)

		/** lib
		*/
		#pragma comment(lib,"ogg/x64/Debug/libogg_static.lib")
		#pragma comment(lib,"ogg/x64/Debug/libvorbis_static.lib")
		#pragma comment(lib,"ogg/x64/Debug/libvorbisfile_static.lib")

	#endif
#endif

