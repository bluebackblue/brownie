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

	public:

		/** get_last
		*/
		static iterator get_last_safe(Type& a_list)
		{
			iterator t_it_last = a_list.end();

			if(a_list.size() > 0){
				--t_it_last;
			}

			return t_it_last;
		}

		/** get_prev
		*/
		static iterator get_prev_safe(Type& a_list,iterator& a_it)
		{
			iterator t_it_before = a_it;

			if(a_list.begin() != t_it_before){
				--t_it_before;
			}else{
				t_it_before = a_list.end();
			}

			return t_it_before;
		}

		/** get_last
		*/
		static iterator get_last(Type& a_list)
		{
			iterator t_it_last = a_list.end();
			--t_it_last;
			return t_it_last;
		}

	};


	/** STLList<T>::Type = STLListType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)
	template <typename T> using STLListType = typename STLList<T>::Type;
	#endif


}

