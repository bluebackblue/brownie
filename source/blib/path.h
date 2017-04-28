#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パス。
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
	
		a_path	: パス。
		return	: パス。

		*/
		static STLWString Dir(const STLWString& a_path);


		/** [static]Name

		a_name	: ([パス]+名前)。
		return	: ([パス]+名前)。

		*/
		static STLWString Name(const STLWString& a_name);


		/** [static]DirAndName

		a_path	: パス。
		a_name	: ([パス]+名前)。
		return	: パス＋([パス]+名前)。

		*/
		static STLWString DirAndName(const STLWString& a_path,const STLWString& a_name);


		/** [static]DirAndDir

		a_path_a	: パス。
		a_path_b	: パス。
		return		: パス＋パス。

		*/
		static STLWString DirAndDir(const STLWString& a_path_a,const STLWString& a_path_b);
	};

}

