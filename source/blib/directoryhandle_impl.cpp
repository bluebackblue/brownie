

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ディレクトリハンドル。実装部分。
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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBlib
{
	/** constructor
	*/
	DirectoryHandle_Impl::DirectoryHandle_Impl() noexcept
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
	DirectoryHandle_Impl::~DirectoryHandle_Impl() noexcept
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
				//フルパス。
				this->fullpath = Path::Dir(a_directoryname);

				//検索パス。
				STLWString t_filepath = Path::DirAndName(this->fullpath,L"*");

				//一つ目。
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

				//二つ目以降。
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


	/** サイズ。
	*/
	s32 DirectoryHandle_Impl::GetSize()
	{
		return static_cast<s32>(this->list.size());
	}


	/** 取得。
	*/
	DirectoryHandle::DirectoryItem& DirectoryHandle_Impl::GetItem(s32 a_index)
	{
		ASSERT((0<=a_index)&&(a_index<static_cast<s32>(this->list.size())));

		return this->list[static_cast<std::size_t>(a_index)];
	}


	/** フルパス取得。
	*/
	STLWString& DirectoryHandle_Impl::GetFullPath()
	{
		return this->fullpath;
	}


}
#pragma warning(pop)

