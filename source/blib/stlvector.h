#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＳＴＬベクター。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./staticassert.h"
#include "./stlallocator.h"


/** include
*/
#include <vector>


/*

	STLVector<TYPE>::Type
	std::vectorのアロケータ指定バージョン。

*/


/** NBlib
*/
namespace NBlib
{
	/** STLVector
	*/
	template <typename T,typename STLALLOCATOR=STLAllocator<T> > class STLVector
	{
	public:
		typedef std::vector<T,STLALLOCATOR>									Type;
		typedef typename std::vector<T,STLALLOCATOR>::iterator				iterator;
		typedef typename std::vector<T,STLALLOCATOR>::const_iterator		const_iterator;

	private:
		STLVector();
		//nonvirtual ~STLVector() = delete;

	};

	/** STLVectorType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)
	template <typename T,typename STLALLOCATOR=STLAllocator<T>> using STLVectorType=typename STLVector<T,STLALLOCATOR>::Type;
	#endif
}

