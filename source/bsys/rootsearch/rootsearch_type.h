#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Œo˜H’T¸B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** NodeIndex
	*/
	class NodeIndex
	{
		s32 nodeindex;

	public:
		/** constructor
		*/
		NodeIndex(s32 a_nodeindex)
			:
			nodeindex(a_nodeindex)
		{
		}

		/** constructor
		*/
		NodeIndex()
			:
			nodeindex(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~NodeIndex()
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
		bool operator ==(const NodeIndex& a_nodeindex) const noexcept
		{
			if(this->IsInvalid() == false){
				if(this->nodeindex == a_nodeindex.nodeindex){
					return true;
				}
			}

			return false;
		}
	};

	/** ConnectIndex
	*/
	class ConnectIndex
	{
		s32 connectindex;

	public:
		/** constructor
		*/
		ConnectIndex(s32 a_connectindex)
			:
			connectindex(a_connectindex)
		{
		}

		/** constructor
		*/
		ConnectIndex()
			:
			connectindex(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~ConnectIndex()
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
		bool operator ==(const ConnectIndex& a_connectindex) const noexcept
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

