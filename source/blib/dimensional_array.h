#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 多次元配列。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"


/** NBlib
*/
namespace NBlib
{
	/** dimensional_array_1
	*/
	template <typename T> class dimensional_array_1
	{
	private:

		/** size
		*/
		s32 size;

		/** list
		*/
		sharedptr<T> list;
		T* list_cache;

	public:

		/** constructor
		*/
		dimensional_array_1()
			:
			size(0),
			list(),
			list_cache(nullptr)
		{
		}

		/** constructor
		*/
		dimensional_array_1(s32 a_size)
			:
			size(a_size),
			list(new T[(a_size)],default_delete<T[]>()),
			list_cache(this->list.get())
		{
		}

		/** destructor
		*/
		nonvirtual ~dimensional_array_1()
		{
		}

	public:

		/** Create
		*/
		void Creaet(s32 a_size)
		{
			this->size = a_size;
			this->list.reset(new T[(a_size)],default_delete<T[]>());
			this->list_cache = this->list.get();
		}

		/** Delete
		*/
		void Delete()
		{
			this->size = 0;
			this->list.reset();
			this->list_cache = nullptr;
		}

		/** Size
		*/
		s32 Size() const
		{
			return this->size;
		}

		/** Get
		*/
		const T& Get(s32 a_index) const
		{
			ASSERT((0<=a_index)&&(a_index<this->size));
			return this->list_cache[a_index];
		}

		/** Set
		*/
		void Set(s32 a_index,const T& a_value)
		{
			ASSERT((0<=a_index)&&(a_index<this->size));
			this->list_cache[a_index] = a_value;
		}

		/** Add
		*/
		void Add(s32 a_index,const T& a_value)
		{
			ASSERT((0<=a_index)&&(a_index<this->size));
			this->list_cache[a_index] += a_value;
		}

		/** SetAll
		*/
		void SetAll(const T& a_value)
		{
			for(s32 ii=0;ii<(this->size);ii++){
				this->list_cache[ii] = a_value;
			}
		}

	};


	/** dimensional_array_2
	*/
	template <typename T> class dimensional_array_2
	{
	private:

		/** width
		*/
		s32 width;

		/** height
		*/
		s32 height;

		/** list
		*/
		sharedptr<T> list;

		/** list_cache
		*/
		T* list_cache;

	public:

		/** constructor
		*/
		dimensional_array_2()
			:
			width(0),
			height(0),
			list(),
			list_cache(nullptr)
		{
		}

		/** constructor
		*/
		dimensional_array_2(s32 a_width,s32 a_height)
			:
			width(a_width),
			height(a_height),
			list(new T[(a_width * a_height)],default_delete<T[]>()),
			list_cache(this->list.get())
		{
		}

		/** destructor
		*/
		nonvirtual ~dimensional_array_2()
		{
		}

	public:

		/** Create
		*/
		void Creaet(s32 a_width,s32 a_height)
		{
			this->width = a_width;
			this->height = a_height;
			this->list.reset(new T[(a_width * a_height)],default_delete<T[]>());
			this->list_cache = this->list.get();
		}

		/** Delete
		*/
		void Delete()
		{
			this->width = 0;
			this->height = 0;
			this->list.reset();
			this->list_cache = nullptr;
		}

		/** Width
		*/
		s32 Width() const
		{
			return this->width;
		}

		/** Height
		*/
		s32 Height() const
		{
			return this->height;
		}

		/** Get
		*/
		const T& Get(s32 a_x,s32 a_y) const
		{
			ASSERT((0<=a_x)&&(a_x<this->width));
			ASSERT((0<=a_y)&&(a_y<this->height));
			return this->list_cache[a_y * this->width + a_x];
		}

		/** Set
		*/
		void Set(s32 a_x,s32 a_y,const T& a_value)
		{
			ASSERT((0<=a_x)&&(a_x<this->width));
			ASSERT((0<=a_y)&&(a_y<this->height));
			this->list_cache[a_y * this->width + a_x] = a_value;
		}

		/** Add
		*/
		void Add(s32 a_x,s32 a_y,const T& a_value)
		{
			ASSERT((0<=a_x)&&(a_x<this->width));
			ASSERT((0<=a_y)&&(a_y<this->height));
			this->list_cache[a_y * this->width + a_x] += a_value;
		}

		/** SetAll
		*/
		void SetAll(const T& a_value)
		{
			for(s32 ii = 0;ii < (this->width * this->height);ii++){
				this->list_cache[ii] = a_value;
			}
		}

	};


}

