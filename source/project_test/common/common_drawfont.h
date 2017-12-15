#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。フォント描画。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./common_render2d.h"


/** NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NCommon
{
	/** DrawFont_VS_ConstantBuffer_B0
	*/
	struct DrawFont_VS_ConstantBuffer_B0
	{
		NBsys::NGeometry::Geometry_Matrix_44 view_projection;

		DrawFont_VS_ConstantBuffer_B0()
			:
			view_projection(NBsys::NGeometry::Geometry_Identity())
		{
		}

		nonvirtual ~DrawFont_VS_ConstantBuffer_B0()
		{
		}
	};
	
	/** DrawFont_PS_ConstantBuffer_B1
	*/
	struct DrawFont_PS_ConstantBuffer_B1 //TODO:未使用。
	{
		/**

		00000000 00000000 00000000 00000001 :

		*/
		u32 flag1;

		/**

		00000000 00000000 00000000 00000001 :

		*/
		u32 flag2;

		/**

		00000000 00000000 00000000 00000001 :

		*/
		u32 flag3;

		/**

		00000000 00000000 00000000 00000001 :

		*/
		u32 flag4;

		float w;
		float h;
		u32 dummy1;
		u32 dummy2;

		DrawFont_PS_ConstantBuffer_B1()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0),
			w(1.0f),
			h(1.0f)
		{
		}

		nonvirtual ~DrawFont_PS_ConstantBuffer_B1()
		{
		}
	};

	/** DrawFont_Material
	*/
	class DrawFont_Material : public Render2D_Material_Base
	{
	private:
		/** step
		*/
		s32 step;

		/** is_initialized
		*/
		bool is_initialized;

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

		/** font
		*/
		sharedptr<NBsys::NFont::Font> font16;
		sharedptr<NBsys::NFont::Font> font32;
		sharedptr<NBsys::NFont::Font> font64;

		/** asyncresult
		*/
		AsyncResult<bool> asyncresult_vertexshader;
		AsyncResult<bool> asyncresult_pixelshader;

		/** id
		*/
		s32 vertexshader_id;
		s32 pixelshader_id;
		s32 vs_constantbuffer_b0_id;
		s32 ps_constantbuffer_b1_id;
		s32 blendstate_id;
		s32 rasterizerstate_cull_none_id;

		/** vertex
		*/
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>> vertex;
		s32 vertex_buffer_id;

	public:
		/** constructor
		*/
		DrawFont_Material(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
			:
			step(0),
			is_initialized(false),
			d3d11(a_d3d11)
		{
		}

		/** destructor
		*/
		nonvirtual ~DrawFont_Material()
		{
		}

		/** 初期化。
		*/
		virtual void Initialize_Update()
		{
			switch(this->step){
			case 0:
				{
					this->font16.reset(new NBsys::NFont::Font(L"Arial",14));
					this->d3d11->Render_SetFont(0,this->font16,16,L"font16");

					this->font32.reset(new NBsys::NFont::Font(L"Arial",28));
					this->d3d11->Render_SetFont(1,this->font32,32,L"font32");

					this->font64.reset(new NBsys::NFont::Font(L"Arial",60));
					this->d3d11->Render_SetFont(2,this->font64,64,L"font64");

					//レイアウト。
					sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type> t_layout(new STLVector<NBsys::ND3d11::D3d11_Layout>::Type());
					{
						s32 t_offset = 0;

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32_FLOAT,0,t_offset));
						t_offset += sizeof(f32) * 3;

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("TEXCOORD",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32_FLOAT,0,t_offset));
						t_offset += sizeof(f32) * 2;

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,0,t_offset));
						t_offset += sizeof(f32) * 4;

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",0,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));
						t_offset += sizeof(u8);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",1,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));
						t_offset += sizeof(u8);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",2,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));
						t_offset += sizeof(u8);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",3,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));
						t_offset += sizeof(u8);
					}

					//シェーダー。
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(0,L"common/drawfont_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(0,L"common/drawfont_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//コンスタントバッファ。
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawFont_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b1_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawFont_PS_ConstantBuffer_B1));

					//バーテックスバッファ。
					s32 t_vertex_allcountof = 1024 * 1024;
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>();
					this->vertex->AddParts("root");
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4 t_vertex_dummy = {0};
					this->vertex->AddVertex(t_vertex_dummy);
					this->vertex_buffer_id = this->d3d11->CreateVertexBuffer(this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte(),0,t_vertex_allcountof,true);
					this->vertex->ClearVertex();

					//ブレンドステータス。
					this->blendstate_id = this->d3d11->CreateBlendState(true);

					//ラスタライザー。
					this->rasterizerstate_cull_none_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::NONE);

					this->step++;
				}break;
			case 1:
				{
					if(this->asyncresult_vertexshader.Get() == true){
						if(this->asyncresult_pixelshader.Get() == true){
							this->step++;
							this->is_initialized = true;
						}
					}
				}break;
			}
		}

		/** 初期化チェック。
		*/
		virtual bool IsInitialized()
		{
			return this->is_initialized;
		}

		/** 描画。
		*/
		virtual void PreRenderOnce(STLList<Render2D_Item>::Type& a_list)
		{
			STLList<Render2D_Item>::iterator t_it_end = a_list.end();
			for(STLList<Render2D_Item>::const_iterator t_it = a_list.begin();t_it != t_it_end;t_it++){
				if(t_it->data.type == Render2D_Item::Type::Font){
					//フォントテクスチャー更新。
					this->d3d11->Render_UpdateFontTexture(t_it->data.texture_index,t_it->data.string);
				}
			}

			this->d3d11->Render_WriteFontTexture(0);
			this->d3d11->Render_WriteFontTexture(1);
			this->d3d11->Render_WriteFontTexture(2);
		}

		/** 描画。
		*/
		virtual void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection,STLList<Render2D_Item>::const_iterator a_it_start,STLList<Render2D_Item>::const_iterator a_it_end)
		{
			auto t_minus = [](f32 a_value) -> f32{
				if(a_value >= 0.0f){
					return a_value;
				}
				return -1.0f;
			};

			f32 t_current_clip_x = -1;
			f32 t_current_clip_y = -1;
			f32 t_current_clip_w = -1;
			f32 t_current_clip_h = -1;

			STLList<Render2D_Item>::const_iterator t_it = a_it_start;
			STLList<Render2D_Item>::const_iterator t_it_renderstart = t_it;
			if(t_it != a_it_end){
				t_current_clip_x = t_minus(t_it->data.x);
				t_current_clip_y = t_minus(t_it->data.y);
				t_current_clip_w = t_minus(t_it->data.w);
				t_current_clip_h = t_minus(t_it->data.h);
			}

			while(t_it != a_it_end){

				if((t_minus(t_it->data.x) != t_current_clip_x)||(t_minus(t_it->data.y) != t_current_clip_y)||(t_minus(t_it->data.w) != t_current_clip_w)||(t_minus(t_it->data.h) != t_current_clip_h)){
					this->RenderCall(a_view_projection,t_it_renderstart,t_it);

					t_current_clip_x = t_minus(t_it->data.x);
					t_current_clip_y = t_minus(t_it->data.y);
					t_current_clip_w = t_minus(t_it->data.w);
					t_current_clip_h = t_minus(t_it->data.h);

					t_it_renderstart = t_it;
				}

				t_it++;
			}

			if(t_it_renderstart != a_it_end){
				this->RenderCall(a_view_projection,t_it_renderstart,a_it_end);
			}
		}

		/** 描画。
		*/
		void RenderCall(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection,STLList<Render2D_Item>::const_iterator a_it_start,STLList<Render2D_Item>::const_iterator a_it_end)
		{
			f32 t_scale_w = 1.0f;
			f32 t_scale_h = 1.0f;
			f32 t_viewport_offset_x = 0.0f;
			f32 t_viewport_offset_y = 0.0f;
			f32 t_viewport_w = a_it_start->data.w;
			f32 t_viewport_h = a_it_start->data.h;

			if((t_viewport_w > 0.0f)&&(t_viewport_h > 0.0f)){
				t_viewport_offset_x = a_it_start->data.x;
				t_viewport_offset_y = a_it_start->data.y;

				t_scale_w = this->d3d11->GetWidth() / t_viewport_w;
				t_scale_h = this->d3d11->GetHeight() / t_viewport_h;

				//ビューポート。
				this->d3d11->Render_ViewPort(
					t_viewport_offset_x,
					t_viewport_offset_y,
					t_viewport_w,
					t_viewport_h
				);
			}else{
				//ビューポート。
				this->d3d11->Render_ViewPort(
					0,
					0,
					static_cast<f32>(this->d3d11->GetWidth()),
					static_cast<f32>(this->d3d11->GetHeight())
				);
			}

			//バーテックスクリア。
			this->vertex->ClearVertex();

			this->d3d11->Render_DrawFont_StartClear(0);
			this->d3d11->Render_DrawFont_StartClear(1);
			this->d3d11->Render_DrawFont_StartClear(2);

			for(STLList<Render2D_Item>::const_iterator t_it = a_it_start;t_it != a_it_end;t_it++){
				//フォントテクスチャー更新。
				this->d3d11->Render_UpdateFontTexture(t_it->data.texture_index,t_it->data.string);

				//バーテックス作成。
				this->d3d11->Render_MakeFontVertex(
					t_it->data.texture_index,
					t_it->data.string,
					this->vertex,
					t_it->data.x - t_viewport_offset_x,
					t_it->data.y - t_viewport_offset_y,
					0.0f,
					t_it->data.size * t_scale_w,
					t_it->data.size * t_scale_h,
					t_it->data.color
				);
			}

			if(this->vertex->GetVertexCountOf(0) > 0){
				NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

				//シェーダー。
				this->d3d11->Render_VSSetShader(this->vertexshader_id);
				this->d3d11->Render_PSSetShader(this->pixelshader_id);

				//テクスチャー設定。
				this->d3d11->Render_SetTexture(0,this->d3d11->Render_GetFontTexture(0));
				this->d3d11->Render_SetTexture(1,this->d3d11->Render_GetFontTexture(1));
				this->d3d11->Render_SetTexture(2,this->d3d11->Render_GetFontTexture(2));

				//トポロジー。
				this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

				//ブレンドステータス。
				this->d3d11->Render_SetBlendState(this->blendstate_id);

				//コンスタントバッファ。
				DrawFont_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
				DrawFont_PS_ConstantBuffer_B1 t_ps_constantbuffer_b1;
				{
					t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();
					t_ps_constantbuffer_b1.w = static_cast<f32>(this->d3d11->GetWidth());
					t_ps_constantbuffer_b1.h = static_cast<f32>(this->d3d11->GetHeight());
				}

				//コンスタントバッファーの内容更新。
				this->d3d11->Render_UpdateSubresource(this->vs_constantbuffer_b0_id,&t_vs_constantbuffer_b0);
				this->d3d11->Render_UpdateSubresource(this->ps_constantbuffer_b1_id,&t_ps_constantbuffer_b1);

				//コンスタントバッファーをシェーダーに設定。
				this->d3d11->Render_VSSetConstantBuffers(this->vs_constantbuffer_b0_id);
				this->d3d11->Render_PSSetConstantBuffers(this->ps_constantbuffer_b1_id);

				//ラスタライザー。
				this->d3d11->Render_SetRasterizerState(this->rasterizerstate_cull_none_id);

				//バーテックスバッファ。
				this->d3d11->Render_ReMapVertexBuffer(this->vertex_buffer_id,this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte() * this->vertex->GetVertexCountOf(0));
				this->d3d11->Render_SetVertexBuffer(this->vertex_buffer_id);

				//描画。
				this->d3d11->Render_Draw(this->vertex->GetVertexCountOf(0),0);
			}
		}
	};
}
#endif

