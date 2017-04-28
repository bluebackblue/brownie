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
#include "./file_pack_workitem.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_PACK_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_Pack
	*/
	class File_Pack
	{
	private:
		/** ���b�N�I�u�W�F�N�g�B
		*/
		LockObject& lockobject;

		/** �p�b�N���X�g�B
		*/
		STLList< sharedptr< File_Pack_WorkItem > >::Type list;

	public:
		/** constructor
		*/
		File_Pack(LockObject& a_lockobject);

		/** destructor
		*/
		nonvirtual ~File_Pack();

		/** �o�^�B
		*/
		void Resist(const sharedptr< File_Pack_WorkItem >& a_workitem);

		/** �ǂݍ��ݍς݃p�b�N�̃`�F�b�N�B
		*/
		bool IsExist(const STLWString& a_pack_filename_short);

		/** �p�b�N����t�@�C�����J���B
		*/
		sharedptr< File_Pack_FileHandle >& CreatePackFileHandle(const STLWString& a_filename);

	};

}}
#endif

