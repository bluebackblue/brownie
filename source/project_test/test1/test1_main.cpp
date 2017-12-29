

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(DEF_TEST_INDEX == 1)
namespace NTest
{
	/** Test_Main
	*/
	void Test_Main()
	{
		//signed
		s8 t_s8 = -1;
		s16 t_s16 = -1;
		s32 t_s32 = -1;
		s64 t_s64 = -1;
		UNUSED(t_s8);
		UNUSED(t_s16);
		UNUSED(t_s32);
		UNUSED(t_s64);

		//unsigned
		u8 t_u8 = 0xFF;
		u16 t_u16 = 0xFFFF;
		u32 t_u32 = 0xFFFFFFFF;
		u64 t_u64 = 0xFFFFFFFFFFFFFFFF;
		UNUSED(t_u8);
		UNUSED(t_u16);
		UNUSED(t_u32);
		UNUSED(t_u64);

		//float
		f32 t_f32 = 0.0f;
		UNUSED(t_f32);

		//double
		f64 t_f64 = 0.0l;
		UNUSED(t_f64);

		//address
		AddressType t_address = reinterpret_cast<AddressType>(&t_u32);
		UNUSED(t_address);

		//char
		char t_char = nullchar;
		UNUSED(t_char);

		//wchar
		wchar t_wchar = nullwchar;
		UNUSED(t_wchar);

		//string
		STLString t_string = "abcd";
		UNUSED(t_string);

		//wstring
		STLWString t_wstring = L"abcd";
		UNUSED(t_wstring);

		//vector
		STLVector<s32>::Type t_vector;
		t_vector.push_back(1);
		t_vector.push_back(2);
		t_vector.push_back(3);
		std::sort(t_vector.begin(),t_vector.end(),[](const s32& a_top,const s32& a_down){
			return (a_top > a_down);
		});

		//map
		STLMap<s16,s64>::Type t_map;
		t_map.insert(std::make_pair(t_s16,t_s64));
		auto t_it = t_map.find(t_s16);
		if(t_it != t_map.cend()){
			ASSERT(t_it->second == t_s64);
		}

		//list
		STLList<s32>::Type t_list;
		t_list.push_back(1);
		t_list.push_front(2);
		t_list.push_back(3);
		t_list.sort([](const s32& a_top,const s32& a_down){
			return (a_top > a_down);
		});

		return;
	}


}
#endif

