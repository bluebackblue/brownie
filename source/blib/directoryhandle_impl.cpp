

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�B���N�g���n���h���B���������B
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./debugassert.h"
#include "./directoryhandle_impl.h"
#include "./path.h"


/** NBlib
*/
namespace NBlib
{
	/** constructor
	*/
	DirectoryHandle_Impl::DirectoryHandle_Impl() throw()
		:
		#if defined(PLATFORM_VCWIN)

		rawhandle(INVALID_HANDLE_VALUE),

		#endif
		isopen(false),
		list(),
		fullpath(L"")
	{
	}

	/** destructor
	*/
	DirectoryHandle_Impl::~DirectoryHandle_Impl() throw()
	{
		this->Close();
	}

	/** Open
	*/
	bool DirectoryHandle_Impl::Open(const STLWString& a_directoryname)
	{
		if(this->isopen == false){
			#if defined(PLATFORM_VCWIN)
			{
				//�t���p�X�B
				this->fullpath = Path::Dir(a_directoryname);

				//�����p�X�B
				STLWString t_filepath = Path::DirAndName(this->fullpath,L"*");

				//��ځB
				{
					WIN32_FIND_DATAW t_finddata;
					this->rawhandle = ::FindFirstFileW(t_filepath.c_str(),&t_finddata);
					if(this->rawhandle == INVALID_HANDLE_VALUE){
						return false;
					}
					DirectoryHandle::DirectoryItem t_item;
					{
						t_item.name = t_finddata.cFileName;
						t_item.is_directory = ((t_finddata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)?(true):(false));
					}
					if((t_item.name != L".")&&(t_item.name != L"..")){
						this->list.push_back(t_item);
					}
				}

				//��ڈȍ~�B
				while(1){
					WIN32_FIND_DATAW t_finddata;
					BOOL t_ret = ::FindNextFileW(this->rawhandle,&t_finddata);
					if(t_ret != TRUE){
						break;
					}else{
						DirectoryHandle::DirectoryItem t_item;
						{
							t_item.name = t_finddata.cFileName;
							t_item.is_directory = ((t_finddata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)?(true):(false));
						}
						if((t_item.name != L".")&&(t_item.name != L"..")){
							this->list.push_back(t_item);
						}
					}
				}

				::FindClose(this->rawhandle);
				this->rawhandle = INVALID_HANDLE_VALUE;
			}
			#endif

			this->isopen = true;
			return true;
		}

		return false;
	}

	/** Close
	*/
	void DirectoryHandle_Impl::Close()
	{
		if(this->isopen){
			this->isopen = false;	
		}
	}

	/** �T�C�Y�B
	*/
	s32 DirectoryHandle_Impl::GetSize()
	{
		return static_cast<s32>(this->list.size());
	}

	/** �擾�B
	*/
	DirectoryHandle::DirectoryItem& DirectoryHandle_Impl::GetItem(s32 a_index)
	{
		ASSERT((0<=a_index)&&(a_index<static_cast<s32>(this->list.size())));

		return this->list[a_index];
	}

	/** �t���p�X�擾�B
	*/
	STLWString& DirectoryHandle_Impl::GetFullPath()
	{
		return this->fullpath;
	}
}

