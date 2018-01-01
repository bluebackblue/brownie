

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


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NCommandLine
*/
#if(BSYS_COMMANDLINE_ENABLE)
namespace NBsys{namespace NCommandLine
{
	/** SjisToWchar
	*/
	static STLWString SjisToWchar(const STLString& a_string)
	{
		#if defined(PLATFORM_VCWIN)
		{
			//コードページ。
			UINT t_codepage = CP_ACP;

			//処理性能とマッピングのフラグ。
			DWORD t_flags = 0;

			//入力文字。
			const char* t_char = a_string.c_str();
			//入力文字数。終端を含める。
			s32 t_char_len = static_cast<s32>(a_string.length() + 1);

			//必要配列サイズを受け取る（バイト数ではない）。終端文字含む。
			s32 t_wchar_use_len = ::MultiByteToWideChar(t_codepage,t_flags,t_char,t_char_len,nullptr,0);

			if(t_wchar_use_len > 0){
				//出力文字。終端を含む。
				s32 t_alloca_size = static_cast<s32>(t_wchar_use_len * sizeof(wchar));
				wchar* t_wchar = reinterpret_cast<wchar*>(MALLOCA(static_cast<std::size_t>(t_alloca_size)));

				if(t_wchar != nullptr){
					//変換。
					t_wchar_use_len = ::MultiByteToWideChar(t_codepage,t_flags,t_char,t_char_len,t_wchar,t_alloca_size / static_cast<s32>(sizeof(wchar)));
					if(static_cast<s32>(t_wchar_use_len * sizeof(wchar)) == t_alloca_size){
						STLWString t_string = t_wchar;
						FREEA(t_wchar);
						return t_string;
					}

					FREEA(t_wchar);
				}
			}
		}
		#endif

		return L"";
	}

	/** JsonItemに変換する。

		パラメータの名前の最初の一文字目はハイフン「-」にする。

		例
			-param1 value1 -param2 -param3 value3

			"-param1" = "value1"
			"-param2" = ""
			"-param3" = "value3"

	*/
	sharedptr<JsonItem> ConvertToJsonItem(s32 a_argc,char* a_argv[],bool a_is_sjis)
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

		STLVector<STLString>::Type t_list;
		for(u32 ii=0;ii<static_cast<u32>(a_argc);ii++){
			if(a_is_sjis){
				t_list.push_back(WcharToChar(SjisToWchar(a_argv[ii])));
			}else{
				t_list.push_back(STLString(a_argv[ii]));
			}
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
					if(t_list.at(static_cast<std::size_t>(t_offset))[0] == '-'){
						//パラメータ。

						t_offset_paramstart = t_offset;

						if(t_offset + 1 >= static_cast<s32>(t_list.size())){
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
					if(t_list.at(static_cast<std::size_t>(t_offset))[0] == '-'){
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
					t_param_string = t_list.at(static_cast<std::size_t>(t_offset_paramstart));
				}

				sharedptr<JsonItem> t_value_json(new JsonItem());
				if(t_offset_valuestart >= 0){
					STLString t_value_string = t_list.at(static_cast<std::size_t>(t_offset_valuestart));
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

			if(t_offset >= static_cast<s32>(t_list.size())){
				break;
			}
		}

		return t_jsonitem;
	}


}}
#endif

