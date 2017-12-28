#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#pragma warning(disable:4710)
#pragma warning(push)
#pragma warning(disable:4820 4514 4365 4987 4571)
#include <list>
#pragma warning(pop)


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

		/** Type
		*/
		typedef std::list<T,STLALLOCATOR> Type;

		/** iterator
		*/
		typedef typename std::list<T,STLALLOCATOR>::iterator iterator;

		/** const_iterator
		*/
		typedef typename std::list<T,STLALLOCATOR>::const_iterator const_iterator;

	private:

		/** constructor
		*/
		STLList() = delete;

		/** destructor
		*/
		nonvirtual ~STLList() = delete;

	};


	/** STLList<T>::Type = STLListType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)
	template <typename T> using STLListType = typename STLList<T>::Type;
	#endif


}

