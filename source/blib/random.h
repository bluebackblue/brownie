#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 乱数。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBlib
{
	/** 線形合同法。
	*/
	class Random_LinearCongruentialGenerators
	{
	private:

		/** seed。
		*/
		u32 seed;

		/** value。
		*/
		u32 value;

	public:

		/** constructor
		*/
		Random_LinearCongruentialGenerators()
			:
			seed(1),
			value(0)
		{
		}

		/** destructor
		*/
		nonvirtual ~Random_LinearCongruentialGenerators()
		{
		}

	public:

		/** シード設定。
		*/
		void SetSeed(u32 a_seed)
		{
			this->seed = a_seed;
			this->value = this->seed;
			this->GetRand();
		}

		/** シード取得。
		*/
		u32 GetSeed() const
		{
			return this->seed;
		}

		/** 乱数取得。
		*/
		u32 GetRand()
		{
			this->value = this->value * 214013 + 2531011;
			return (this->value>>16);
		}

		/** 乱数取得(0.0f <= value < 1.0f)。
		*/
		f32 GetFloat()
		{
			u32 t_rand = this->GetRand();
			return (t_rand & 0xFFFF) / 65536.0f;
		}

	};


	/** 非決定論的乱数。
	*/
	u32 GetRandFromDevice();


	/** 乱数。
	*/
	template <typename T=Random_LinearCongruentialGenerators> class RandomTemplate
	{
	private:

		/** impl
		*/
		T impl;

	public:

		/** constructor
		*/
		RandomTemplate()
			: impl()
		{
		}

		/** destructor
		*/
		nonvirtual ~RandomTemplate()
		{
		}

		/** シード設定に非決定論的乱数を使用する。
		*/
		void SetSeedFromDevice()
		{
			this->SetSeed(GetRandFromDevice());
		}

		/** シード設定。
		*/
		void SetSeed(u32 a_seed)
		{
			this->impl.SetSeed(a_seed);
		}

		/** シード取得。
		*/
		u32 GetSeed() const
		{
			return this->impl.GetSeed();
		}

		/** 乱数取得。
		*/
		u32 Get()
		{
			return this->impl.GetRand();
		}

		/** 乱数取得(0.0f <= value < 1.0f)。
		*/
		f32 GetFloat()
		{
			return this->impl.GetFloat();
		}

		/** 乱数取得(0 <= value < a_max)。
		*/
		u32 Get(u32 a_max)
		{
			ASSERT(a_max > 0);

			return this->impl.GetRand() % a_max;
		}

	};


}
#pragma warning(pop)

