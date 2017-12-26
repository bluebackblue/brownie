#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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

		/** Type
		*/
		typedef std::vector<T,STLALLOCATOR> Type;

		/** iterator
		*/
		typedef typename std::vector<T,STLALLOCATOR>::iterator iterator;

		/** const_iterator
		*/
		typedef typename std::vector<T,STLALLOCATOR>::const_iterator const_iterator;

	private:

		/** constructor
		*/
		STLVector() = delete;

		/** destructor
		*/
		nonvirtual ~STLVector() = delete;

	};


	/** STLVector<T,STLALLOCATOR>::Type = STLVectorType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)
	template <typename T,typename STLALLOCATOR=STLAllocator<T>> using STLVectorType=typename STLVector<T,STLALLOCATOR>::Type;
	#endif


}

