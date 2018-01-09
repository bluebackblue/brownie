#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu_mouse.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu_type.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4820)
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
			Position2DType<f32> offset;
			
			/** size
			*/
			WindowMenu_Size size;

			/** constructor
			*/
			InitItem()
				:
				mode(WindowMenu_Mode::Free),
				offset(),
				size()
			{
			}

			nonvirtual ~InitItem()
			{
			}
		};

	public:

		/** enable
		*/
		bool enable;

		/** type
		*/
		WindowMenu_WindowType::Id type;

		/** 親。
		*/
		WindowMenu_Window_Base* parent;

		/** child_list
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type child_list;

		/** name
		*/
		STLString name;

		/** 優先順位。
		*/
		s32 z_sort;

	public:

		/** モード。
		*/
		WindowMenu_Mode::Id mode;

		/** [設定値]自分の位置。
		*/
		Position2DType<f32> offset;

		/** [設定値]自分のサイズ。
		*/
		WindowMenu_Size size;

		/** 範囲外のマウスイベント通知。
		*/
		bool outrange_mouseevent;

		/** 描画する。
		*/
		bool draw_enable;

		/** 計算結果。
		*/
		bool calc_x_fix;
		bool calc_y_fix;
		bool calc_w_fix;
		bool calc_h_fix;

		/** 計算。
		*/
		Rect2DType_R<f32> calc_rect;

		/** 計算に必要な親が所持している自分のインデックス。
		*/
		s32 calc_child_index;

		/** 計算に必要な親が所持している自分のイテレータ。
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator calc_it;

	public:

		/** constructor
		*/
		WindowMenu_Window_Base(const STLString& a_name = "",WindowMenu_WindowType::Id a_type = NBsys::NWindowMenu::WindowMenu_WindowType::Custom);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Base();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);

		/** 子の追加。
		*/
		void AddChild(sharedptr<WindowMenu_Window_Base> a_window,s32 a_z_sort_add = 10);

		/** 子の作成。
		*/
		template <typename T> sharedptr<T> CreateChild(const STLString& a_name,s32 a_z_sort_add = 10)
		{
			sharedptr<T> t_window(new T(a_name));
			this->AddChild(t_window,a_z_sort_add);
			return t_window;
		}

		/** 子の削除。
		*/
		void RemoveChild(sharedptr<WindowMenu_Window_Base> a_window);

		/** 子を探す。
		*/
		const sharedptr<WindowMenu_Window_Base>& FindChild(const STLString& a_name) const;

		/** IsRange
		*/
		bool IsRange(const Position2DType<f32> a_pos);

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

		/** システムからのアクティブ変更処理。
		*/
		virtual void System_ChangeActive(bool a_active);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual void CallBack_Update();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

		/** アクティブ変更。
		*/
		virtual void CallBack_ChangeActive(bool a_active);

		/** 削除リクエスト。取得。
		*/
		virtual bool CallBack_GetDeleteRequest() const;

		/** 削除リクエスト。設定。
		*/
		virtual void CallBack_SetDeleteRequest();

		/** 計算結果のクリア。
		*/
		virtual void CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator a_it,s32 a_index);

	};


}}
#pragma warning(pop)
#endif

