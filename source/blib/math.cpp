

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 算術。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./math.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4514)
#include <cmath>
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib

4711 : 自動インライン展開を選択しました。

*/
#pragma warning(push)
#pragma warning(disable:4514 4711)
namespace NBlib
{
	/** NMath
	*/
	namespace NMath
	{
		/** sincosテーブル。
		*/
		static SinCosSample s_sin_cos_table[BLIB_MATH_SINCOSFAST_TABLESIZE + 1] = {0};


		/** GetSinCosTable
		*/
		SinCosSampleList& GetSinCosTable()
		{
			return s_sin_cos_table;
		}


		/** 初期化。
		*/
		void Initialize()
		{
			for(s32 ii=0;ii<(COUNTOF(s_sin_cos_table));ii++){
				f32 t_rad = (2.0f * NMath::pi() * ii) / (COUNTOF(s_sin_cos_table) - 1);
				s_sin_cos_table[ii].sin_val = NMath::sin_f(t_rad);
				s_sin_cos_table[ii].cos_val = NMath::cos_f(t_rad);
			}
		}

	}


}
#pragma warning(pop)

