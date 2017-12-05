#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �����B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{

	/** ���`�����@�B
	*/
	class Random_LinearCongruentialGenerators
	{
	private:
		/** seed�B
		*/
		u32 seed;

		/** value�B
		*/
		u32 value;

	public:
		/** constructor�B
		*/
		Random_LinearCongruentialGenerators()
			:
			seed(1),
			value(0)
		{
		}

		/** destructor�B
		*/
		nonvirtual ~Random_LinearCongruentialGenerators()
		{
		}

	public:
		/** �V�[�h�ݒ�B
		*/
		void SetSeed(u32 a_seed)
		{
			this->seed = a_seed;
			this->value = this->seed;
			this->GetRand();
		}

		/** �V�[�h�擾�B
		*/
		u32 GetSeed() const
		{
			return this->seed;
		}

		/** �����擾�B
		*/
		u32 GetRand()
		{
			this->value = this->value * 214013 + 2531011;
			return (this->value>>16);
		}

		/** �����擾(0.0f <= value < 1.0f)�B
		*/
		f32 GetFloat()
		{
			u32 t_rand = this->GetRand();
			return (t_rand & 0xFFFF) / 65536.0f;
		}
	};

	/** �񌈒�_�I�����B
	*/
	u32 GetRandFromDevice();

	/** �����B
	*/
	template <typename T=Random_LinearCongruentialGenerators> class RandomTemplate
	{
	private:
		T impl;

	public:
		/** constructor�B
		*/
		RandomTemplate()
			: impl()
		{
		}

		/** destructor�B
		*/
		nonvirtual ~RandomTemplate()
		{
		}

		/** �V�[�h�ݒ�ɔ񌈒�_�I�������g�p����B
		*/
		void SetSeedFromDevice()
		{
			this->SetSeed(GetRandFromDevice());
		}

		/** �V�[�h�ݒ�B
		*/
		void SetSeed(u32 a_seed)
		{
			this->impl.SetSeed(a_seed);
		}

		/** �V�[�h�擾�B
		*/
		u32 GetSeed() const
		{
			return this->impl.GetSeed();
		}

		/** �����擾�B
		*/
		u32 Get()
		{
			return this->impl.GetRand();
		}

		/** �����擾(0.0f <= value < 1.0f)�B
		*/
		f32 GetFloat()
		{
			return this->impl.GetFloat();
		}

		/** �����擾(0 <= value < a_max)�B
		*/
		u32 Get(u32 a_max)
		{
			ASSERT(a_max > 0);

			return this->impl.GetRand() % a_max;
		}
	};

}

