#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイルハンドル。実装部分。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./filehandle.h"
#include "./staticassert.h"
#include "./debugassert.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBlib
*/
namespace NBlib
{
	/** FileHandle_Impl
	*/
	class FileHandle_Impl
	{
	private:
		/** handle
		*/
		#if defined(PLATFORM_VCWIN)

		HANDLE rawhandle;

		#endif

		/** isopen
		*/
		bool isopen;

		/** readmode
		*/
		bool readmode;

	public:
		/** constructor
		*/
		FileHandle_Impl() noexcept;

		/** destructor
		*/
		nonvirtual ~FileHandle_Impl() noexcept;

	public:
		/** ReadOpen
		*/
		bool ReadOpen(const STLWString& a_filename);

		/** WriteOpen
		*/
		bool WriteOpen(const STLWString& a_filename);

		/** Close
		*/
		void Close();

		/** Read
		*/
		bool Read(u8* a_buffer,s64 a_size,s64 a_offset);

		/** Write
		*/
		bool Write(const u8* a_buffer,s64 a_size,s64 a_offset);

		/** GetSize
		*/
		s64 GetSize() const;

		/** IsOpen
		*/
		bool IsOpen() const;

		/** SetEOF
		*/
		void SetEOF(s64 a_offset);

		/** GetHandle
		*/
		#if defined(PLATFORM_VCWIN)

		HANDLE GetRawHandle() const;

		#endif

	};
}

