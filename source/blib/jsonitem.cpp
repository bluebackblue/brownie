

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �i�r�n�m�A�C�e���B
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
#include "./vastring.h"
#include "./autolock.h"
#include "./blib_bootinitialize.h"


/** include
*/
#if(BLIB_STDREGEX_ENABLE)

	#include <regex>

#endif


/** NBlib
*/
namespace NBlib
{

	#if(BLIB_JSONITEM_ENABLE)

	/** [static]�m�ہB
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

	/** [static]����B
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
		/** �ŏ��̈ꕶ������^�C�v�𐄑��B
		*/
		JsonItem::ValueType::Id GetValueTypeFromChar(char a_char)
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
					return JsonItem::ValueType::BoolDataTrue;
				}break;
			case 'f':
			case 'F':
				{
					return JsonItem::ValueType::BoolDataFalse;
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
					return JsonItem::ValueType::UnknownNumber;
				}break;
			default:
				{
					//�s���ȊJ�n�����B
					ASSERT(0);

					return JsonItem::ValueType::None;
				}break;
			}
		}

		/** �����`�F�b�N�B
		*/
		bool IsInteger(const STLString& a_string)
		{
			#if(BLIB_STDREGEX_ENABLE)
			{
				return std::regex_match(a_string.c_str(),std::cmatch(),std::regex("^[-]?[0-9]+"));
			}
			#else
			{
				STLString::const_iterator t_start = a_string.begin();
				STLString::const_iterator t_end = a_string.end();
				STLString::const_iterator t_it = t_start;

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

		/** �G�X�P�[�v�V�[�P���X�������u���{�����v�ɕϊ��B
		*/
		const char* CheckEscapeSequence(char a_char)
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

			//�ʏ핶���B
			return nullptr;
		}

		/** �u���{�����v���V�[�P���X�����ɕϊ��B
		*/
		const char* ToSequenceString(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if(a_string[a_index] == '\\'){
					if((0 <= (a_index+1)) && ((a_index+1) < static_cast<s32>(a_string.length()))){
						switch(a_string[a_index+1]){
						case '\"':
							{
								//�_�u���N�H�[�e�[�V�����B
								return "\"";
							}break;
						case '\'':
							{
								//�V���O���N�H�[�e�[�V�����B
								return "\'";
							}break;
						case '\\':
							{
								//���B
								return "\\";
							}break;
						case 'n':
							{
								//���s�B
								return "\n";
							}break;
						case '/':
							{
								//�X���b�V���B
								return "/";
							}break;
						default:
							{
								//�m��Ȃ��G�X�P�[�v�V�[�P���X�B
								ASSERT(0);

								return nullptr;
							}break;
						}
					}else{
						//�͈͊O�B
						ASSERT(0);

						return nullptr;
					}
				}else{
					//�ʏ핶���B
					ASSERT(0);

					return nullptr;
				}
			}else{
				//�͈͊O�B
				ASSERT(0);

				return nullptr;
			}

			//�s���B
			ASSERT(0);

			return nullptr;
		}

		/** �����̃T�C�Y�B
		*/
		s32 GetMojiSize(const STLString& a_string,s32 a_index,bool a_escape)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if(a_string[a_index] == '\\'){
					if(a_escape == true){
						if(static_cast<s32>(a_string.length()) >= (2 + a_index)){
							//�G�X�P�[�v�V�[�P���X�̌��͂P�o�C�g�����B
							return 2;
						}else{
							//������������Ȃ��B
							ASSERT(0);

							return 0;
						}
					}else{
						//�G�X�P�[�v�V�[�P���X�Ƃ��ď������Ȃ��B
						return 1;
					}
				}else{
					//�G�X�P�[�v�V�[�P���X�ȊO�B

					u8 t_char = a_string[a_index];

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
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}
		}

		/** ������JSON�̒����B
		*/
		s32 GetLength_StringData(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if((a_string[a_index] == '"')||(a_string[a_index] == '\'')){
					s32 t_index = a_index + 1;
					while(t_index < static_cast<s32>(a_string.length())){
						if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//�I�[�B
							return t_index - a_index + 1;
						}else{
							//���̕����ցB
							s32 t_add = GetMojiSize(a_string,t_index,true);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//�\�z�O�̕����R�[�h�B
								ASSERT(0);

								return 0;
							}
						}
					}
				
					//�\�z�O�̏I�[�B
					ASSERT(0);

					return 0;
				}else{
					//������ȊO�B
					ASSERT(0);

					return 0;
				}
			}else{
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}
		}

		/** ����JSON�̒����B
		*/
		s32 GetLength_Number(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				s32 t_index = a_index;
				while(t_index < static_cast<s32>(a_string.length())){
					switch(a_string[t_index]){
					case '}':
					case ']':
					case ',':
						{
							//�I�[�B
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
							//���l�B
							t_index++;
						}break;
					default:
						{
							//�s���B
							ASSERT(0);

							return 0;
						}break;	
					}
				}
			
				//�I�[�B
				return t_index - a_index;
			}else{
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}
		}

		/** �A�z���X�gJSON�̒����B
		*/
		s32 GetLength_AssociateArray(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if(a_string[a_index] == '{'){
					s32 t_nest = 1;
					s32 t_index = a_index + 1;
				
					while(t_index < static_cast<s32>(a_string.length())){
						if(a_string[t_index] == '}'){
							if(t_nest <= 1){
								//�I�[�B
								return t_index - a_index + 1;
							}else{
								//�l�X�g�B
								t_nest--;
								t_index++;
							}
						}else if(a_string[t_index] == '{'){
							//�l�X�g�B
							t_nest++;
							t_index++;
						}else if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//������B
							s32 t_add = GetLength_StringData(a_string,t_index);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//�\�z�O�̕����R�[�h�B
								ASSERT(0);

								return 0;
							}
						}else{
							//���ցB
							t_index++;
						}
					}
				
					//�I�[���Ȃ��B
					ASSERT(0);

					return 0;
				}else{
					//�A�z�z��ȊO�B
					ASSERT(0);

					return 0;
				}
			}else{
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}
		}

		/** �C���f�b�N�X���X�gJSON�̒����B
		*/
		s32 GetLength_IndexArray(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if(a_string[a_index] == '['){
					s32 t_nest = 1;
					s32 t_index = a_index + 1;
				
					while(t_index < static_cast<s32>(a_string.length())){
						if(a_string[t_index] == ']'){
							if(t_nest <= 1){
								//�I�[�B
								return t_index - a_index + 1;
							}else{
								//�l�X�g�B
								t_nest--;
								t_index++;
							}
						}else if(a_string[t_index] == '['){
							//�l�X�g�B
							t_nest++;
							t_index++;
						}else if((a_string[t_index] == '"')||(a_string[t_index] == '\'')){
							//������B
							s32 t_add = GetLength_StringData(a_string,t_index);
							if(t_add > 0){
								t_index += t_add;
							}else{
								//�\�z�O�̕����R�[�h�B
								ASSERT(0);

								return 0;
							}
						}else{
							//���ցB
							t_index++;
						}
					}
				
					//�I�[���Ȃ��B
					ASSERT(0);

					return 0;	
				}else{
					//�z��ȊO�B
					ASSERT(0);

					return 0;
				}
			}else{
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}
		}

		/** TRUEJSON�̒����B
		*/
		s32 GetLength_BoolTrue(const STLString& a_string,s32 a_index)
		{
			const char t_true_1[4] = {'T','R','U','E'};
			const char t_true_2[4] = {'t','r','u','e'};

			for(s32 ii=0;ii<COUNTOF(t_true_1);ii++){
				s32 t_index = a_index + ii;
				if((0 <= t_index) && (t_index < static_cast<s32>(a_string.length()))){
					if((a_string[t_index] == t_true_1[ii])||(a_string[t_index] == t_true_2[ii])){
					}else{
						//TRUE�ȊO�B
						ASSERT(0);
						
						return 0;
					}
				}else{
					//TRUE�ȊO�B
					ASSERT(0);

					return 0;
				}
			}

			{
				s32 t_index = a_index + COUNTOF(t_true_1);

				if((0 <= t_index) && (t_index < static_cast<s32>(a_string.length()))){
					if((a_string[t_index] == '}')||(a_string[t_index] == ']')||(a_string[t_index] == ',')){
						//�I�[�B
						return COUNTOF(t_true_1);
					}else{
						//TRUE�ȊO�B
						ASSERT(0);

						return 0;					
					}
				}else{
					//TRUE�ȊO�B
					ASSERT(0);

					return 0;
				}
			}
		}

		/** FALSEJSON�̒����B
		*/
		s32 GetLength_BoolFalse(const STLString& a_string,s32 a_index)
		{
			const char t_true_1[5] = {'F','A','L','S','E'};
			const char t_true_2[5] = {'f','a','l','s','e'};

			for(s32 ii=0;ii<COUNTOF(t_true_1);ii++){
				s32 t_index = a_index + ii;
				if((0 <= t_index) && (t_index < static_cast<s32>(a_string.length()))){
					if((a_string[t_index] == t_true_1[ii])||(a_string[t_index] == t_true_2[ii])){
					}else{
						//FALSE�ȊO�B
						ASSERT(0);
						
						return 0;
					}
				}else{
					//FALSE�ȊO�B
					ASSERT(0);

					return 0;
				}
			}

			{
				s32 t_index = a_index + COUNTOF(t_true_1);

				if((0 <= t_index) && (t_index < static_cast<s32>(a_string.length()))){
					if((a_string[t_index] == '}')||(a_string[t_index] == ']')||(a_string[t_index] == ',')){
						//�I�[�B
						return COUNTOF(t_true_1);
					}else{
						//FALSE�ȊO�B
						ASSERT(0);

						return 0;					
					}
				}else{
					//FALSE�ȊO�B
					ASSERT(0);

					return 0;
				}
			}
		}

		/** BinaryData�̒����B
		*/
		s32 GetLength_BinaryData(const STLString& a_string,s32 a_index)
		{
			if((0 <= a_index) && (a_index < static_cast<s32>(a_string.length()))){
				if(a_string[a_index] == '<'){

					s32 t_index = a_index + 1;
				
					while(t_index < static_cast<s32>(a_string.length())){
						switch(a_string[t_index]){
						case '>':
							{
								//�I�[�B
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
								//���ցB
								t_index++;
							}break;
						default:
							{
								//�s���B
								ASSERT(0);

								return 0;
							}break;
						}
					}
				
					//�I�[���Ȃ��B
					ASSERT(0);

					return 0;	
				}else{
					//�o�C�i���f�[�^�ȊO�B
					ASSERT(0);

					return 0;
				}
			}else{
				//�͈͊O�B
				ASSERT(0);

				return 0;
			}

		}

		/** JSON��������C���f�b�N�X���X�g�̍쐬[*,*,*]�B
		*/
		sharedptr<STLVector<sharedptr<JsonItem>>::Type> CreateIndexArrayFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLVector<sharedptr<JsonItem>>::Type> t_indexlist(new STLVector<sharedptr<JsonItem>>::Type());
		
			s32 t_index = 0;
			while(t_index < static_cast<s32>(a_jsonstring.length())){
				if(a_jsonstring[t_index] == ']'){
					//�I�[�B
					ASSERT(t_index + 1 == static_cast<s32>(a_jsonstring.length()));

					return t_indexlist;
				}else if(a_jsonstring[t_index] == ','){
					//���̍��ڂ���B
					t_index++;
				}else if(a_jsonstring[t_index] == '['){
					if(t_index == 0){
						//�J�n�B
						t_index++;
						continue;
					}else if(t_index == 1){
						//�C���f�b�N�X���X�g�̒��ɃC���f�b�N�X���X�g�B
					}else{
						//�s���B
						ASSERT(0);

						t_indexlist.reset(new STLVector<sharedptr<JsonItem>>::Type());
						return t_indexlist;
					}
				}
		
				//�l�B
				s32 t_value_size = 0;
				switch(GetValueTypeFromChar(a_jsonstring[t_index])){
				case JsonItem::ValueType::StringData:
					{
						t_value_size = GetLength_StringData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::UnknownNumber:
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
				case JsonItem::ValueType::BoolDataTrue:
					{
						t_value_size = GetLength_BoolTrue(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BoolDataFalse:
					{
						t_value_size = GetLength_BoolFalse(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BinaryData:
					{
						t_value_size = GetLength_BinaryData(a_jsonstring,t_index);
					}break;
				default:
					{
						//�s���B
						ASSERT(0);

						t_indexlist.reset(new STLVector<sharedptr<JsonItem>>::Type());
						return t_indexlist;
					}break;
				}
			
				//���X�g�̍Ō�ɒǉ��B
				if(t_value_size > 0){
					sharedptr<JsonItem> t_additem(new JsonItem());
					{
						t_additem->SetJsonString(a_jsonstring.substr(t_index,t_value_size));
					}

					t_indexlist->push_back(t_additem);

					t_index += t_value_size;
				}else{
					ASSERT(0);

					t_indexlist.reset(new STLVector<sharedptr<JsonItem>>::Type());
					return t_indexlist;
				}
			}
		
			//�͈͊O�B
			ASSERT(0);

			t_indexlist.reset(new STLVector<sharedptr<JsonItem>>::Type());
			return t_indexlist;
		}

		/** JSON��������A�z�z��̍쐬�B
		*/
		sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type> CreateAssociativeArrayFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type> t_associativelist(new STLMap<STLString,sharedptr<JsonItem>>::Type);
		
			s32 t_index = 0;
			while(t_index < static_cast<s32>(a_jsonstring.length())){
				if(a_jsonstring[t_index] == '}'){
					//�I�[�B
					ASSERT(t_index + 1 == static_cast<s32>(a_jsonstring.length()));

					return t_associativelist;
				}else if(a_jsonstring[t_index] == ','){
					//���̍��ڂ���B
					t_index++;
				}else if(a_jsonstring[t_index] == '{'){
					if(t_index == 0){
						//�J�n�B
						t_index++;
						continue;
					}else{
						//�s���B
						ASSERT(0);

						t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
						return t_associativelist;
					}
				}
			
				//���O�B
				STLString t_name_string;
				if((a_jsonstring[t_index] == '"')||(a_jsonstring[t_index] == '\'')){
					s32 t_name_size = GetLength_StringData(a_jsonstring,t_index);
					if(t_name_size >= 2){
						t_name_string = a_jsonstring.substr(t_index+1,t_name_size-2);
						t_index += t_name_size;
					}else{
						//�s���B
						ASSERT(0);

						t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
						return t_associativelist;
					}
				}else{
					//�s���B
					ASSERT(0);

					t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
					return t_associativelist;
				}
			
				//�u:�v�B
				if(a_jsonstring[t_index] == ':'){
					t_index++;
				}else{
					//�s���B
					ASSERT(0);

					t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
					return t_associativelist;
				}
			
				//�l�B
				s32 t_value_size = 0;
				switch(GetValueTypeFromChar(a_jsonstring[t_index])){
				case JsonItem::ValueType::StringData:
					{
						t_value_size = GetLength_StringData(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::UnknownNumber:
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
				case JsonItem::ValueType::BoolDataTrue:
					{
						t_value_size = GetLength_BoolTrue(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BoolDataFalse:
					{
						t_value_size = GetLength_BoolFalse(a_jsonstring,t_index);
					}break;
				case JsonItem::ValueType::BinaryData:
					{
						t_value_size = GetLength_BinaryData(a_jsonstring,t_index);
					}break;
				default:
					{
						//�s���B
						ASSERT(0);

						t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
						return t_associativelist;
					}break;
				}
			
				//���X�g�ɒǉ��B
				if(t_value_size > 0){
					sharedptr<JsonItem> t_additem(new JsonItem());
					{
						t_additem->SetJsonString(a_jsonstring.substr(t_index,t_value_size));
					}

					t_associativelist->insert(STLMap<STLString,sharedptr<JsonItem>>::value_type(t_name_string,t_additem));

					t_index += t_value_size;
				}else{
					ASSERT(0);

					t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
					return t_associativelist;
				}
			}
		
			//�͈͊O�B
			ASSERT(0);

			t_associativelist.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type);
			return t_associativelist;
		}

		/** JSON��������o�C�i���f�[�^�̍쐬�B
		*/
		sharedptr<STLVector<u8>::Type> CreateBinaryDataFromJsonString(const STLString& a_jsonstring)
		{
			sharedptr<STLVector<u8>::Type> t_binarydata(new STLVector<u8>::Type());

			t_binarydata->reserve(a_jsonstring.length() / 2);

			s32 t_index = 0;
			while(t_index < static_cast<s32>(a_jsonstring.length())){
				if(a_jsonstring[t_index] == '>'){
					//�I�[�B
					ASSERT(t_index + 1 == static_cast<s32>(a_jsonstring.length()));

					return t_binarydata;
				}else if(a_jsonstring[t_index] == '<'){
					if(t_index == 0){
						//�J�n�B
						t_index++;
						continue;
					}else{
						//�s���B
						ASSERT(0);

						t_binarydata.reset(new STLVector<u8>::Type());
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
							//�s���B
							ASSERT(0);

							t_binarydata.reset(new STLVector<u8>::Type());
							return t_binarydata;
						}break;
					}

					t_index++;

					if(t_index < static_cast<s32>(a_jsonstring.length())){
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
								//�s���B
								ASSERT(0);

								t_binarydata.reset(new STLVector<u8>::Type());
								return t_binarydata;
							}break;
						}

						t_index++;

						t_binarydata->push_back(t_binary);
					}else{
						//�s���B
						ASSERT(0);

						t_binarydata.reset(new STLVector<u8>::Type());
						return t_binarydata;
					}
				}
			}

			//�͈͊O�B
			ASSERT(0);

			t_binarydata.reset(new STLVector<u8>::Type());
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
	JsonItem::JsonItem(const Value_Bool& a_value)
	{
		this->SetBool(a_value.value);
	}

	/** constructor
	*/
	JsonItem::JsonItem(const Value_BinaryData& a_value)
	{
		this->SetBinaryData(a_value.value);
	}

	/** �f�B�[�v�R�s�[�B
	*/
	sharedptr<JsonItem> JsonItem::DeepCopy() const
	{
		sharedptr<JsonItem> t_new_jsonitem(new JsonItem(this->ConvertJsonString()));
		return t_new_jsonitem;
	}


	/** �i�r�n�m��������Z�b�g�B
	*/
	void JsonItem::SetJsonString(const STLString& a_jsonstring)
	{
		if(static_cast<s32>(a_jsonstring.length()) > 0){
			ValueType::Id t_valuetype = NImpl::GetValueTypeFromChar(a_jsonstring[0]);
			switch(t_valuetype){
			case ValueType::StringData:
			case ValueType::AssociativeArray:
			case ValueType::IndexArray:
			case ValueType::BinaryData:
			case ValueType::BoolDataTrue:
			case ValueType::BoolDataFalse:
			case ValueType::IntegerNumber:
			case ValueType::FloatNumber:
				{
					this->jsonstring.reset(new STLString(a_jsonstring));
					this->valuetype = t_valuetype;
					this->value.Reset();
					return;
				}break;
			case ValueType::UnknownNumber:
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


	/** �l���B
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
					s32 t_index = 1;
					s32 t_max = static_cast<s32>(t_jsonstring_temp->length() - 1);

					this->value.string_data.reset(new STLString());
					this->value.string_data->reserve(16 + t_max);
				
					while(t_index < t_max){
						s32 t_add = NImpl::GetMojiSize((*t_jsonstring_temp),t_index,true);
						if(t_add == 2){
							if((*t_jsonstring_temp)[t_index] == '\\'){
								//�G�X�P�[�v�V�[�P���X�������V�[�P���X�����ɕϊ��B
								const char* t_add_string = NImpl::ToSequenceString((*t_jsonstring_temp),t_index);
								if(t_add_string != nullptr){
									//�ϊ��㕶�����ǉ��B
									this->value.string_data->append(t_add_string);
								}else{
									//�s���B
									ASSERT(0);

									*(this->value.string_data) = "";
									return;
								}
							}else{
								//�ʏ핶���i�Q�����j��ǉ��B
								this->value.string_data->append(t_jsonstring_temp->substr(t_index,t_add));
							}
						}else if(t_add > 0){
							//�ʏ핶���i���������j��ǉ��B
							this->value.string_data->append(t_jsonstring_temp->substr(t_index,t_add));
						}else{
							//�s���ȃG���R�[�h�B
							ASSERT(0);

							*(this->value.string_data) = "";
							return;
						}

						t_index += t_add;
					}

					if(t_index != t_max){
						//�s���ȃG���R�[�h�B
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
			case ValueType::BoolDataTrue:
				{
					this->value.bool_value = true;
					return;
				}break;
			case ValueType::BoolDataFalse:
				{
					this->value.bool_value = false;
					return;
				}break;
			case ValueType::BinaryData:
				{
					this->value.binary_data = NImpl::CreateBinaryDataFromJsonString(*t_jsonstring_temp);
				}break;
			default:
				{
					//�s���B
					ASSERT(0);

					this->value.Reset();
					return;
				}break;
			}
		}

		//�s���B
		ASSERT(0);

		this->value.Reset();
		return;
	}

	/** [�擾]GetListMax
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
		}

		ASSERT(0);

		return 0;
	}

	/** [�擾]GetStringData
	*/
	const sharedptr<STLString>& JsonItem::GetStringData() const
	{
		ASSERT(this->valuetype == ValueType::StringData);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.string_data;
	}

	/** [�擾]GetInteger
	*/
	s32 JsonItem::GetInteger() const
	{
		ASSERT(this->valuetype == ValueType::IntegerNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.integer_number;
	}

	/** [�擾]GetUnsignedInteger
	*/
	u32 JsonItem::GetUnsignedInteger() const
	{
		ASSERT(this->valuetype == ValueType::IntegerNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return static_cast<u32>(this->value.integer_number);
	}

	/** [�擾]GetFloat
	*/
	f32 JsonItem::GetFloat() const
	{
		ASSERT(this->valuetype == ValueType::FloatNumber);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.float_number;
	}

	/** [�擾][�l]GetBool
	*/
	bool JsonItem::GetBool() const
	{
		ASSERT((this->valuetype == ValueType::BoolDataTrue)||(this->valuetype == ValueType::BoolDataFalse));

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.bool_value;
	}

	/** [�擾][�l]GetBinaryData
	*/
	sharedptr<STLVector<u8>::Type>& JsonItem::GetBinaryData()
	{
		ASSERT(this->valuetype == ValueType::BinaryData);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		return this->value.binary_data;
	}

	/** [�擾]GetValueType
	*/
	JsonItem::ValueType::Id JsonItem::GetValueType() const
	{
		return this->valuetype;
	}

	/** [�擾]�A�z���X�g�̃A�C�e���擾�B
	*/
	sharedptr<JsonItem>& JsonItem::GetItem(const STLString& a_itemname)
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		{
			STLMap<STLString,sharedptr<JsonItem>>::iterator t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->end()){
				return t_it->second;
			}
		}

		ASSERT(0);

		return sharedptr<JsonItem>::null();
	}

	/** [�擾]�A�z���X�g�̃A�C�e���擾�B
	*/
	const sharedptr<JsonItem>& JsonItem::GetItem(const STLString& a_itemname) const
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		{
			STLMap<STLString,sharedptr<JsonItem>>::iterator t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->end()){
				return t_it->second;
			}
		}

		ASSERT(0);

		return sharedptr<JsonItem>::null();
	}

	/** [�擾]�A�z���X�g�̃A�C�e���`�F�b�N�B
	*/
	bool JsonItem::IsExistItem(const STLString& a_itemname)
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		{
			STLMap<STLString,sharedptr<JsonItem>>::iterator t_it = this->value.associative_array->find(a_itemname);
			if(t_it != this->value.associative_array->end()){
				return true;
			}
		}
		
		return false;
	}

	/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���擾�B
	*/
	sharedptr<JsonItem>& JsonItem::GetItem(s32 a_index)
	{
		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if((0 <= a_index) && (a_index < static_cast<s32>(this->value.index_array->size()))){
			return (*(this->value.index_array))[a_index];
		}
		
		ASSERT(0);

		return sharedptr<JsonItem>::null();
	}

	/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���擾�B
	*/
	const sharedptr<JsonItem>& JsonItem::GetItem(s32 a_index) const
	{
		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if((0 <= a_index) && (a_index < static_cast<s32>(this->value.index_array->size()))){
			return (*(this->value.index_array))[a_index];
		}
		
		ASSERT(0);

		return sharedptr<JsonItem>::null();
	}

	/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���`�F�b�N�B
	*/
	bool JsonItem::IsExistItem(s32 a_index)
	{
		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		if((0 <= a_index) && (a_index < static_cast<s32>(this->value.index_array->size()))){
			return true;
		}
		
		return false;
	}

	/** [�ݒ�]�A�z���X�g�ɃA�C�e���ǉ��B�폜�B
	*/
	void JsonItem::SetItem(const STLString& a_itemname,sharedptr<JsonItem>& a_item,bool a_deepcopy)
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		if(a_item != nullptr){
			if(a_deepcopy == true){
				this->value.associative_array->insert(STLMap<STLString,sharedptr<JsonItem>>::value_type(a_itemname,a_item->DeepCopy()));
			}else{
				this->value.associative_array->insert(STLMap<STLString,sharedptr<JsonItem>>::value_type(a_itemname,a_item));
			}
		}else{
			this->value.associative_array->erase(a_itemname);
		}
	}

	/** [�ݒ�]�C���f�b�N�X���X�g�ɃA�C�e���ǉ��B
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

	/** [�폜]�C���f�b�N�X���X�g����A�C�e���폜�B
	*/
	void JsonItem::RemoveItem(s32 a_index)
	{
		ASSERT(this->valuetype == ValueType::IndexArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}
		
		this->value.index_array->erase(this->value.index_array->begin()+a_index);
	}

	/** [�ݒ�]�����f�[�^�B
	*/
	void JsonItem::SetStringData(const STLString& a_string)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::StringData;
		this->value.string_data.reset(new STLString(a_string));
	}

	/** [�ݒ�]��A�z���X�g�B
	*/
	void JsonItem::SetAssociativeArray()
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::AssociativeArray;
		this->value.associative_array.reset(new STLMap<STLString,sharedptr<JsonItem>>::Type());
	}

	/** [�ݒ�]��C���f�b�N�X���X�g�B
	*/
	void JsonItem::SetIndexArray()
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IndexArray;
		this->value.index_array.reset(new STLVector<sharedptr<JsonItem>>::Type());
	}

	/** [�ݒ�]�����Z�b�g�B
	*/
	void JsonItem::SetInteger(s32 a_integer)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IntegerNumber;
		this->value.integer_number = a_integer;
	}

	/** [�ݒ�]�����Z�b�g�B
	*/
	void JsonItem::SetUnsignedInteger(u32 a_unsignedinteger)
	{
		this->jsonstring.reset();
		this->value.Reset();
		
		this->valuetype = ValueType::IntegerNumber;
		this->value.integer_number = static_cast<s32>(a_unsignedinteger);
	}

	/** [�ݒ�]�����Z�b�g�B
	*/
	void JsonItem::SetFloat(f32 a_float)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = ValueType::FloatNumber;
		this->value.float_number = a_float;
	}

	/** [�ݒ�]Bool�Z�b�g�B
	*/
	void JsonItem::SetBool(bool a_bool)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = a_bool ? ValueType::BoolDataTrue : ValueType::BoolDataFalse;
		this->value.bool_value = a_bool;
	}

	/** [�ݒ�]�o�C�i���\�f�[�^�Z�b�g�B
	*/
	void JsonItem::SetBinaryData(const sharedptr<STLVector<u8>::Type>& a_binarydata)
	{
		this->jsonstring.reset();
		this->value.Reset();

		this->valuetype = ValueType::BinaryData;
		this->value.binary_data = a_binarydata;
	}

	/** �A�z�z��L�[���X�g�쐬�B
	*/
	sharedptr<STLVector<STLString>::Type> JsonItem::CreateAssociativeKeyList()
	{
		ASSERT(this->valuetype == ValueType::AssociativeArray);

		if(this->jsonstring != nullptr){
			this->JsonStringToValue();
		}

		STLMap<STLString,sharedptr<JsonItem>>::iterator t_start = this->value.associative_array->begin();
		STLMap<STLString,sharedptr<JsonItem>>::iterator t_end = this->value.associative_array->end();
		STLMap<STLString,sharedptr<JsonItem>>::iterator t_it = t_start;

		sharedptr<STLVector<STLString>::Type> t_ret_keylist(new STLVector<STLString>::Type());

		for(;t_it!=t_end;++t_it){
			t_ret_keylist->push_back(t_it->first);
		}

		return t_ret_keylist;
	}

	/** JsonString�փR���o�[�g�B
	*/
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
					s32 t_index = 0;
					s32 t_max = static_cast<s32>(this->value.string_data->length());

					while(t_index < t_max){
						//�P�����擾�B
						s32 t_add = NImpl::GetMojiSize(*this->value.string_data,t_index,true);
						if(t_add == 1){
							const char* t_add_string = NImpl::CheckEscapeSequence((*(this->value.string_data))[t_index]);
							if(t_add_string == nullptr){
								//�ʏ핶���B
							}else{
								t_jsonstring += t_add_string;
								t_index++;
								continue;
							}
						}else if(t_add <= 0){
							//�s���B
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
				char t_buffer[32] = {0};
				return VASTRING(t_buffer,sizeof(t_buffer),"%d",this->value.integer_number);
			}break;
		case ValueType::FloatNumber:
			{
				char t_buffer[32] = {0};
				return VASTRING(t_buffer,sizeof(t_buffer),"%f",this->value.float_number);
			}break;
		case ValueType::IndexArray:
			{
				STLString t_jsonstring = "[";
				t_jsonstring.reserve(64);
				{
					STLVector<sharedptr<JsonItem>>::const_iterator t_start = this->value.index_array->begin();
					STLVector<sharedptr<JsonItem>>::const_iterator t_end = this->value.index_array->end();
					STLVector<sharedptr<JsonItem>>::const_iterator t_it = t_start;

					//��ځB
					if(t_it != t_end){
						t_jsonstring += (*t_it)->ConvertJsonString();
						++t_it;

						//��ڈȍ~�B
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
					STLMap<STLString,sharedptr<JsonItem>>::const_iterator t_start = this->value.associative_array->begin();
					STLMap<STLString,sharedptr<JsonItem>>::const_iterator t_end = this->value.associative_array->end();
					STLMap<STLString,sharedptr<JsonItem>>::const_iterator t_it = t_start;

					if(t_it != t_end){
						//��ځB
						t_jsonstring += "\"";
						t_jsonstring += t_it->first;
						t_jsonstring += "\":";
						t_jsonstring += (t_it->second)->ConvertJsonString();
						++t_it;

						//��ڈȍ~�B
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
		default:
			{
				//�s���B
				ASSERT(0);

				return "";
			}break;
		}

		//�s���B
		ASSERT(0);

		return "";
	}

	#endif
}

