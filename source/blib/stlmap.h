#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
#include <map>


#if(BLIB_STDUNORDEREDMAP_ENABLE)

	#include <unordered_map>

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
		typedef std::map<KEY,T,PR,STLALLOCATOR>								Type;
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::value_type		value_type;
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::iterator			iterator;
		typedef typename std::map<KEY,T,PR,STLALLOCATOR>::const_iterator	const_iterator;

	private:
		STLBtMap();
		//nonvirtual ~STLBtMap() = delete;

	};

	/** STLBtMapType
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
			typedef std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>								Type;
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::value_type			value_type;
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::iterator			iterator;
			typedef typename std::unordered_map<KEY,T,H,KEYEQ,STLALLOCATOR>::const_iterator		const_iterator;

		private:
			STLMap();
			//nonvirtual ~STLMap() = delete;

		};

	#else

		#define STLMap STLBtMap

	#endif

	/** STLMapType
	*/
	#if(BLIB_STDALIASTEMPLATE_ENABLE)

		template <typename KEY,typename T,typename H=std::hash<KEY>,typename KEYEQ=std::equal_to<KEY>,class STLALLOCATOR=STLAllocator<std::pair<const KEY,T>>> using STLMapType=typename STLMap<KEY,T,H,KEYEQ,STLALLOCATOR>::Type;

	#endif
}

