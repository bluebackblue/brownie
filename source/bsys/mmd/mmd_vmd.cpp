

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ‚l‚l‚cB‚o‚l‚wB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./mmd_vmd.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_VMD_ENABLE)
namespace NBsys{namespace NMmd
{

	/** Load_Header
	*/
	bool Mmd_Vmd::Load_Header(u8*& a_raw)
	{
		//Mmd_Vmd_Header
		this->header_a = Memory::Copy< Mmd_Vmd_Header_A >(a_raw,COUNTOF(Mmd_Vmd_Header_A::string) * sizeof(char));
		this->header_b = Memory::Copy< Mmd_Vmd_Header_B >(a_raw,COUNTOF(Mmd_Vmd_Header_B::string) * sizeof(char));

		STLWString t_w_string;
		STLString t_string = this->header_b.string;
		CharToWchar(t_string,t_w_string);

		return true;
	}

	/** Load
	*/
	bool Mmd_Vmd::Load(sharedptr< NFile::File_Object >& a_file)
	{
		if(a_file->IsBusy() == true){
			return false;
		}

		sharedptr< u8 >& t_data = a_file->GetLoadData();
		u8* t_raw = t_data.get();
		
		{
			if(this->Load_Header(t_raw) == false){
				return false;
			}
		}

		return true;
	}

}}
#endif

