#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_pack_filehandle.h"


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** File_Pack_WorkItem
	*/
	class File_Pack_WorkItem
	{
	private:

		/** MainStep
		*/
		struct MainStep
		{
			enum Id
			{
				None = 0,
				Open,
				Read,
				End,
				Error,
			};
		};

		/** メインステップ。
		*/
		MainStep::Id mainstep;

		/** ファイルハンドル。
		*/
		FileHandle filehandle;

		/** パックファイル名。
		*/
		STLWString pack_filename_short;

		/** パックルートパス。
		*/
		STLWString pack_rootpath_short;

		/** データサイズ。
		*/
		s64 data_size;

		/** エラーコード。
		*/
		ErrorCode::Id errorcode;

		/** filelist
		*/
		STLMap<STLWString,sharedptr<File_Pack_FileHandle>>::Type filelist;

	public:

		/** constructor
		*/
		explicit File_Pack_WorkItem(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short);

		/** destructor
		*/
		nonvirtual ~File_Pack_WorkItem();

	public:

		/** エラーコード取得。
		*/
		ErrorCode::Id GetErrorCode() const;

		/** パックファイル名取得。
		*/
		const STLWString& GetPackFileNameShort();

		/** ファイル検索。
		*/
		sharedptr<File_Pack_FileHandle>& FindFromFileNameShort(const STLWString& a_filename_short);

		/** 更新。
		*/
		bool Update(const STLWString& a_rootpath_full);

	};


}}
#endif

