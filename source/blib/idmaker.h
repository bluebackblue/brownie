#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＩＤ発行。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./stlvector.h"


/** NBlib
*/
namespace NBlib
{
	/** IDMaker
	*/
	class IDMaker
	{
	private:
		/** free_list
		*/
		STLVector< s32 >::Type free_list;

		/** size
		*/
		s32 size;

		/** 自動追加。
		*/
		bool autocreate;

	public:
		/** constructor.
		*/
		IDMaker()
			:
			free_list(),
			size(0),
			autocreate(true)
		{
		}

		/** constructor.
		*/
		IDMaker(s32 a_max,bool a_autocreate)
			:
			free_list(),
			size(0),
			autocreate(a_autocreate)
		{
			this->Create(a_max);
		}

		/** destructor
		*/
		nonvirtual ~IDMaker()
		{
		}

	public:
		/** ID追加。
		*/
		void Create(s32 a_max)
		{
			for(s32 ii=0;ii<a_max;ii++){
				this->free_list.push_back(this->size);
				this->size++;
			}
		}

		/** ID発行。
		*/
		s32 MakeID()
		{
			if(this->free_list.size() <= 0){
				if(this->autocreate == true){
					this->Create(16);
				}else{
					return -1;
				}
			}

			s32 t_id = this->free_list[this->free_list.size() - 1];

			this->free_list.pop_back();

			return t_id;
		}

		/** ID破棄。
		*/
		void ReleaseID(s32 a_id)
		{
			this->free_list.push_back(a_id);
		}

		/** Reset
		*/
		void Reset()
		{
			this->free_list.clear();
			this->size = 0;
		}

	};
}

