#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NBlib
{
	/** JsonItem
	*/
	#if(BLIB_JSONITEM_ENABLE)
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
		
				StringData,				//文字データ。
				AssociativeArray,		//連想配列。
				IndexArray,				//インデックス配列。
				IntegerNumber,			//整数。
				FloatNumber,			//少数。
				BoolData,				//真偽データ。
				BinaryData,				//バイナリデータ。
		
				//中間計算用。
				Calc_UnknownNumber,		//数値（少数/整数）。
				Calc_BoolDataTrue,		//真。
				Calc_BoolDataFalse,		//偽。

			};
		};

		/** 文字データ。
		*/
		struct Value_StringData
		{
			STLString value;
			Value_StringData(const STLString& a_value)
				:
				value(a_value)
			{
			}
		};

		/** 連想配列。
		*/
		struct Value_AssociativeArray
		{
		};

		/** インデックス配列。
		*/
		struct Value_IndexArray
		{
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

		/** 真偽データ。
		*/
		struct Value_BoolData
		{
			bool value;
			explicit Value_BoolData(bool a_value)
				:
				value(a_value)
			{
			}
		};

		/** バイナリデータ。
		*/
		struct Value_BinaryData
		{
			sharedptr<STLVector<u8>::Type> value;
			Value_BinaryData(const sharedptr<STLVector<u8>::Type>& a_value)
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

			/** 文字データ。
			*/
			sharedptr<STLString> string_data;

			/** 連想配列。
			*/
			sharedptr<STLMap<STLString,sharedptr<JsonItem>>::Type> associative_array;

			/** インデックス配列。
			*/
			sharedptr<STLVector<sharedptr<JsonItem>>::Type> index_array;

			/** 整数。
			*/
			s32 integer_number;

			/** 少数。
			*/
			f32 float_number;

			/** 真偽データ。
			*/
			bool bool_data;

			/** padding
			*/
			padding64(0,7);
			padding32(0,3);

			/** バイナリ―。
			*/
			sharedptr<STLVector<u8>::Type> binary_data;

			/** リセット。
			*/
			void Reset()
			{
				this->string_data.reset();
				this->associative_array.reset();
				this->index_array.reset();
				this->integer_number = 0;
				this->float_number = 0.0f;
				this->bool_data = false;
				this->binary_data.reset();
			}
		};

		/** ＪＳＯＮ文字列。
		*/
		mutable sharedptr<STLString> jsonstring;

		/** バリアント型。タイプ。
		*/
		ValueType::Id valuetype;

		/** padding
		*/
		padding64(0,4);

		/** バリアント型。
		*/
		mutable StValue value;

	private:

		/** 確保。
		*/
		static void* Alloc(std::size_t a_size);

		/** 解放。
		*/
		static void Free(void* a_pointer);

	public:

		/** operator new
		*/
		#if defined(custom_new)

		#undef new

		static void* operator new(std::size_t a_size,const char* a_file,s32 a_line) noexcept
		{
			UNUSED(a_file);
			UNUSED(a_line);

			return JsonItem::Alloc(a_size);
		}

		#define new custom_new

		#else
		static void* operator new(size_t a_size) noexcept
		{
			return JsonItem::Alloc(a_size);
		}
		#endif

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
		JsonItem(const Value_BoolData& a_value);

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

		/** [取得][値]GetBoolData
		*/
		bool GetBoolData() const;

		/** [取得][値]GetBinaryData
		*/
		sharedptr<STLVector<u8>::Type>& GetBinaryData();

		/** [取得]GetValueType
		*/
		ValueType::Id GetValueType() const;

		/** タイプチェック。文字データ。
		*/
		bool IsStringData();

		/** タイプチェック。連想配列。
		*/
		bool IsAssociativeArray();

		/** タイプチェック。インデックス配列。
		*/
		bool IsIndexArray();

		/** タイプチェック。整数。
		*/
		bool IsIntegerNumber();

		/** タイプチェック。少数。
		*/
		bool IsFloatNumber();

		/** タイプチェック。真偽データ。
		*/
		bool IsBoolData();

		/** タイプチェック。バイナリデータ。
		*/
		bool IsBinaryData();

		/** [取得]連想リストのアイテム取得。
		*/
		sharedptr<JsonItem>& GetItem(const STLString& a_itemname);

		/** [取得]連想リストのアイテム取得。
		*/
		const sharedptr<JsonItem>& GetItem(const STLString& a_itemname) const;

		/** [取得]連想リストのアイテムチェック。
		*/
		bool IsExistItem(const STLString& a_itemname,ValueType::Id a_valuetype = ValueType::None) const;
	
		/** [取得]インデックスリストのアイテム取得。
		*/
		sharedptr<JsonItem>& GetItem(s32 a_index);

		/** [取得]インデックスリストのアイテム取得。
		*/
		const sharedptr<JsonItem>& GetItem(s32 a_index) const;

		/** [取得]インデックスリストのアイテムチェック。
		*/
		bool IsExistItem(s32 a_index,ValueType::Id a_valuetype = ValueType::None);
	
		/** [設定]連想リストにアイテム追加。削除。
		*/
		void SetItem(const STLString& a_itemname,const sharedptr<JsonItem>& a_item,bool a_deepcopy);
	
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

		/** [設定]真偽データセット。
		*/
		void SetBoolData(bool a_bool);
	
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
#pragma warning(pop)

