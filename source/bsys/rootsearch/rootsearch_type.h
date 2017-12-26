#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 経路探査。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** RootSearch_NodeIndex
	*/
	class RootSearch_NodeIndex
	{
		s32 nodeindex;

	public:
		/** constructor
		*/
		RootSearch_NodeIndex(s32 a_nodeindex)
			:
			nodeindex(a_nodeindex)
		{
		}

		/** constructor
		*/
		RootSearch_NodeIndex()
			:
			nodeindex(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~RootSearch_NodeIndex()
		{
		}

		/** GetValue
		*/
		s32 GetValue()
		{
			return this->nodeindex;
		}

		/** IsInvalid
		*/
		bool IsInvalid() const
		{
			if(this->nodeindex < 0){
				return true;
			}

			return false;
		}

		/** operator ==
		*/
		bool operator ==(const RootSearch_NodeIndex& a_nodeindex) const noexcept
		{
			if(this->IsInvalid() == false){
				if(this->nodeindex == a_nodeindex.nodeindex){
					return true;
				}
			}

			return false;
		}
	};

	/** RootSearch_ConnectIndex
	*/
	class RootSearch_ConnectIndex
	{
		s32 connectindex;

	public:
		/** constructor
		*/
		RootSearch_ConnectIndex(s32 a_connectindex)
			:
			connectindex(a_connectindex)
		{
		}

		/** constructor
		*/
		RootSearch_ConnectIndex()
			:
			connectindex(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~RootSearch_ConnectIndex()
		{
		}

		/** GetValue
		*/
		s32 GetValue()
		{
			return this->connectindex;
		}

		/** IsInvalid
		*/
		bool IsInvalid() const
		{
			if(this->connectindex < 0){
				return true;
			}

			return false;
		}

		/** operator ==
		*/
		bool operator ==(const RootSearch_ConnectIndex& a_connectindex) const noexcept
		{
			if(this->IsInvalid() == false){
				if(this->connectindex == a_connectindex.connectindex){
					return true;
				}
			}

			return false;
		}

	};
}}
#endif

