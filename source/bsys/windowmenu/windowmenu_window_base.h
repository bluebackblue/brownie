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


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_Window_Base
	*/
	class WindowMenu_Window_Base
	{
	public:
		/** Mode
		*/
		struct Mode
		{
			enum Id
			{
				//自由配置。
				Free,

				//縦。
				Vertical,

				//横。
				Horizontal,
			};
		};

	public:
		/** 自分。
		*/
		WindowMenu_Window_Base* me;

		/** 親。
		*/
		WindowMenu_Window_Base* parent;

	public:
		/** モード。
		*/
		Mode::Id mode;

		/** child_list
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type child_list;

		/** name
		*/
		STLString name;

		/** [設定値]自分の位置。
		*/
		f32 offset_x;
		f32 offset_y;

		/** [設定値]自分のサイズ。
		*/
		f32 width;
		f32 height;

		/** 描画優先度。
		*/
		s32 z;

		/** [計算結果]自分の位置。
		*/
		f32 calc_x;
		f32 calc_y;

		/** [計算結果]自分のサイズ。
		*/
		f32 calc_w;
		f32 calc_h;

		/** 計算に必要な親が所持している自分のイテレータ。
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator calc_it;

		/** 計算に必要な親が所持している自分のインデックス。
		*/
		s32 calc_child_index;

	public:
		/** constructor
		*/
		WindowMenu_Window_Base(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Base();

	public:
		/** Initialize

		a_width : 負の値を設定した場合は自動計算。
		a_height : 負の値を設定した場合は自動計算。

		*/
		void Initialize(Mode::Id a_mode,f32 a_offset_x,f32 a_offset_y,f32 a_width,f32 a_height,s32 a_z);

		/** 子の追加。
		*/
		void AddChild(sharedptr<WindowMenu_Window_Base>& a_window);

		/** 子の削除。
		*/
		void RemoveChild(sharedptr<WindowMenu_Window_Base>& a_window);

		/** IsRange
		*/
		bool IsRange(f32 a_x,f32 a_y);

	public:
		/** システムからのマウス再起処理。
		*/
		virtual bool System_MouseUpdate(WindowMenu_Mouse& a_mouse);

		/** システムからの更新処理。
		*/
		virtual void System_Update();

		/** システムからの描画処理。
		*/
		virtual void System_Draw();

		/** マウス処理。
		*/
		virtual bool CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual bool CallBack_Update();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw();

		/** 削除リクエスト。取得。
		*/
		virtual bool GetDeleteRequest();

		/** 削除リクエスト。設定。
		*/
		virtual void SetDeleteRequest();

		/** 計算結果のクリア。
		*/
		virtual void CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator a_it,s32 a_index);

		/** サイズ計算。
		*/
		static void CalcRect(WindowMenu_Window_Base* a_window);

		/** サイズ計算。
		*/
		static void CalcX(WindowMenu_Window_Base* a_window);

		/** サイズ計算。
		*/
		static void CalcY(WindowMenu_Window_Base* a_window);

		/** サイズ計算。
		*/
		static void CalcW(WindowMenu_Window_Base* a_window);

		/** サイズ計算。
		*/
		static void CalcH(WindowMenu_Window_Base* a_window);
	};
}}

