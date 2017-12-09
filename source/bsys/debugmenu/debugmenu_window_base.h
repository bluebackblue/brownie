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
#include "../color/color.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** DebugMenu_Window_Base
	*/
	class DebugMenu_Window_Base
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
		DebugMenu_Window_Base* me;

		/** 親。
		*/
		DebugMenu_Window_Base* parent;

	public:
		/** モード。
		*/
		Mode::Id mode;

		/** child_list
		*/
		STLVector<sharedptr<DebugMenu_Window_Base>>::Type child_list;

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
		f32 z;

		/** [計算結果]自分の位置。
		*/
		f32 calc_x;
		f32 calc_y;

		/** [計算結果]自分のサイズ。
		*/
		f32 calc_w;
		f32 calc_h;

		/** [計算結果]親の位置。
		*/
		f32 calc_parent_x;
		f32 calc_parent_y;

	public:
		/** constructor
		*/
		DebugMenu_Window_Base();

		/** destructor
		*/
		virtual ~DebugMenu_Window_Base();

		/** Initialize
		*/
		void Initialize(Mode::Id a_mode,f32 a_offset_x,f32 a_offset_y,f32 a_width,f32 a_height,f32 a_z);

		/** CalcWidth
		*/
		f32 CalcWidth();

		/** CalcHeight
		*/
		f32 CalcHeight();

		/** CalcWidthFromParent
		*/
		f32 CalcWidthFromParent();

		/** CalcHeightFromParent
		*/
		f32 CalcHeightFromParent();

		/** CalcWidthFromChild
		*/
		f32 CalcWidthFromChild();

		/** CalcHeightFromChild
		*/
		f32 CalcHeightFromChild();

		/** AddChild
		*/
		void AddChild(const sharedptr<DebugMenu_Window_Base>& a_window);

		/** 表示位置計算。
		*/
		virtual void CalcRect(f32 a_parent_offset_x,f32 a_parent_offset_y);

		/** 更新。
		*/
		virtual void Update();

		/** 描画。
		*/
		virtual void Draw();

		/** 削除リクエスト。取得。
		*/
		virtual bool GetDeleteRequest();

		/** コールバック。親が接続された直後に呼び出される。
		*/
		virtual void CallBack_SetParent();
	};

}}

