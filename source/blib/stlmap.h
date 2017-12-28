#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＳＴＬマップ。
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
#pragma warning(disable:4514 4987 4365 4820)
#include <map>
#pragma warning(pop)


#if(BLIB_STDUNORDEREDMAP_ENABLE)

#pragma warning(disable:4710)
#pragma warning(push)
#pragma warning(disable:4987 4820 4514 4365 4625 4571)
#include <unordered_map>
#pragma warning(pop)

#endif


/*

	STLBtMap<KEY,T,PR,STLALLOCATOR>::Type
	STLMap<KEY,T,H,KEYEQ,STLALLOCATOR>::Type
	std::map / std::unordered_mapのアロケータ指定バージョン。

*/


/** NBlib
*/
namespace NBlib
{
	/** STLBtMap
	*/
	template <typename KEY,typename T,typename PR=std::less<KEY>,typename STLALLOCATOR=STLAllocator<std::pair<const KEY,T>>> class STLBtMap
	{
	public:

		/** Type
		*/
		typedef std::map<KEY,T,PR,STLALLOCATOR> Type;

		/** value_type
		*/
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::value_type value_type;

		/** iterator
		*/
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::iterator iterator;

		/** const_iterator
		*/
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::const_iterator const_iterator;

	private:

		/** constructor
		*/
		STLBtMap() = delete;

		/** destructor
		*/
		nonvirtual ~STLBtMap() = delete;

	};


	/** STLBtMap<KEY,T,PR,STLALLOCATOR>::Type = STLBtMapType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)

		template <typename KEY,typename T,typename PR=std::less<KEY>,typename STLALLOCATOR=STLAllocator<std::pair<const KEY,T>>> using STLBtMapType=typename STLBtMap<KEY,T,PR,STLALLOCATOR>::Type;

	#endif


	/** STLMap
	*/
	#if(BLIB_STDUNORDEREDMAP_ENABLE)

		template <typename KEY,typename T,typename H=std::hash<KEY>,typename KEYEQ=std::equal_to<KEY>,class STLALLOCATOR=STLAllocator<std::pair<const KEY,T>>> class STLMap
		{
		public:

			/** Type
			*/
			typedef std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR> Type;

			/** value_type
			*/
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::value_type value_type;

			/** iterator
			*/
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::iterator iterator;

			/** const_iterator
			*/
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::const_iterator const_iterator;

		private:

			/** constructor
			*/
			STLMap() = delete;

			/** destructor
			*/
			nonvirtual ~STLMap() = delete;

		};


		/** STLMap<KEY,T,H,KEYEQ,STLALLOCATOR>::Type = STLMapType
		*/
		#if(BLIB_STDALIASTEMPLATE_ENABLE)

			template <typename KEY,typename T,typename H=std::hash<KEY>,typename KEYEQ=std::equal_to<KEY>,class STLALLOCATOR=STLAllocator<std::pair<const KEY,T>>> using STLMapType=typename STLMap<KEY,T,H,KEYEQ,STLALLOCATOR>::Type;

		#endif

	#else

		#define STLMap STLBtMap

	#endif


}

