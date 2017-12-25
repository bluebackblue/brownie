#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ＭＭＤ。ＰＭＸ。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../file/file.h"
#include "../geometry/geometry.h"
#include "../color/color.h"


/** include
*/
#include "./mmd_vmd_type.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_ENABLE)
namespace NBsys{namespace NMmd
{
	/** Mmd_Vmd
	*/
	class Mmd_Vmd
	{
	public:

		/** header_a
		*/
		Mmd_Vmd_Header_A header_a;

		/** header_b
		*/
		Mmd_Vmd_Header_B header_b;

	public:

		/** constructor
		*/
		Mmd_Vmd()
		{
		}

		/** destructor
		*/
		~Mmd_Vmd()
		{
		}

	private:

		/** Load_Header
		*/
		bool Load_Header(u8*& a_raw);

	public:

		/** Load
		*/
		bool Load(sharedptr<NFile::File_Object>& a_file);

	};


}}
#endif

