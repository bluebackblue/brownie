#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＳＴＬリスト。
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
#include <list>


/*

	STLList<TYPE>::Type
	std::listのアロケータ指定バージョン。

*/


/** NBlib
*/
namespace NBlib
{
	/** STLList
	*/
	template <typename T,typename STLALLOCATOR=STLAllocator<T>> class STLList
	{
	public:
		typedef std::list<T,STLALLOCATOR>									Type;
		typedef typename std::list<T,STLALLOCATOR>::iterator				iterator;
		typedef typename std::list<T,STLALLOCATOR>::const_iterator			const_iterator;

	private:
		STLList();
		//nonvirtual ~STLList() = delete;

	};

	/** STLListType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)
	template <typename T> using STLListType = typename STLList<T>::Type;
	#endif
}

