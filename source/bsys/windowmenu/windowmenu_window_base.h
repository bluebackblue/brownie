#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./windowmenu_mouse.h"


/** include
*/
#include "../color/color.h"


/** include
*/
#include "./windowmenu_type.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_Window_Base
	*/
	class WindowMenu_Window_Base
	{
	public:
		/** InitItem
		*/
		struct InitItem
		{
			/** mode
			*/
			WindowMenu_Mode::Id mode;

			/** offset
			*/
			WindowMenu_Offset offset;
			
			/** size
			*/
			WindowMenu_Size size;

			/** z_sort
			*/
			s32 z_sort;

			/** constructor
			*/
			InitItem()
				:
				mode(WindowMenu_Mode::Free),
				offset(WindowMenu_Offset(0.0f,0.0f)),
				size(WindowMenu_Size(WindowMenu_SizeType::Fix,0.0f,WindowMenu_SizeType::Fix,0.0f))
			{
			}

			/** constructor
			*/
			InitItem(WindowMenu_Mode::Id a_mode,const WindowMenu_Offset& a_offset,const WindowMenu_Size& a_size,s32 a_z_sort)
				:
				mode(a_mode),
				offset(a_offset),
				size(a_size),
				z_sort(a_z_sort)
			{
			}

			nonvirtual ~InitItem()
			{
			}
		};

	public:
		/** 親。
		*/
		WindowMenu_Window_Base* parent;

	public:
		/** モード。
		*/
		WindowMenu_Mode::Id mode;

		/** child_list
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type child_list;

		/** name
		*/
		STLString name;

		/** [設定値]自分の位置。
		*/
		WindowMenu_Offset offset;

		/** [設定値]自分のサイズ。
		*/
		WindowMenu_Size size;

		/** [設定値]優先順位。
		*/
		s32 z_sort;

		/** 計算結果。
		*/
		bool calc_x_fix;
		bool calc_y_fix;
		bool calc_w_fix;
		bool calc_h_fix;
		f32 calc_x;
		f32 calc_y;
		f32 calc_w;
		f32 calc_h;


		/** 計算に必要な親が所持している自分のインデックス。
		*/
		s32 calc_child_index;

		/** 計算に必要な親が所持している自分のイテレータ。
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator calc_it;

	public:
		/** constructor
		*/
		WindowMenu_Window_Base(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Base();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);

		/** 子の追加。
		*/
		void AddChild(sharedptr<WindowMenu_Window_Base> a_window,s32 a_z_sort_add = 10);

		/** 子の削除。
		*/
		void RemoveChild(sharedptr<WindowMenu_Window_Base> a_window);

		/** IsRange
		*/
		bool IsRange(f32 a_x,f32 a_y);

		/** サイズ計算。
		*/
		void CalcRect();

		/** サイズ計算。
		*/
		void CalcX(WindowMenu_SizeType::Id a_from_sizetype);

		/** サイズ計算。
		*/
		void CalcY(WindowMenu_SizeType::Id a_from_sizetype);

		/** サイズ計算。
		*/
		void CalcW(WindowMenu_SizeType::Id a_from_sizetype);

		/** サイズ計算。
		*/
		void CalcH(WindowMenu_SizeType::Id a_from_sizetype);

	public:
		/** システムからのマウス再起処理。
		*/
		virtual bool System_MouseUpdate(WindowMenu_Mouse& a_mouse);

		/** システムからの更新処理。
		*/
		virtual void System_Update();

		/** システムからの描画処理。
		*/
		virtual void System_Draw(s32 a_z_sort);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual bool CallBack_Update();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

		/** アクティブ変更。
		*/
		virtual void CallBack_ChangeActive(bool a_active);

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest();

		/** 削除リクエスト。設定。
		*/
		virtual void CallBack_SetDeleteRequest();

		/** 計算結果のクリア。
		*/
		virtual void CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator a_it,s32 a_index);
	};
}}

