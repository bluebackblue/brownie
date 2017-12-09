#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �i�r�n�m�A�C�e���B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./stlvector.h"
#include "./stlmap.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	#if(BLIB_JSONITEM_ENABLE)

	/** JsonItem
	*/
	class JsonItem
	{
	public:
		/** ValueType
		*/
		struct ValueType
		{
			enum Id
			{
				None = 0,
		
				StringData,			//�����f�[�^�B
				AssociativeArray,	//�A�z�z��B
				IndexArray,			//�C���f�b�N�X�z��B
				UnknownNumber,		//���l�i����/�����j�B
				IntegerNumber,		//�����B
				FloatNumber,		//�����B
		
				BoolDataTrue,		//�^�B
				BoolDataFalse,		//�U�B

				BinaryData,			//�o�C�i���f�[�^�B
			};
		};

		/** �����f�[�^�B
		*/
		struct Value_StringData
		{
			STLString value;
			explicit Value_StringData(const STLString a_value)
				:
				value(a_value)
			{
			}
		};

		/** �A�z�z��B
		*/
		struct Value_AssociativeArray
		{
			explicit Value_AssociativeArray()
			{
			}
		};

		/** �C���f�b�N�X�z��B
		*/
		struct Value_IndexArray
		{
			explicit Value_IndexArray()
			{
			}
		};

		/** �����B
		*/
		struct Value_Integer
		{
			s32 value;
			explicit Value_Integer(s32 a_value)
				:
				value(a_value)
			{
			}
		};

		/** �����B
		*/
		struct Value_UnsignedInteger
		{
			s32 value;
			explicit Value_UnsignedInteger(u32 a_value)
				:
				value(static_cast<s32>(a_value))
			{
			}
		};

		/** �����B
		*/
		struct Value_Float
		{
			f32 value;
			explicit Value_Float(f32 a_value)
				:
				value(a_value)
			{
			}
		};

		/** Bool�B
		*/
		struct Value_Bool
		{
			bool value;
			explicit Value_Bool(bool a_value)
				:
				value(a_value)
			{
			}
		};

		/** Value_BinaryData
		*/
		struct Value_BinaryData
		{
			sharedptr<STLVector<u8>::Type> value;
			explicit Value_BinaryData(sharedptr<STLVector<u8>::Type>& a_value)
				:
				value(a_value)
			{
			}
		};

	private:
		/** �o���A���g�^�B
		*/
		class StValue
		{
		public:

			sharedptr<STLString>										string_data;
			sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type>		associative_array;
			sharedptr<STLVector<sharedptr<JsonItem>>::Type>				index_array;
			s32															integer_number;
			f32															float_number;
			bool														bool_value;
			sharedptr<STLVector<u8>::Type>								binary_data;

			/** ���Z�b�g�B
			*/
			void Reset()
			{
				this->string_data.reset();
				this->associative_array.reset();
				this->index_array.reset();
				this->integer_number = 0;
				this->float_number = 0.0f;
				this->bool_value = false;
				this->binary_data.reset();
			}
		};

		/** �i�r�n�m������B
		*/
		mutable sharedptr<STLString> jsonstring;

		/** �o���A���g�^�B�^�C�v�B
		*/
		ValueType::Id valuetype;

		/** �o���A���g�^�B
		*/
		mutable StValue value;

	private:

		/** �m�ہB
		*/
		static void* Alloc(size_t a_size);

		/** ����B
		*/
		static void Free(void* a_pointer);

	public:

		/** operator new
		*/
		static void* operator new(size_t a_size) noexcept
		{
			return JsonItem::Alloc(a_size);
		}
		
		/** operator delete
		*/
		static void operator delete(void* a_pointer)
		{
			JsonItem::Free(a_pointer);
		}

	public:
		/** constructor
		*/
		JsonItem();

		/** constructor
		*/
		JsonItem(const STLString& a_jsonstring);

		/** constructor
		*/
		JsonItem(const Value_StringData& a_value);

		/** constructor
		*/
		JsonItem(const Value_AssociativeArray& /*a_value*/);
		
		/** constructor
		*/
		JsonItem(const Value_IndexArray& /*a_value*/);

		/** constructor
		*/
		JsonItem(const Value_Integer& a_value);

		/** constructor
		*/
		JsonItem(const Value_UnsignedInteger& a_value);

		/** constructor
		*/
		JsonItem(const Value_Float& a_value);

		/** constructor
		*/
		JsonItem(const Value_Bool& a_value);

		/** constructor
		*/
		JsonItem(const Value_BinaryData& a_value);

		/** �f�B�[�v�R�s�[�B
		*/
		sharedptr<JsonItem> DeepCopy() const;
	
		/** �i�r�n�m��������Z�b�g�B
		*/
		void SetJsonString(const STLString& a_jsonstring);

	private:
		/** �l���B
		*/
		void JsonStringToValue() const;

	public:
		/** [�擾]GetListMax
		*/
		s32 GetListMax() const;
	
		/** [�擾][�l]GetStringData
		*/
		const sharedptr<STLString>& GetStringData() const;
	
		/** [�擾][�l]GetInteger
		*/
		s32 GetInteger() const;
	
		/** [�擾][�l]GetUnsignedInteger
		*/
		u32 GetUnsignedInteger() const;

		/** [�擾][�l]GetFloat
		*/
		f32 GetFloat() const;

		/** [�擾][�l]GetBool
		*/
		bool GetBool() const;

		/** [�擾][�l]GetBinaryData
		*/
		sharedptr<STLVector<u8>::Type>& GetBinaryData();

		/** [�擾]GetValueType
		*/
		ValueType::Id GetValueType() const;

		/** [�擾]�A�z���X�g�̃A�C�e���擾�B
		*/
		sharedptr<JsonItem>& GetItem(const STLString& a_itemname);

		/** [�擾]�A�z���X�g�̃A�C�e���擾�B
		*/
		const sharedptr<JsonItem>& GetItem(const STLString& a_itemname) const;

		/** [�擾]�A�z���X�g�̃A�C�e���`�F�b�N�B
		*/
		bool IsExistItem(const STLString& a_itemname);
	
		/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���擾�B
		*/
		sharedptr<JsonItem>& GetItem(s32 a_index);

		/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���擾�B
		*/
		const sharedptr<JsonItem>& GetItem(s32 a_index) const;

		/** [�擾]�C���f�b�N�X���X�g�̃A�C�e���`�F�b�N�B
		*/
		bool IsExistItem(s32 a_index);
	
		/** [�ݒ�]�A�z���X�g�ɃA�C�e���ǉ��B�폜�B
		*/
		void SetItem(const STLString& a_itemname,sharedptr<JsonItem>& a_item,bool a_deepcopy);
	
		/** [�ݒ�]�C���f�b�N�X���X�g�ɃA�C�e���ǉ��B
		*/
		void AddItem(const sharedptr<JsonItem>& a_item,bool a_deepcopy);
	
		/** [�폜]�C���f�b�N�X���X�g����A�C�e���폜�B
		*/
		void RemoveItem(s32 a_index);
	
		/** [�ݒ�]�����f�[�^�B
		*/
		void SetStringData(const STLString& a_string);
	
		/** [�ݒ�]��A�z���X�g�B
		*/
		void SetAssociativeArray();
	
		/** [�ݒ�]��C���f�b�N�X���X�g�B
		*/
		void SetIndexArray();
	
		/** [�ݒ�]�����Z�b�g�B
		*/
		void SetInteger(s32 a_integer);

		/** [�ݒ�]�����Z�b�g�B
		*/
		void SetUnsignedInteger(u32 a_unsignedinteger);
	
		/** [�ݒ�]�����Z�b�g�B
		*/
		void SetFloat(f32 a_float);

		/** [�ݒ�]Bool�Z�b�g�B
		*/
		void SetBool(bool a_bool);
	
		/** SetBinaryData
		*/
		void SetBinaryData(const sharedptr<STLVector<u8>::Type>& a_binarydata);

		/** �A�z�z��L�[���X�g�쐬�B
		*/
		sharedptr<STLVector<STLString>::Type> CreateAssociativeKeyList();

		/** JsonString�փR���o�[�g�B
		*/
		const STLString ConvertJsonString() const;

	};

	#endif

}


