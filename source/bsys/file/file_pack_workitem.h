#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_pack_filehandle.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_PACK_ENABLE)
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

		/** ���C���X�e�b�v�B
		*/
		MainStep::Id mainstep;

		/** �t�@�C���n���h���B
		*/
		FileHandle filehandle;

		/** �p�b�N�t�@�C�����B
		*/
		STLWString pack_filename_short;

		/** �p�b�N���[�g�p�X�B
		*/
		STLWString pack_rootpath_short;

		/** �f�[�^�T�C�Y�B
		*/
		s64 data_size;

		/** �G���[�R�[�h�B
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

		/** �G���[�R�[�h�擾�B
		*/
		ErrorCode::Id GetErrorCode() const;

		/** �p�b�N�t�@�C�����擾�B
		*/
		const STLWString& GetPackFileNameShort();

		/** �t�@�C�������B
		*/
		sharedptr<File_Pack_FileHandle>& FindFromFileNameShort(const STLWString& a_filename_short);

		/** �X�V�B
		*/
		bool Update(const STLWString& a_rootpath_full);

	};

}}
#endif

