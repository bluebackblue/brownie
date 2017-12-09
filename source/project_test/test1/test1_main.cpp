

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief インクルード。
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST1
*/
#if defined(DEF_TEST1)


/** include
*/
#include "./test1_main.h"


/** Test_Main
*/
void Test_Main()
{
	//signed
	s8 t_s8 = -1;
	s16 t_s16 = -1;
	s32 t_s32 = -1;
	s64 t_s64 = -1;

	//unsigned
	u8 t_u8 = 0xFF;
	u16 t_u16 = 0xFFFF;
	u32 t_u32 = 0xFFFFFFFF;
	u64 t_u64 = 0xFFFFFFFFFFFFFFFF;

	//float
	f32 t_f32 = 0.0f;

	//double
	f64 t_f64 = 0.0l;

	//address
	AddressType t_address = reinterpret_cast<AddressType>(&t_u32);

	//char
	char t_char = nullchar;

	//wchar
	wchar t_wchar = nullwchar;

	//string
	STLString t_string = "abcd";

	//wstring
	STLWString t_wstring = L"abcd";

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
	t_map.insert(decltype(t_map)::value_type(t_s16,t_s64));
	decltype(t_map)::iterator t_it = t_map.find(t_s16);
	if(t_it != t_map.end()){
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

#endif

