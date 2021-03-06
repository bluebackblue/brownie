﻿

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＭＭＤ。ＰＭＸ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./mmd_vmd.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NMmd
*/
#if(BSYS_MMD_ENABLE)
namespace NBsys{namespace NMmd
{
	/** Load_Header
	*/
	bool Mmd_Vmd::Load_Header(u8*& a_raw)
	{
		//Mmd_Vmd_Header
		this->header_a = NMemory::StreamCopy<Mmd_Vmd_Header_A>(a_raw,COUNTOF(Mmd_Vmd_Header_A::string) * sizeof(char));
		this->header_b = NMemory::StreamCopy<Mmd_Vmd_Header_B>(a_raw,COUNTOF(Mmd_Vmd_Header_B::string) * sizeof(char));

		STLWString t_w_string;
		STLString t_string = this->header_b.string;
		CharToWchar(t_string,t_w_string);

		return true;
	}


	/** Load
	*/
	bool Mmd_Vmd::Load(sharedptr<NFile::File_Object>& a_file)
	{
		if(a_file->IsBusy() == true){
			return false;
		}

		sharedptr<u8>& t_data = a_file->GetLoadData();
		u8* t_raw = t_data.get();
		
		if(t_raw){
			if(this->Load_Header(t_raw) == false){
				return false;
			}
		}else{
			return false;
		}

		return true;
	}


}}
#endif

