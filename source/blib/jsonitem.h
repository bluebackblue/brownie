#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＪＳＯＮアイテム。
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
		
				StringData,			//文字データ。
				AssociativeArray,	//連想配列。
				IndexArray,			//インデックス配列。
				UnknownNumber,		//数値（少数/整数）。
				IntegerNumber,		//整数。
				FloatNumber,		//少数。
		
				BoolDataTrue,		//真。
				BoolDataFalse,		//偽。

				BinaryData,			//バイナリデータ。
			};
		};

		/** 文字データ。
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

		/** 連想配列。
		*/
		struct Value_AssociativeArray
		{
			explicit Value_AssociativeArray()
			{
			}
		};

		/** インデックス配列。
		*/
		struct Value_IndexArray
		{
			explicit Value_IndexArray()
			{
			}
		};

		/** 整数。
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

		/** 整数。
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

		/** 少数。
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

		/** Bool。
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
		/** バリアント型。
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

			/** リセット。
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

		/** ＪＳＯＮ文字列。
		*/
		mutable sharedptr<STLString> jsonstring;

		/** バリアント型。タイプ。
		*/
		ValueType::Id valuetype;

		/** バリアント型。
		*/
		mutable StValue value;

	private:

		/** 確保。
		*/
		static void* Alloc(size_t a_size);

		/** 解放。
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

		/** ディープコピー。
		*/
		sharedptr<JsonItem> DeepCopy() const;
	
		/** ＪＳＯＮ文字列をセット。
		*/
		void SetJsonString(const STLString& a_jsonstring);

	private:
		/** 値化。
		*/
		void JsonStringToValue() const;

	public:
		/** [取得]GetListMax
		*/
		s32 GetListMax() const;
	
		/** [取得][値]GetStringData
		*/
		const sharedptr<STLString>& GetStringData() const;
	
		/** [取得][値]GetInteger
		*/
		s32 GetInteger() const;
	
		/** [取得][値]GetUnsignedInteger
		*/
		u32 GetUnsignedInteger() const;

		/** [取得][値]GetFloat
		*/
		f32 GetFloat() const;

		/** [取得][値]GetBool
		*/
		bool GetBool() const;

		/** [取得][値]GetBinaryData
		*/
		sharedptr<STLVector<u8>::Type>& GetBinaryData();

		/** [取得]GetValueType
		*/
		ValueType::Id GetValueType() const;

		/** [取得]連想リストのアイテム取得。
		*/
		sharedptr<JsonItem>& GetItem(const STLString& a_itemname);

		/** [取得]連想リストのアイテム取得。
		*/
		const sharedptr<JsonItem>& GetItem(const STLString& a_itemname) const;

		/** [取得]連想リストのアイテムチェック。
		*/
		bool IsExistItem(const STLString& a_itemname);
	
		/** [取得]インデックスリストのアイテム取得。
		*/
		sharedptr<JsonItem>& GetItem(s32 a_index);

		/** [取得]インデックスリストのアイテム取得。
		*/
		const sharedptr<JsonItem>& GetItem(s32 a_index) const;

		/** [取得]インデックスリストのアイテムチェック。
		*/
		bool IsExistItem(s32 a_index);
	
		/** [設定]連想リストにアイテム追加。削除。
		*/
		void SetItem(const STLString& a_itemname,sharedptr<JsonItem>& a_item,bool a_deepcopy);
	
		/** [設定]インデックスリストにアイテム追加。
		*/
		void AddItem(const sharedptr<JsonItem>& a_item,bool a_deepcopy);
	
		/** [削除]インデックスリストからアイテム削除。
		*/
		void RemoveItem(s32 a_index);
	
		/** [設定]文字データ。
		*/
		void SetStringData(const STLString& a_string);
	
		/** [設定]空連想リスト。
		*/
		void SetAssociativeArray();
	
		/** [設定]空インデックスリスト。
		*/
		void SetIndexArray();
	
		/** [設定]整数セット。
		*/
		void SetInteger(s32 a_integer);

		/** [設定]整数セット。
		*/
		void SetUnsignedInteger(u32 a_unsignedinteger);
	
		/** [設定]少数セット。
		*/
		void SetFloat(f32 a_float);

		/** [設定]Boolセット。
		*/
		void SetBool(bool a_bool);
	
		/** SetBinaryData
		*/
		void SetBinaryData(const sharedptr<STLVector<u8>::Type>& a_binarydata);

		/** 連想配列キーリスト作成。
		*/
		sharedptr<STLVector<STLString>::Type> CreateAssociativeKeyList();

		/** JsonStringへコンバート。
		*/
		const STLString ConvertJsonString() const;

	};

	#endif

}


