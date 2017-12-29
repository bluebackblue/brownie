

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パス。
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
#include "./path.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib
*/
namespace NBlib
{
	/** [static]パスの整形。

	a_path	: パス。
	return	: パス。

	*/
	STLWString Path::Dir(const STLWString& a_path)
	{
		STLWString t_ret;

		for(u32 ii=0;ii<static_cast<u32>(a_path.length());ii++){
			if(a_path[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_path[ii];
			}
		}

		if(t_ret.length() > 0){
			if(t_ret[t_ret.length() - 1] != L'/'){
				t_ret += L'/';
			}
		}

		return t_ret;
	}


	/** [static]名前付きパスの整形。

	a_name	: ([パス]+名前)。
	return	: ([パス]+名前)。

	*/
	STLWString Path::Name(const STLWString& a_name)
	{
		STLWString t_ret;

		for(u32 ii=0;ii<static_cast<u32>(a_name.length());ii++){
			if(a_name[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_name[ii];
			}
		}

		return t_ret;
	}


	/** [static]パスと名前付きパスの合成。

	a_path	: パス。
	a_name	: ([パス]+名前)。
	return	: パス＋([パス]+名前)。

	*/
	STLWString Path::DirAndName(const STLWString& a_path,const STLWString& a_name)
	{
		STLWString t_ret;

		for(u32 ii=0;ii<static_cast<u32>(a_path.length());ii++){
			if(a_path[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_path[ii];
			}
		}

		if(t_ret.length() > 0){
			if(t_ret[t_ret.length() - 1] != L'/'){
				t_ret += L'/';
			}
		}

		for(u32 ii=0;ii<static_cast<u32>(a_name.length());ii++){
			if(a_name[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_name[ii];
			}
		}

		return t_ret;
	}


	/** [static]パスの合成。

	a_path_a	: パス。
	a_path_b	: パス。
	return		: パス＋パス。

	*/
	STLWString Path::DirAndDir(const STLWString& a_path_a,const STLWString& a_path_b)
	{
		STLWString t_ret;

		for(u32 ii=0;ii<static_cast<u32>(a_path_a.length());ii++){
			if(a_path_a[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_path_a[ii];
			}
		}

		if(t_ret.length() > 0){
			if(t_ret[t_ret.length() - 1] != L'/'){
				t_ret += L'/';
			}
		}

		for(u32 ii=0;ii<static_cast<u32>(a_path_b.length());ii++){
			if(a_path_b[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_path_b[ii];
			}
		}

		if(t_ret.length() > 0){
			if(t_ret[t_ret.length() - 1] != L'/'){
				t_ret += L'/';
			}
		}

		return t_ret;
	}


}

