

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE\.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コマンドライン。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./commandline.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NCommandLine
*/
#if(BSYS_COMMANDLINE_ENABLE)
namespace NBsys{namespace NCommandLine
{
	/** JsonItemに変換する。

		パラメータの名前の最初の一文字目はハイフン「-」にする。

		例
			-param1 value1 -param2 -param3 value3

			"-param1" = "value1"
			"-param2" = ""
			"-param3" = "value3"

	*/
	sharedptr<JsonItem> ConvertToJsonItem(s32 a_argc,char* a_argv[])
	{
		sharedptr<JsonItem> t_jsonitem(new JsonItem());
		t_jsonitem->SetAssociativeArray();

		/** Step
		*/
		struct Step
		{
			enum Id
			{
				None = 0,
				SearchParam,
				SearchValue,
			};
		};

		s32 t_offset = 1;

		if(t_offset >= a_argc){
			return t_jsonitem;
		}

		Step::Id t_step = Step::SearchParam;

		s32 t_offset_paramstart = -1;
		s32 t_offset_valuestart = -1;
		bool  t_fix = false;

		while(1){
			bool t_tonext = true;

			switch(t_step){
			case Step::SearchParam:
				{
					if(a_argv[t_offset][0] == '-'){
						//パラメータ。

						t_offset_paramstart = t_offset;

						if(t_offset+1 >= a_argc){
							//終端。
							t_fix = true;
						}

						t_step = Step::SearchValue;
					}else{
						//不明。

						return sharedptr<JsonItem>();
					}
				}break;
			case Step::SearchValue:
				{
					if(a_argv[t_offset][0] == '-'){
						//次のパラメータを発見。

						t_fix = true;

						t_tonext = false;
					}else{
						//バリュー。

						t_offset_valuestart = t_offset;

						t_fix = true;
					}
				}break;
			case Step::None:
			default:
				{
					ASSERT(0);
				}break;
			}

			if(t_fix == true){
				STLString t_param_string = "";
				if(t_offset_paramstart >= 0){
					t_param_string = reinterpret_cast<char*>(a_argv[t_offset_paramstart]);
				}

				sharedptr<JsonItem> t_value_json(new JsonItem());
				if(t_offset_valuestart >= 0){
					STLString t_value_string = reinterpret_cast<char*>(a_argv[t_offset_valuestart]);
					t_value_json->SetStringData(t_value_string);
				}else{
					STLString t_value_string = "";
					t_value_json->SetStringData(t_value_string);
				}

				t_jsonitem->SetItem(t_param_string,t_value_json,true);

				t_offset_paramstart = -1;
				t_offset_valuestart = -1;
				t_fix = false;

				t_step = Step::SearchParam;
			}

			if(t_tonext == true){
				t_offset++;
			}

			if(t_offset >= a_argc){
				break;
			}
		}

		return t_jsonitem;
	}


}}
#endif

