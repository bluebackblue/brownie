

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 文字ツール。
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
#include "./stlstring.h"
#include "./malloca.h"
#include "./debugassert.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBlib
*/
namespace NBlib
{
	/** CharからWCharへ変換。
	*/
	void CharToWchar(const STLString& a_string,STLWString& a_wstring)
	{
		#if defined(PLATFORM_VCWIN)
		{
			//コードページ。
			UINT t_codepage = CP_UTF8;
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
				s32 t_alloca_size = t_wchar_use_len * sizeof(wchar);
				wchar* t_wchar = reinterpret_cast<wchar*>(MALLOCA(t_alloca_size));

				if(t_wchar != nullptr){
					//変換。
					t_wchar_use_len = ::MultiByteToWideChar(t_codepage,t_flags,t_char,t_char_len,t_wchar,t_alloca_size / sizeof(wchar));
					if(static_cast<s32>(t_wchar_use_len * sizeof(wchar)) == t_alloca_size){
						a_wstring = t_wchar;

						FREEA(t_wchar);
						return;
					}

					FREEA(t_wchar);
				}
			}
		}
		#endif

		a_wstring = L"";
		ASSERT(0);
	}


	/** WcharからCharへ変換。
	*/
	void WcharToChar(const STLWString& a_wstring,STLString& a_string)
	{
		#if defined(PLATFORM_VCWIN)
		{
			//コードページ。
			UINT t_codepage = CP_UTF8;
			//処理性能とマッピングのフラグ。
			DWORD t_flags = 0;

			//入力文字。
			const wchar* t_wchar = a_wstring.c_str();
			//入力文字数。終端を含める。
			s32 t_wchar_len = static_cast<s32>(a_wstring.length() + 1);

			//必要配列サイズを受け取る（バイト数ではない）。終端文字含む。
			s32 t_char_use_len = ::WideCharToMultiByte(t_codepage,t_flags,t_wchar,t_wchar_len,nullptr,0,nullptr,nullptr);
		
			if(t_char_use_len > 0){
				//出力文字。終端文字を含む。
				s32 t_alloca_size = t_char_use_len * sizeof(char);
				char* t_char = reinterpret_cast<char*>(MALLOCA(t_alloca_size));

				if(t_char != nullptr){
					//変換。
					t_char_use_len = ::WideCharToMultiByte(t_codepage,t_flags,t_wchar,t_wchar_len,t_char,t_alloca_size,nullptr,nullptr);
					if(static_cast<s32>(t_char_use_len * sizeof(char)) == t_alloca_size){
						a_string = t_char;

						FREEA(t_char);
						return;
					}
				}

				FREEA(t_char);
			}
		}
		#endif

		a_string = "";
		ASSERT(0);
	}


	/** 16進数文字列 => s32 への変換。
	*/
	void HexCharToInt(const STLString& a_string,s32& a_value)
	{
		const char* t_data = a_string.c_str();
		s32 t_size = static_cast<s32>(a_string.size());

		u32 t_value = 0;

		if(t_size > 0){

			s32 t_ii_start = 0;

			if(t_data[0] == '-'){
				t_ii_start = 1;
			}

			for(s32 ii=t_ii_start;ii<t_size;ii++){

				t_value <<= 4;

				switch(t_data[ii]){
				case '0':
					{
					}break;
				case '1':
					{
						t_value |= 1;
					}break;
				case '2':
					{
						t_value |= 2;
					}break;
				case '3':
					{
						t_value |= 3;
					}break;
				case '4':
					{
						t_value |= 4;
					}break;
				case '5':
					{
						t_value |= 5;
					}break;
				case '6':
					{
						t_value |= 6;
					}break;
				case '7':
					{
						t_value |= 7;
					}break;
				case '8':
					{
						t_value |= 8;
					}break;
				case '9':
					{
						t_value |= 9;
					}break;
				case 'a':
				case 'A':
					{
						t_value |= 10;
					}break;
				case 'b':
				case 'B':
					{
						t_value |= 11;
					}break;
				case 'c':
				case 'C':
					{
						t_value |= 12;
					}break;
				case 'd':
				case 'D':
					{
						t_value |= 13;
					}break;
				case 'e':
				case 'E':
					{
						t_value |= 14;
					}break;
				case 'f':
				case 'F':
					{
						t_value |= 15;
					}break;
				default:
					{
						a_value = 0;
					}return;
				}
			}

			if(t_ii_start == 0){
				a_value = t_value;
			}else{
				a_value = - static_cast<s32>(t_value);
			}

			return;
		}

		a_value = 0;
		return;
	}


	/** a_stringの先頭文字がa_prefixと一致するかどうか。
	*/
	bool StartsWith(const STLString& a_string,const STLString& a_prefix)
	{
		const char* t_string = a_string.c_str();
		const char* t_prefix = a_prefix.c_str();
		s32 t_ii_max = static_cast<s32>(a_prefix.size());

		for(s32 ii=0;ii<t_ii_max;ii++){
			if(a_string[ii] == nullchar){
				return false;
			}else if(t_string[ii] != t_prefix[ii]){
				return false;
			}
		}

		return true;
	}


}

