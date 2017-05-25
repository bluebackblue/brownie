

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÇlÇlÇcÅBÇoÇlÇwÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../file/file.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NMmdPmx
{

	bool Load(sharedptr< NFile::File_Object >& a_file)
	{
		if(a_file->IsBusy() == true){
			return false;
		}

		sharedptr< u8 >& t_data = a_file->GetLoadData();

		/*
			if (!ReadHeader(pmxFile, file))
			{
				SABA_ERROR("ReadHeader Fail.");
				return false;
			}

			if (!ReadInfo(pmxFile, file))
			{
				SABA_ERROR("ReadInfo Fail.");
				return false;
			}

			if (!ReadVertex(pmxFile, file))
			{
				SABA_ERROR("ReadVertex Fail.");
				return false;
			}

			if (!ReadFace(pmxFile, file))
			{
				SABA_ERROR("ReadFace Fail.");
				return false;
			}

			if (!ReadTexture(pmxFile, file))
			{
				SABA_ERROR("ReadTexture Fail.");
				return false;
			}

			if (!ReadMaterial(pmxFile, file))
			{
				SABA_ERROR("ReadMaterial Fail.");
				return false;
			}

			if (!ReadBone(pmxFile, file))
			{
				SABA_ERROR("ReadBone Fail.");
				return false;
			}

			if (!ReadMorph(pmxFile, file))
			{
				SABA_ERROR("ReadMorph Fail.");
				return false;
			}

			if (!ReadDisplayFrame(pmxFile, file))
			{
				SABA_ERROR("ReadDisplayFrame Fail.");
				return false;
			}

			if (!ReadRigidbody(pmxFile, file))
			{
				SABA_ERROR("ReadRigidbody Fail.");
				return false;
			}

			if (!ReadJoint(pmxFile, file))
			{
				SABA_ERROR("ReadJoint Fail.");
				return false;
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadSoftbody(pmxFile, file))
				{
					SABA_ERROR("ReadSoftbody Fail.");
					return false;
				}
			}

			return true
		*/
		

		return true;
	}

}}
#endif

