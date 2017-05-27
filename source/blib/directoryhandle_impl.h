#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�B���N�g���n���h���B���������B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./directoryhandle.h"
#include "./staticassert.h"
#include "./debugassert.h"
#include "./stlvector.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBlib
*/
namespace NBlib
{
	/** DirectoryHandle_Impl
	*/
	class DirectoryHandle_Impl
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

		/** list
		*/
		STLVector< DirectoryHandle::DirectoryItem >::Type list;

		/** fullpath
		*/
		STLWString fullpath;

	public:
		/** constructor
		*/
		DirectoryHandle_Impl() noexcept;

		/** destructor
		*/
		nonvirtual ~DirectoryHandle_Impl() noexcept;

	public:
		/** Oepn
		*/
		bool Open(const STLWString& a_directoryname);

		/** Close
		*/
		void Close();

		/** �T�C�Y�B
		*/
		s32 GetSize();

		/** �擾�B
		*/
		DirectoryHandle::DirectoryItem& GetItem(s32 a_index);

		/** �t���p�X�擾�B
		*/
		STLWString& GetFullPath();

	};
}

