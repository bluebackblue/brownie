

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�X�B
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


/** NBlib
*/
namespace NBlib
{

	/** [static]Dir

	a_path	: �p�X�B
	return	: �p�X�B

	*/
	STLWString Path::Dir(const STLWString& a_path)
	{
		STLWString t_ret;

		for(s32 ii=0;ii<static_cast<s32>(a_path.length());ii++){
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


	/** [static]Name

	a_name	: ([�p�X]+���O)�B
	return	: ([�p�X]+���O)�B

	*/
	STLWString Path::Name(const STLWString& a_name)
	{
		STLWString t_ret;

		for(s32 ii=0;ii<static_cast<s32>(a_name.length());ii++){
			if(a_name[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_name[ii];
			}
		}

		return t_ret;
	}


	/** [static]DirAndName

	a_path	: �p�X�B
	a_name	: ([�p�X]+���O)�B
	return	: �p�X�{([�p�X]+���O)�B

	*/
	STLWString Path::DirAndName(const STLWString& a_path,const STLWString& a_name)
	{
		STLWString t_ret;

		for(s32 ii=0;ii<static_cast<s32>(a_path.length());ii++){
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

		for(s32 ii=0;ii<static_cast<s32>(a_name.length());ii++){
			if(a_name[ii] == '\\'){
				t_ret += L'/';
			}else{
				t_ret += a_name[ii];
			}
		}

		return t_ret;
	}


	/** [static]DirAndDir

	a_path_a	: �p�X�B
	a_path_b	: �p�X�B
	return		: �p�X�{�p�X�B

	*/
	STLWString Path::DirAndDir(const STLWString& a_path_a,const STLWString& a_path_b)
	{
		STLWString t_ret;

		for(s32 ii=0;ii<static_cast<s32>(a_path_a.length());ii++){
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

		for(s32 ii=0;ii<static_cast<s32>(a_path_b.length());ii++){
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

