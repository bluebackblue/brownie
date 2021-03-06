﻿

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＪＳＯＮアイテム。
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
#include "./stlallocator.h"
#include "./jsonitem.h"
#include "./debugassert.h"
#include "./autolock.h"
#include "./blib_bootinitialize.h"


/** include
*/
#if(BLIB_STDREGEX_ENABLE)

	#pragma warning(push)
	#pragma warning(disable:4710 4514 4987 4820 4625 4626 4365 5026 5027 4061 4623 4571 4774)
	#include <regex>
	#pragma warning(pop)

#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib
*/
#if(BLIB_JSONITEM_ENABLE)
namespace NBlib
{
	/** [static]確保。
	*/
	void* JsonItem::Alloc(size_t a_size)
	{
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		if(a_size <= GlobalFixedAllocator_Type::Config::BlockSize){
			AutoLock t_autolock(GlobalFixedAllocator_LockObject());
			void* t_pointer = GlobalFixedAllocator_Get().Alloc();
			if(t_pointer != nullptr){
				return t_pointer;
			}
		}
		#endif

		{
			void* t_pointer = new u8[a_size];
			if(t_pointer != nullptr){
				return t_pointer;
			}
		}

		ASSERT(0);
		return nullptr;
	}


	/** [static]解放。
	*/
	void JsonItem::Free(void* a_pointer)
	{
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		{
			AutoLock t_autolock(GlobalFixedAllocator_LockObject());
			bool t_ret = GlobalFixedAllocator_Get().Free(a_pointer);
			if(t_ret == true){
				return;
			}
		}
		#endif

		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}


	/** NImpl
	*/
	namespace NImpl
	{
		/** 最初の一文字からタイプを推測。
		*/
		static JsonItem::ValueType::Id GetValueTypeFromChar(char a_char)
		{
			switch(a_char){
			case '"':
			case '\'':
				{
					return JsonItem::ValueType::StringData;
				}break;
			case '{':
				{
					return JsonItem::ValueType::AssociativeArray;
				}break;
			case '[':
				{
					return JsonItem::ValueType::IndexArray;
				}break;
			case '<':
				{
					return JsonItem::ValueType::BinaryData;
				}break;
			case 't':
			case 'T':
				{
					return JsonItem::ValueType::Calc_BoolDataTrue;
				}break;
			case 'f':
			case 'F':
				{
					return JsonItem::ValueType::Calc_BoolDataFalse;
				}break;
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				{
					return JsonItem::ValueType::Calc_UnknownNumber;
				}break;
			default:
				{
					//不明な開始文字。
					ASSERT(0);

					return JsonItem::ValueType::None;
				}break;
			}
		}


		/** 整数チェック。
		*/
		static bool IsInteger(const STLString& a_string)
		{
			#if(BLIB_STDREGEX_ENABLE)
			{
				#if defined(PLATFORM_GNUCWIN)
				return std::regex_match(a_string.c_str(),std::regex("^[-]?[0-9]+"));
				#else
				return std::regex_match(a_string,std::regex("^[-]?[0-9]+"));
				#endif
			}
			#else
			{
				auto t_start = a_string.cbegin();
				auto t_end = a_string.cend();
				auto t_it = t_start;

				if(t_it != t_end){
					switch((*t_it)){
					case '-':
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						{
						}break;
					default:
						{
							return false;
						}break;
					}
			
					t_it++;
				}

				for(;t_it!=t_end;t_it++){
					switch((*t_it)){
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						{
						}break;
					default:
						{
							return false;
						}break;
					}
				}

				return true;
			}
			#endif
		}


		/** エスケープシーケンス文字を「￥＋文字」に変換。
		*/
		static const char* CheckEscapeSequence(char a_char)
		{
			switch(a_char){
			case '\\':
				{
					return "\\\\";
				}break;
			case '\"':
				{
					return "\\\"";
				}break;
			case '\'':
				{
					return "\\\'";
				}break;
			case '\n':
				{
					return "\\n";
				}break;
			default:
				{
				}break;
			}

			//通常文字。
			return nullptr;
		}


		/** 「￥＋文字」をシーケンス文字に変換。
		*/
		#pragma warning(push)
		#pragma warning(disable:4702)
		static const char* ToSequenceString(const STLString& a_string,u32 a_index)
		{
			if(a_index < a_string.length()){
				if(a_string[a_index] == '\\'){
					if((a_index + 1) < a_string.length()){
						switch(a_string[a_index+1]){
						case '\"':
							{
								//ダブルクォーテーション。
								return "\"";
							}break;
						case '\'':
							{
								//シングルクォーテーション。
								return "\'";
							}break;
						case '\\':
							{
								//￥。
								return "\\";
							}break;
						case 'n':
							{
								//改行。
								return "\n";
							}break;
						case '/':
							{
								//スラッシュ。
								return "/";
							}break;
						default:
							{
								//知らないエスケープシーケンス。
								ASSERT(0);

								return nullptr;
							}break;
						}
					}else{
						//範囲外。
						ASSERT(0);

						return nullptr;
					}
				}else{
					//通常文字。
					ASSERT(0);

					return nullptr;
				}
			}else{
				//範囲外。
				ASSERT(0);

				return nullptr;
			}

			//不明。
			ASSERT(0);

			return nullptr;
		}
		#pragma warning(pop)


		/** 文字のサイズ。
		*/
		static u32 GetMojiSize(const STLString& a_string,u32 a_index,bool a_escape)
		{
			if(a_index < a_string.length()){
				if(a_string[a_index] == '\\'){
					if(a_escape == true){
						if(a_string.length() >= (2 + a_index)){
							//エスケープシーケンスの後ろは１バイト文字。
							return 2;
						}else{
							//文字数が足りない。
							ASSERT(0);

							return 0;
						}
					}else{
						//エスケープシーケンスとして処理しない。
						return 1;
					}
				}else{
					//エスケープシーケンス以外。

					u8 t_char = static_cast<u8>(a_string[a_index]);

					if((t_char & 0x80) == 0){
						//t_char & 10000000 == 00000000
						return 1;
					}else if((t_char & 0xE0) == 0xC0){
						//t_char & 11100000 == 11000000
						return 2;
					}else if((t_char & 0xF0) == 0xE0){
						//t_char & 11110000 == 11100000
						return 3;
					}else if((t_char & 0xF8) == 0xF0){
						//t_char & 11111000 == 11110000
						return 4;
					}else if((t_char & 0xFC) == 0xF8){
						//t_char & 11111100 == 11111000
						return 5;
					}else if((t_char & 0xFE) == 0xFC){
						//t_char & 11111110 == 11111100
						return 6;
					}else{
						return 1;
					}
				}
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** 文字列JSONの長さ。
		*/
		static u32 GetLength_StringData(const STLString& a_string,u32 a_index)
		{
			u32 t_index = static_cast<u32>(a_index);

			if(t_index < a_string.length()){
				if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
					t_index++;
					while(t_index < a_string.length()){
						if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//終端。
							return t_index - a_index + 1;
						}else{
							//次の文字へ。
							u32 t_add = NImpl::GetMojiSize(a_string,t_index,true);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//予想外の文字コード。
								ASSERT(0);

								return 0;
							}
						}
					}
				
					//予想外の終端。
					ASSERT(0);

					return 0;
				}else{
					//文字列以外。
					ASSERT(0);

					return 0;
				}
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** 数字JSONの長さ。
		*/
		static u32 GetLength_Number(const STLString& a_string,u32 a_index)
		{
			if(a_index < a_string.length()){
				u32 t_index = a_index;
				while(a_index < a_string.length()){
					switch(a_string[t_index]){
					case '}':
					case ']':
					case ',':
						{
							//終端。
							return t_index - a_index;
						}break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '.':
					case '+':
					case '-':
						{
							//数値。
							t_index++;
						}break;
					default:
						{
							//不明。
							ASSERT(0);

							return 0;
						}break;	
					}
				}
			
				//終端。
				return t_index - a_index;
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** 連想リストJSONの長さ。
		*/
		static u32 GetLength_AssociateArray(const STLString& a_string,u32 a_index)
		{
			if(a_index < a_string.length()){
				if(a_string[a_index] == '{'){
					s32 t_nest = 1;
					u32 t_index = a_index + 1;
				
					while(t_index < a_string.length()){
						if(a_string[t_index] == '}'){
							if(t_nest <= 1){
								//終端。
								return t_index - a_index + 1;
							}else{
								//ネスト。
								t_nest--;
								t_index++;
							}
						}else if(a_string[t_index] == '{'){
							//ネスト。
							t_nest++;
							t_index++;
						}else if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//文字列。
							u32 t_add = GetLength_StringData(a_string,t_index);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//予想外の文字コード。
								ASSERT(0);

								return 0;
							}
						}else{
							//次へ。
							t_index++;
						}
					}
				
					//終端がない。
					ASSERT(0);

					return 0;
				}else{
					//連想配列以外。
					ASSERT(0);

					return 0;
				}
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** インデックスリストJSONの長さ。
		*/
		static u32 GetLength_IndexArray(const STLString& a_string,u32 a_index)
		{
			if(a_index < a_string.length()){
				if(a_string[a_index] == '['){
					s32 t_nest = 1;
					u32 t_index = a_index + 1;
				
					while(t_index < a_string.length()){
						if(a_string[t_index] == ']'){
							if(t_nest <= 1){
								//終端。
								return t_index - a_index + 1;
							}else{
								//ネスト。
								t_nest--;
								t_index++;
							}
						}else if(a_string[t_index] == '['){
							//ネスト。
							t_nest++;
							t_index++;
						}else if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//文字列。
							u32 t_add = GetLength_StringData(a_string,t_index);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//予想外の文字コード。
								ASSERT(0);

								return 0;
							}
						}else{
							//次へ。
							t_index++;
						}
					}
				
					//終端がない。
					ASSERT(0);

					return 0;	
				}else{
					//配列以外。
					ASSERT(0);

					return 0;
				}
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** TRUEJSONの長さ。
		*/
		static u32 GetLength_BoolTrue(const STLString& a_string,u32 a_index)
		{
			const char t_true_1[4] = {'T','R','U','E'};
			const char t_true_2[4] = {'t','r','u','e'};

			for(s32 ii=0;ii<COUNTOF(t_true_1);ii++){
				u32 t_index = static_cast<u32>(a_index + ii);

				if(t_index < a_string.length()){
					if((a_string[t_index] == t_true_1[ii])||(a_string[t_index] == t_true_2[ii])){
					}else{
						//TRUE以外。
						ASSERT(0);
						
						return 0;
					}
				}else{
					//TRUE以外。
					ASSERT(0);

					return 0;
				}
			}

			{
				u32 t_index = static_cast<u32>(a_index + COUNTOF(t_true_1));

				if(t_index < a_string.length()){
					if((a_string[t_index] == '}')||(a_string[t_index] == ']')||(a_string[t_index] == ',')){
						//終端。
						return COUNTOF(t_true_1);
					}else{
						//TRUE以外。
						ASSERT(0);

						return 0;					
					}
				}else{
					//TRUE以外。
					ASSERT(0);

					return 0;
				}
			}
		}


		/** FALSEJSONの長さ。
		*/
		static u32 GetLength_BoolFalse(const STLString& a_string,u32 a_index)
		{
			const char t_true_1[5] = {'F','A','L','S','E'};
			const char t_true_2[5] = {'f','a','l','s','e'};

			for(s32 ii=0;ii<COUNTOF(t_true_1);ii++){
				u32 t_index = a_index + ii;

				if(t_index < a_string.length()){
					if((a_string[t_index] == t_true_1[ii])||(a_string[t_index] == t_true_2[ii])){
					}else{
						//FALSE以外。
						ASSERT(0);
						
						return 0;
					}
				}else{
					//FALSE以外。
					ASSERT(0);

					return 0;
				}
			}

			{
				u32 t_index = static_cast<u32>(a_index + COUNTOF(t_true_1));

				if(t_index < a_string.length()){
					if((a_string[t_index] == '}')||(a_string[t_index] == ']')||(a_string[t_index] == ',')){
						//終端。
						return COUNTOF(t_true_1);
					}else{
						//FALSE以外。
						ASSERT(0);

						return 0;					
					}
				}else{
					//FALSE以外。
					ASSERT(0);

					return 0;
				}
			}
		}


		/** BinaryDataの長さ。
		*/
		static u32 GetLength_BinaryData(const STLString& a_string,u32 a_index)
		{
			if(a_index < a_string.length()){
				if(a_string[a_index] == '<'){
					u32 t_index = a_index + 1;
					while(t_index < a_string.length()){
						switch(a_string[t_index]){
						case '>':
							{
								//終端。
								return t_index - a_index + 1;
							}break;
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'a':
						case 'A':
						case 'b':
						case 'B':
						case 'c':
						case 'C':
						case 'd':
						case 'D':
						case 'e':
						case 'E':
						case 'f':
						case 'F':
							{
								//次へ。
								t_index++;
							}break;
						default:
							{
								//不明。
								ASSERT(0);

								return 0;
							}break;
						}
					}
				
					//終端がない。
					ASSERT(0);

					return 0;	
				}else{
					//バイナリデータ以外。
					ASSERT(0);

					return 0;
				}
			}else{
				//範囲外。
				ASSERT(0);

				return 0;
			}
		}


		/** JSON文字からインデックスリストの作成[*,*,*]。
		*/
		static sharedptr<STLVector<sharedptr<JsonItem>>::Type> CreateIndexArrayFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLVector<sharedptr<JsonItem>>::Type> t_indexlist(new STLVector<sharedptr<JsonItem>>::Type());
		
			u32 t_index = 0;
			while(t_index < a_jsonstring.length()){
				if(a_jsonstring[t_index] == ']'){
					//終端。
					ASSERT(t_index + 1 == a_jsonstring.length());

					return t_indexlist;
				}else if(a_jsonstring[t_index] == ','){
					//次の項目あり。
					t_index++;
				}else if(a_jsonstring[t_index] == '['){
					if(t_index == 0){
						//開始。
						t_index++;
						continue;
					}else if(t_index == 1){
						//インデックスリストの中にインデックスリスト。
					}else{
						//不明。
						ASSERT(0);

						t_indexlist.reset(new decltype(t_indexlist)::element_type());
						return t_indexlist;
					}
				}
		
				//値。
				u32 t_value_size = 0;
				switch(GetValueTypeFromChar(a_jsonstring[t_index])){
				case JsonItem::ValueType::StringData:
					{
						t_value_size = GetLength_StringData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_UnknownNumber:
				case JsonItem::ValueType::IntegerNumber:
				case JsonItem::ValueType::FloatNumber:
					{
						t_value_size = GetLength_Number(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::AssociativeArray:
					{
						t_value_size = GetLength_AssociateArray(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::IndexArray:
					{
						t_value_size = GetLength_IndexArray(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_BoolDataTrue:
					{
						t_value_size = GetLength_BoolTrue(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_BoolDataFalse:
					{
						t_value_size = GetLength_BoolFalse(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BinaryData:
					{
						t_value_size = GetLength_BinaryData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::None:
				case JsonItem::ValueType::BoolData:
				default:
					{
						//不明。
						ASSERT(0);

						t_indexlist.reset(new decltype(t_indexlist)::element_type());
						return t_indexlist;
					}break;
				}
			
				//リストの最後に追加。
				if(t_value_size > 0){

					#if defined(new)
					#undef new
					#endif

					sharedptr<JsonItem> t_additem(new JsonItem());

					#if defined(custom_new)
					#define new custom_new
					#endif

					{
						t_additem->SetJsonString(a_jsonstring.substr(t_index,t_value_size));
					}

					t_indexlist->push_back(t_additem);

					t_index += t_value_size;
				}else{
					ASSERT(0);

					t_indexlist.reset(new decltype(t_indexlist)::element_type());
					return t_indexlist;
				}
			}
		
			//範囲外。
			ASSERT(0);

			t_indexlist.reset(new decltype(t_indexlist)::element_type());
			return t_indexlist;
		}


		/** JSON文字から連想配列の作成。
		*/
		static sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type> CreateAssociativeArrayFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type> t_associativelist(new STLMap<STLString,sharedptr<JsonItem>>::Type);
		
			u32 t_index = 0;
			while(t_index < a_jsonstring.length()){
				if(a_jsonstring[t_index] == '}'){
					//終端。
					ASSERT((t_index + 1) == a_jsonstring.length());

					return t_associativelist;
				}else if(a_jsonstring[t_index] == ','){
					//次の項目あり。
					t_index++;
				}else if(a_jsonstring[t_index] == '{'){
					if(t_index == 0){
						//開始。
						t_index++;
						continue;
					}else{
						//不明。
						ASSERT(0);

						t_associativelist.reset(new decltype(t_associativelist)::element_type());
						return t_associativelist;
					}
				}
			
				//名前。
				STLString t_name_string;
				if((a_jsonstring[t_index] == '"')||(a_jsonstring[t_index] == '\'')){
					u32 t_name_size = GetLength_StringData(a_jsonstring,t_index);
					if(t_name_size >= 2){
						t_name_string = a_jsonstring.substr(t_index + 1,t_name_size - 2);
						t_index += t_name_size;
					}else{
						//不明。
						ASSERT(0);

						t_associativelist.reset(new decltype(t_associativelist)::element_type());
						return t_associativelist;
					}
				}else{
					//不明。
					ASSERT(0);

					t_associativelist.reset(new decltype(t_associativelist)::element_type());
					return t_associativelist;
				}
			
				//「:」。
				if(a_jsonstring[t_index] == ':'){
					t_index++;
				}else{
					//不明。
					ASSERT(0);

					t_associativelist.reset(new decltype(t_associativelist)::element_type());
					return t_associativelist;
				}
			
				//値。
				u32 t_value_size = 0;
				switch(GetValueTypeFromChar(a_jsonstring[t_index])){
				case JsonItem::ValueType::StringData:
					{
						t_value_size = GetLength_StringData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_UnknownNumber:
				case JsonItem::ValueType::IntegerNumber:
				case JsonItem::ValueType::FloatNumber:
					{
						t_value_size = GetLength_Number(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::AssociativeArray:
					{
						t_value_size = GetLength_AssociateArray(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::IndexArray:
					{
						t_value_size = GetLength_IndexArray(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_BoolDataTrue:
					{
						t_value_size = GetLength_BoolTrue(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::Calc_BoolDataFalse:
					{
						t_value_size = GetLength_BoolFalse(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BinaryData:
					{
						t_value_size = GetLength_BinaryData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BoolData:
				case JsonItem::ValueType::None:
				default:
					{
						//不明。
						ASSERT(0);

						t_associativelist.reset(new decltype(t_associativelist)::element_type());
						return t_associativelist;
					}break;
				}
			
				//リストに追加。
				if(t_value_size > 0){

					#if defined(new)
					#undef new
					#endif

					sharedptr<JsonItem> t_additem(new JsonItem());

					#if defined(custom_new)
					#define new custom_new
					#endif

					{
						t_additem->SetJsonString(a_jsonstring.substr(t_index,t_value_size));
					}

					t_associativelist->insert(std::make_pair(t_name_string,t_additem));

					t_index += t_value_size;
				}else{
					ASSERT(0);

					t_associativelist.reset(new decltype(t_associativelist)::element_type());
					return t_associativelist;
				}
			}
		
			//範囲外。
			ASSERT(0);

			t_associativelist.reset(new decltype(t_associativelist)::element_type());
			return t_associativelist;
		}


		/** JSON文字からバイナリデータの作成。
		*/
		static sharedptr<STLVector<u8>::Type> CreateBinaryDataFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLVector<u8>::Type> t_binarydata(new STLVector<u8>::Type());

			t_binarydata->reserve(a_jsonstring.length() / 2);

			u32 t_index = 0;
			while(t_index < a_jsonstring.length()){
				if(a_jsonstring[t_index] == '>'){
					//終端。
					ASSERT((t_index + 1) == a_jsonstring.length());

					return t_binarydata;
				}else if(a_jsonstring[t_index] == '<'){
					if(t_index == 0){
						//開始。
						t_index++;
						continue;
					}else{
						//不明。
						ASSERT(0);

						t_binarydata.reset(new decltype(t_binarydata)::element_type());
						return t_binarydata;
					}
				}else{

					u8 t_binary = 0x00;

					switch(a_jsonstring[t_index]){
					case '0':t_binary = 0x00;break;
					case '1':t_binary = 0x10;break;
					case '2':t_binary = 0x20;break;
					case '3':t_binary = 0x30;break;
					case '4':t_binary = 0x40;break;
					case '5':t_binary = 0x50;break;
					case '6':t_binary = 0x60;break;
					case '7':t_binary = 0x70;break;
					case '8':t_binary = 0x80;break;
					case '9':t_binary = 0x90;break;
					case 'a':t_binary = 0xA0;break;
					case 'A':t_binary = 0xA0;break;
					case 'b':t_binary = 0xB0;break;
					case 'B':t_binary = 0xB0;break;
					case 'c':t_binary = 0xC0;break;
					case 'C':t_binary = 0xC0;break;
					case 'd':t_binary = 0xD0;break;
					case 'D':t_binary = 0xD0;break;
					case 'e':t_binary = 0xE0;break;
					case 'E':t_binary = 0xE0;break;
					case 'f':t_binary = 0xF0;break;
					case 'F':t_binary = 0xF0;break;
					default:
						{
							//不明。
							ASSERT(0);

							t_binarydata.reset(new decltype(t_binarydata)::element_type());
							return t_binarydata;
						}break;
					}

					t_index++;

					if(t_index < a_jsonstring.length()){
						switch(a_jsonstring[t_index]){
						case '0':t_binary |= 0x00;break;
						case '1':t_binary |= 0x01;break;
						case '2':t_binary |= 0x02;break;
						case '3':t_binary |= 0x03;break;
						case '4':t_binary |= 0x04;break;
						case '5':t_binary |= 0x05;break;
						case '6':t_binary |= 0x06;break;
						case '7':t_binary |= 0x07;break;
						case '8':t_binary |= 0x08;break;
						case '9':t_binary |= 0x09;break;
						case 'a':t_binary |= 0x0A;break;
						case 'A':t_binary |= 0x0A;break;
						case 'b':t_binary |= 0x0B;break;
						case 'B':t_binary |= 0x0B;break;
						case 'c':t_binary |= 0x0C;break;
						case 'C':t_binary |= 0x0C;break;
						case 'd':t_binary |= 0x0D;break;
						case 'D':t_binary |= 0x0D;break;
						case 'e':t_binary |= 0x0E;break;
						case 'E':t_binary |= 0x0E;break;
						case 'f':t_binary |= 0x0F;break;
						case 'F':t_binary |= 0x0F;break;
						default:
							{
								//不明。
								ASSERT(0);

								t_binarydata.reset(new decltype(t_binarydata)::element_type());
								return t_binarydata;
							}break;
						}

						t_index++;

						t_binarydata->push_back(t_binary);
					}else{
						//不明。
						ASSERT(0);

						t_binarydata.reset(new decltype(t_binarydata)::element_type());
						return t_binarydata;
					}
				}
			}

			//範囲外。
			ASSERT(0);

			t_binarydata.reset(new decltype(t_binarydata)::element_type());
			return t_binarydata;
		}
	}


	/** constructor
	*/
	JsonItem::JsonItem()
		:
		valuetype(ValueType::None)
	{
		this->value.Reset();
	}


	/** constructor
	*/
	JsonItem::JsonItem(const STLString& a_jsonstring)
	{
		this->SetJsonString(a_jsonstring);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_StringData& a_value)
	{
		this->SetStringData(a_value.value);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_AssociativeArray& /*a_value*/)
	{
		this->SetAssociativeArray();
	}

		
	/** constructor
	*/
	JsonItem::JsonItem(const Value_IndexArray& /*a_value*/)
	{
		this->SetIndexArray();
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_Integer& a_value)
	{
		this->SetInteger(a_value.value);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_UnsignedInteger& a_value)
	{
		this->SetInteger(a_value.value);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_Float& a_value)
	{
		this->SetFloat(a_value.value);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_BoolData& a_value)
	{
		this->SetBoolData(a_value.value);
	}


	/** constructor
	*/
	JsonItem::JsonItem(const Value_BinaryData& a_value)
	{
		this->SetBinaryData(a_value.value);
	}


	/** ディープコピー。
	*/
	sharedptr<JsonItem> JsonItem::DeepCopy() const
	{
		#if defined(new)
		#undef new
		#endif

		sharedptr<JsonItem> t_new_jsonitem(new JsonItem(this->ConvertJsonString()));

		#if defined(custom_new)
		#define new custom_new
		#endif

		return t_new_jsonitem;
	}


	/** ＪＳＯＮ文字列をセット。
	*/
	void JsonItem::SetJsonString(const STLString& a_jsonstring)
	{
		if(a_jsonstring.length() > 0){
			ValueType::Id t_valuetype = NImpl::GetValueTypeFromChar(a_jsonstring[0]);
			switch(t_valuetype){
			case ValueType::StringData:
			case ValueType::AssociativeArray:
			case ValueType::IndexArray:
			case ValueType::BinaryData:
			case ValueType::IntegerNumber:
			case ValueType::FloatNumber:
				{
					this->jsonstring.reset(new STLString(a_jsonstring));
					this->valuetype = t_valuetype;
					this->value.Reset();
					return;
				}break;
			case ValueType::Calc_UnknownNumber:
				{
					if(NImpl::IsInteger(a_jsonstring)){
						this->jsonstring.reset(new STLString(a_jsonstring));
						this->valuetype = ValueType::IntegerNumber;
						this->value.Reset();
						return;
					}else{
						this->jsonstring.reset(new STLString(a_jsonstring));
						this->valuetype = ValueType::FloatNumber;
						this->value.Reset();
						return;
					}
				}break;
			case ValueType::Calc_BoolDataTrue:
				{
					//値で設定。

					this->jsonstring.reset();
					this->valuetype = ValueType::BoolData;
					this->value.bool_data = true;
					return;
				}break;
			case ValueType::Calc_BoolDataFalse:
				{
					//値で設定。

					this->jsonstring.reset();
					this->valuetype = ValueType::BoolData;
					this->value.bool_data = false;
					return;
				}break;
			case ValueType::None:
			case ValueType::BoolData:
			default:
				{
					ASSERT(0);

					this->jsonstring.reset();
					this->valuetype = ValueType::None;
					this->value.Reset();
					return;
				}break;
			}
		}

		ASSERT(0);

		this->jsonstring.reset();
		this->valuetype = ValueType::None;
		this->value.Reset();
	}


	/** 値化。
	*/
	void JsonItem::JsonStringToValue() const
	{
		sharedptr<STLString> t_jsonstring_temp = this->jsonstring;
		this->jsonstring.reset();

		this->value.Reset();

		if(t_jsonstring_temp != nullptr){
			switch(this->valuetype){
			case ValueType::StringData:
				{
					u32 t_index = 1;
					u32 t_max = static_cast<u32>(t_jsonstring_temp->length() - 1);

					this->value.string_data.reset(new STLString());
					this->value.string_data->reserve(16 + t_max);
				
					while(t_index < t_max){
						u32 t_add = NImpl::GetMojiSize((*t_jsonstring_temp),t_index,true);
						if(t_add == 2){
							if((*t_jsonstring_temp)[t_index] == '\\'){
								//エスケープシーケンス文字をシーケンス文字に変換。
								const char* t_add_string = NImpl::ToSequenceString((*t_jsonstring_temp),t_index);
								if(t_add_string != nullptr){
									//変換後文字列を追加。
									this->value.string_data->append(t_add_string);
								}else{
									//不明。
									ASSERT(0);

									*(this->value.string_data) = "";
									return;
								}
							}else{
								//通常文字（２文字）を追加。
								this->value.string_data->append(t_jsonstring_temp->substr(t_index,t_add));
							}
						}else if(t_add > 0){
							//通常文字（複数文字）を追加。
							this->value.string_data->append(t_jsonstring_temp->substr(t_index,t_add));
						}else{
							//不明なエンコード。
							ASSERT(0);

							*(this->value.string_data) = "";
							return;
						}

						t_index += t_add;
					}

					if(t_index != t_max){
						//不明なエンコード。
						ASSERT(0);

						*(this->value.string_data) = "";
						return;
					}

					return;
				}break;
			case ValueType::IntegerNumber:
				{
					this->value.integer_number = std::atoi(t_jsonstring_temp->c_str());
					return;
				}break;
			case ValueType::FloatNumber:
				{
					this->value.float_number = static_cast<f32>(std::atof(t_jsonstring_temp->c_str()));
					return;
				}break;
			case ValueType::IndexArray:
				{
					this->value.index_array = NImpl::CreateIndexArrayFromJsonString(*t_jsonstring_temp);
					return;
				}break;
			case ValueType::AssociativeArray:
				{
					this->value.associative_array = NImpl::CreateAssociativeArrayFromJsonString(*t_jsonstring_temp);
					return;
				}break;
			case ValueType::BoolData:
				{
					const char t_char = t_jsonstring_temp->at(0);

					if((t_char == 't')||(t_char == 'T')){
						this->value.bool_data = true;
					}else{
						this->value.bool_data = false;
					}
					return;
				}break;
			case ValueType::BinaryData:
				{
					this->value.binary_data = NImpl::CreateBinaryDataFromJsonString(*t_jsonstring_temp);
				}break;
			case ValueType::None:
			case ValueType::Calc_BoolDataFalse:
			case ValueType::Calc_BoolDataTrue:
			case ValueType::Calc_UnknownNumber:
			default:
				{
					//不明。
					ASSERT(0);

					this->value.Reset();
					return;
				}break;
			}
		}

		//不明。
		ASSERT(0);

		this->value.Reset();
		return;
	}


	/** [取得]GetListMax
	*/
	s32 JsonItem::GetListMax() const
	{
		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		switch(this->valuetype){
		case ValueType::AssociativeArray:
			{
				return static_cast<s32>(this->value.associative_array->size());
			}break;
		case ValueType::IndexArray:
			{
				return static_cast<s32>(this->value.index_array->size());
			}break;
		case ValueType::StringData:
			{
				return static_cast<s32>(this->value.string_data->size());
			}break;
		case ValueType::None:
		case ValueType::IntegerNumber:
		case ValueType::FloatNumber:
		case ValueType::BoolData:
		case ValueType::BinaryData:
		case ValueType::Calc_BoolDataFalse:
		case ValueType::Calc_BoolDataTrue:
		case ValueType::Calc_UnknownNumber:
		default:
			{
			}
		}

		ASSERT(0);

		return 0;
	}


	/** [取得]GetStringData
	*/
	const sharedptr<STLString>& JsonItem::GetStringData() const
	{
		ASSERT(this->valuetype == ValueType::StringData);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.string_data;
	}


	/** [取得]GetInteger
	*/
	s32 JsonItem::GetInteger() const
	{
		ASSERT(this->valuetype == ValueType::IntegerNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.integer_number;
	}


	/** [取得]GetUnsignedInteger
	*/
	u32 JsonItem::GetUnsignedInteger() const
	{
		ASSERT(this->valuetype == ValueType::IntegerNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return static_cast<u32>(this->value.integer_number);
	}


	/** [取得]GetFloat
	*/
	f32 JsonItem::GetFloat() const
	{
		ASSERT(this->valuetype == ValueType::FloatNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.float_number;
	}


	/** [取得][値]GetBoolData
	*/
	bool JsonItem::GetBoolData() const
	{
		ASSERT(this->valuetype == ValueType::BoolData);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.bool_data;
	}


	/** [取得][値]GetBinaryData
	*/
	sharedptr<STLVector<u8>::Type>& JsonItem::GetBinaryData()
	{
		ASSERT(this->valuetype == ValueType::BinaryData);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.binary_data;
	}


	/** [取得]GetValueType
	*/
	JsonItem::ValueType::Id JsonItem::GetValueType() const
	{
		return this->valuetype;
	}


	/** タイプチェック。文字データ。
	*/
	bool JsonItem::IsStringData()
	{
		if(this->valuetype == ValueType::StringData){
			return true;
		}
		return false;
	}


	/** タイプチェック。連想配列。
	*/
	bool JsonItem::IsAssociativeArray()
	{
		if(this->valuetype == ValueType::AssociativeArray){
			return true;
		}
		return false;
	}


	/** タイプチェック。インデックス配列。
	*/
	bool JsonItem::IsIndexArray()
	{
		if(this->valuetype == ValueType::IndexArray){
			return true;
		}
		return false;
	}


	/** タイプチェック。整数。
	*/
	bool JsonItem::IsIntegerNumber()
	{
		if(this->valuetype == ValueType::IntegerNumber){
			return true;
		}
		return false;
	}


	/** タイプチェック。少数。
	*/
	bool JsonItem::IsFloatNumber()
	{
		if(this->valuetype == ValueType::FloatNumber){
			return true;
		}
		return false;
	}


	/** タイプチェック。真偽。
	*/
	bool JsonItem::IsBoolData()
	{
		if(this->valuetype == ValueType::BoolData){
			return true;
		}
		return false;
	}


	/** タイプチェック。バイナリデータ。
	*/
	bool JsonItem::IsBinaryData()
	{
		if(this->valuetype == ValueType::BinaryData){
			return true;
		}
		return false;
	}


	/** [取得]連想リストのアイテム取得。
	*/
	sharedptr<JsonItem>& JsonItem::GetItem(const STLString& a_itemname)
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		{
			auto t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->cend()){
				return t_it->second;
			}
		}

		ASSERT(0);

		return sharedptr_null<JsonItem>();
	}


	/** [取得]連想リストのアイテム取得。
	*/
	const sharedptr<JsonItem>& JsonItem::GetItem(const STLString& a_itemname) const
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		{
			auto t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->cend()){
				return t_it->second;
			}
		}

		ASSERT(0);

		return sharedptr_null<JsonItem>();
	}


	/** [取得]連想リストのアイテムチェック。
	*/
	bool JsonItem::IsExistItem(const STLString& a_itemname,ValueType::Id a_valuetype) const
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		{
			auto t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->cend()){
				if(a_valuetype == ValueType::None || t_it->second->GetValueType() == a_valuetype){
					return true;
				}
			}
		}
		
		return false;
	}


	/** [取得]インデックスリストのアイテム取得。
	*/
	sharedptr<JsonItem>& JsonItem::GetItem(s32 a_index)
	{
		ASSERT(a_index >= 0);
		u32 t_index = static_cast<u32>(a_index);

		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if(t_index < static_cast<s32>(this->value.index_array->size())){
			return this->value.index_array->at(t_index);
		}
		
		ASSERT(0);

		return sharedptr_null<JsonItem>();
	}


	/** [取得]インデックスリストのアイテム取得。
	*/
	const sharedptr<JsonItem>& JsonItem::GetItem(s32 a_index) const
	{
		ASSERT(a_index >= 0);
		u32 t_index = static_cast<u32>(a_index);

		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if(t_index < static_cast<s32>(this->value.index_array->size())){
			return this->value.index_array->at(t_index);
			
		}
		
		ASSERT(0);

		return sharedptr_null<JsonItem>();
	}


	/** [取得]インデックスリストのアイテムチェック。
	*/
	bool JsonItem::IsExistItem(s32 a_index,ValueType::Id a_valuetype)
	{
		ASSERT(a_index >= 0);
		u32 t_index = static_cast<u32>(a_index);

		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if(t_index < static_cast<s32>(this->value.index_array->size())){
			if(a_valuetype == ValueType::None || this->value.index_array->at(t_index)->GetValueType() == a_valuetype){
				return true;
			}

			return true;
		}
		
		return false;
	}


	/** [設定]連想リストにアイテム追加。削除。
	*/
	void JsonItem::SetItem(const STLString& a_itemname,const sharedptr<JsonItem>& a_item,bool a_deepcopy)
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		if(a_item != nullptr){
			if(a_deepcopy == true){
				this->value.associative_array->insert(std::make_pair(a_itemname,a_item->DeepCopy()));
			}else{
				this->value.associative_array->insert(std::make_pair(a_itemname,a_item));
			}
		}else{
			this->value.associative_array->erase(a_itemname);
		}
	}


	/** [設定]インデックスリストにアイテム追加。
	*/
	void JsonItem::AddItem(const sharedptr<JsonItem>& a_item,bool a_deepcopy)
	{
		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if(a_deepcopy == true){
			this->value.index_array->push_back(a_item->DeepCopy());
		}else{
			this->value.index_array->push_back(a_item);
		}
	}


	/** [削除]インデックスリストからアイテム削除。
	*/
	void JsonItem::RemoveItem(s32 a_index)
	{
		ASSERT(a_index >= 0);

		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		this->value.index_array->erase(this->value.index_array->cbegin() + a_index);
	}


	/** [設定]文字データ。
	*/
	void JsonItem::SetStringData(const STLString& a_string)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::StringData;
		this->value.string_data.reset(new STLString(a_string));
	}


	/** [設定]空連想リスト。
	*/
	void JsonItem::SetAssociativeArray()
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::AssociativeArray;
		this->value.associative_array.reset(new decltype(this->value.associative_array)::element_type());
	}


	/** [設定]空インデックスリスト。
	*/
	void JsonItem::SetIndexArray()
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IndexArray;
		this->value.index_array.reset(new decltype(this->value.index_array)::element_type());
	}


	/** [設定]整数セット。
	*/
	void JsonItem::SetInteger(s32 a_integer)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IntegerNumber;
		this->value.integer_number = a_integer;
	}


	/** [設定]整数セット。
	*/
	void JsonItem::SetUnsignedInteger(u32 a_unsignedinteger)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IntegerNumber;
		this->value.integer_number = static_cast<s32>(a_unsignedinteger);
	}


	/** [設定]少数セット。
	*/
	void JsonItem::SetFloat(f32 a_float)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = ValueType::FloatNumber;
		this->value.float_number = a_float;
	}


	/** [設定]真偽データセット。
	*/
	void JsonItem::SetBoolData(bool a_bool)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = ValueType::BoolData;
		this->value.bool_data = a_bool;
	}


	/** [設定]バイナリ―データセット。
	*/
	void JsonItem::SetBinaryData(const sharedptr<STLVector<u8>::Type>& a_binarydata)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = ValueType::BinaryData;
		this->value.binary_data = a_binarydata;
	}


	/** 連想配列キーリスト作成。
	*/
	sharedptr<STLVector<STLString>::Type> JsonItem::CreateAssociativeKeyList()
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		auto t_start = this->value.associative_array->cbegin();
		auto t_end = this->value.associative_array->cend();
		auto t_it = t_start;

		sharedptr<STLVector<STLString>::Type> t_ret_keylist(new STLVector<STLString>::Type());

		for(;t_it!=t_end;++t_it){
			t_ret_keylist->push_back(t_it->first);
		}

		return t_ret_keylist;
	}


	/** JsonStringへコンバート。
	*/
	#pragma warning(push)
	#pragma warning(disable:4702)
	const STLString JsonItem::ConvertJsonString() const
	{
		if(this->jsonstring != nullptr){
			return *(this->jsonstring);
		}

		switch(this->valuetype){
		case ValueType::StringData:
			{
				STLString t_jsonstring = "\"";
				t_jsonstring.reserve(64);
				{
					u32 t_index = 0;
					u32 t_max = static_cast<u32>(this->value.string_data->length());

					while(t_index < t_max){
						//１文字取得。
						u32 t_add = NImpl::GetMojiSize(*this->value.string_data,t_index,false);
						if(t_add == 1){
							const char* t_add_string = NImpl::CheckEscapeSequence((*(this->value.string_data))[t_index]);
							if(t_add_string == nullptr){
								//通常文字。
							}else{
								t_jsonstring += t_add_string;
								t_index++;
								continue;
							}
						}else if(t_add <= 0){
							//不明。
							ASSERT(0);

							return "";
						}

						t_jsonstring += this->value.string_data->substr(t_index,t_add);
						t_index += t_add;
					}
				}
				t_jsonstring += "\"";

				return t_jsonstring;
			}break;
		case ValueType::IntegerNumber:
			{
				return ToString(this->value.integer_number);
			}break;
		case ValueType::FloatNumber:
			{
				return ToString(this->value.float_number);
			}break;
		case ValueType::IndexArray:
			{
				STLString t_jsonstring = "[";
				t_jsonstring.reserve(64);
				{
					auto t_start = this->value.index_array->cbegin();
					auto t_end = this->value.index_array->cend();
					auto t_it = t_start;

					//一つ目。
					if(t_it != t_end){
						t_jsonstring += (*t_it)->ConvertJsonString();
						++t_it;

						//二つ目以降。
						for(;t_it!=t_end;++t_it){
							t_jsonstring += ",";
							t_jsonstring += (*t_it)->ConvertJsonString();
						}
					}
				}
				t_jsonstring += "]";
				return t_jsonstring;
			}break;
		case ValueType::AssociativeArray:
			{
				STLString t_jsonstring = "{";
				t_jsonstring.reserve(64);
				{
					auto t_start = this->value.associative_array->cbegin();
					auto t_end = this->value.associative_array->cend();
					auto t_it = t_start;

					if(t_it != t_end){
						//一つ目。
						t_jsonstring += "\"";
						t_jsonstring += t_it->first;
						t_jsonstring += "\":";
						t_jsonstring += (t_it->second)->ConvertJsonString();
						++t_it;

						//二つ目以降。
						for(;t_it!=t_end;++t_it){
							t_jsonstring += ",\"";
							t_jsonstring += t_it->first;
							t_jsonstring += "\":";
							t_jsonstring += (t_it->second)->ConvertJsonString();
						}
					}
				}
				t_jsonstring += "}";
				return t_jsonstring;
			}break;
		case ValueType::BoolData:
			{
				if(this->value.bool_data){
					return "true";
				}
				return "false";
			}break;
		case ValueType::BinaryData:
			{
				STLString t_jsonstring = "<";
				t_jsonstring.reserve(64);
				{
					//TODO:
				}
				t_jsonstring += ">";
				return t_jsonstring;
			}break;
		case JsonItem::ValueType::None:
		case JsonItem::ValueType::Calc_UnknownNumber:
		case JsonItem::ValueType::Calc_BoolDataTrue:
		case JsonItem::ValueType::Calc_BoolDataFalse:
		default:
			{
				//不明。
				ASSERT(0);

				return "";
			}break;
		}

		//不明。
		ASSERT(0);

		return "";
	}
	#pragma warning(pop) 

}
#endif

