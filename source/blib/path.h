#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�X�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** Path
	*/
	class Path
	{
	public:

		/** [static]Dir
	
		a_path	: �p�X�B
		return	: �p�X�B

		*/
		static STLWString Dir(const STLWString& a_path);


		/** [static]Name

		a_name	: ([�p�X]+���O)�B
		return	: ([�p�X]+���O)�B

		*/
		static STLWString Name(const STLWString& a_name);


		/** [static]DirAndName

		a_path	: �p�X�B
		a_name	: ([�p�X]+���O)�B
		return	: �p�X�{([�p�X]+���O)�B

		*/
		static STLWString DirAndName(const STLWString& a_path,const STLWString& a_name);


		/** [static]DirAndDir

		a_path_a	: �p�X�B
		a_path_b	: �p�X�B
		return		: �p�X�{�p�X�B

		*/
		static STLWString DirAndDir(const STLWString& a_path_a,const STLWString& a_path_b);
	};

}

