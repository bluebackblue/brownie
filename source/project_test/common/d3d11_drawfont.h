#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。Ｄ３Ｄ１１。フォント描画。
*/


/** include
*/
#include "../include.h"


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
	
	/** DrawFont_PS_ConstantBuffer_B0
	*/
	struct DrawFont_PS_ConstantBuffer_B0 //TODO:未使用。
	{
		/**

		00000001 :
		00000010 :
		00000100 :
		00001000 :
		00010000 :
		00100000 :
		01000000 :
		10000000 :

		*/
		u32 flag1;

		/**

		00000001 :
		00000010 :
		00000100 :
		00001000 :
		00010000 :
		00100000 :
		01000000 :
		10000000 :

		*/
		u32 flag2;

		/**

		00000001 :
		00000010 :
		00000100 :
		00001000 :
		00010000 :
		00100000 :
		01000000 :
		10000000 :

		*/
		u32 flag3;

		/**

		00000001 :
		00000010 :
		00000100 :
		00001000 :
		00010000 :
		00100000 :
		01000000 :
		10000000 :

		*/
		u32 flag4;

		DrawFont_PS_ConstantBuffer_B0()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		nonvirtual ~DrawFont_PS_ConstantBuffer_B0()
		{
		}
	};

	/** D3d11_DrawFont_Manager
	*/
	class D3d11_DrawFont_Manager
	{
	private:
		/** step
		*/
		s32 step;

		/** isbusy
		*/
		bool isbusy;

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
		s32 ps_constantbuffer_b0_id;
		s32 blendstate_id;
		s32 rasterizerstate_cull_none_id;

		/** vertex
		*/
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>> vertex[3];
		s32 vertex_buffer_id[3];

	public:
		/** constructor
		*/
		D3d11_DrawFont_Manager(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
			:
			step(0),
			isbusy(true),
			d3d11(a_d3d11)
		{
		}

		/** destructor
		*/
		nonvirtual ~D3d11_DrawFont_Manager()
		{
		}

		/** IsBusy
		*/
		bool IsBusy()
		{
			return this->isbusy;
		}

		/** PreUpdate
		*/
		void PreUpdate()
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
					this->ps_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(1,sizeof(DrawFont_PS_ConstantBuffer_B0));

					//バーテックスバッファ。
					for(s32 ii=0;ii<COUNTOF(this->vertex);ii++){
						s32 t_vertex_allcountof = 2 * 1024;
						this->vertex[ii] = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>();
						this->vertex[ii]->AddParts("root");
						this->vertex[ii]->ReserveVertex(t_vertex_allcountof);

						NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex_dummy = {0};
						this->vertex[ii]->AddVertex(t_vertex_dummy);
						this->vertex_buffer_id[ii] = this->d3d11->CreateVertexBuffer(this->vertex[ii]->GetVertexPointer(),this->vertex[ii]->GetVertexStrideByte(),0,t_vertex_allcountof,true);
						this->vertex[ii]->ClearVertex();
					}

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
							this->isbusy = false;
						}
					}
				}break;
			case 2:
				{
					for(s32 ii=0;ii<COUNTOF(this->vertex);ii++){
						this->vertex[ii]->ClearVertex();
						this->d3d11->Render_DrawFont_StartClear(ii);
					}
				}break;
			}
		}

		/** DrawFont16
		*/
		void DrawFont16(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,f32 a_z,const NBsys::NColor::Color_F& a_color)
		{
			this->d3d11->Render_UpdateFontTexture(0,a_string);
			this->d3d11->Render_MakeFontVertex(0,a_string,this->vertex[0],a_x,a_y,a_z,a_font_size,a_color);
		}

		/** DrawFont32
		*/
		void DrawFont32(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,f32 a_z,const NBsys::NColor::Color_F& a_color)
		{
			this->d3d11->Render_UpdateFontTexture(1,a_string);
			this->d3d11->Render_MakeFontVertex(1,a_string,this->vertex[1],a_x,a_y,a_z,a_font_size,a_color);
		}

		/** DrawFont64
		*/
		void DrawFont64(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,f32 a_z,const NBsys::NColor::Color_F& a_color)
		{
			this->d3d11->Render_UpdateFontTexture(2,a_string);
			this->d3d11->Render_MakeFontVertex(2,a_string,this->vertex[2],a_x,a_y,a_z,a_font_size,a_color);
		}

		/** 描画。
		*/
		void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
		{
			if(this->isbusy == false){
				for(s32 ii=0;ii<COUNTOF(this->vertex);ii++){
					if(this->vertex[ii]->GetVertexCountOf(0) > 0){
						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

						//シェーダー。
						this->d3d11->Render_VSSetShader(this->vertexshader_id);
						this->d3d11->Render_PSSetShader(this->pixelshader_id);

						//テクスチャー設定。
						this->d3d11->Render_SetTexture(0,this->d3d11->Render_GetFontTexture(ii));

						//トポロジー。
						this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

						//ブレンドステータス。
						this->d3d11->Render_SetBlendState(this->blendstate_id);

						//コンスタントバッファ。
						DrawFont_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
						DrawFont_PS_ConstantBuffer_B0 t_ps_constantbuffer_b0;
						{
							t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();
						}

						//コンスタントバッファーの内容更新。
						this->d3d11->Render_UpdateSubresource(this->vs_constantbuffer_b0_id,&t_vs_constantbuffer_b0);
						this->d3d11->Render_UpdateSubresource(this->ps_constantbuffer_b0_id,&t_ps_constantbuffer_b0);

						//コンスタントバッファーをシェーダーに設定。
						this->d3d11->Render_VSSetConstantBuffers(this->vs_constantbuffer_b0_id);
						this->d3d11->Render_PSSetConstantBuffers(this->ps_constantbuffer_b0_id);

						//ラスタライザー。
						this->d3d11->Render_SetRasterizerState(this->rasterizerstate_cull_none_id);

						//バーテックスバッファ。
						this->d3d11->Render_ReMapVertexBuffer(this->vertex_buffer_id[ii],this->vertex[ii]->GetVertexPointer(),this->vertex[ii]->GetVertexStrideByte() * this->vertex[ii]->GetVertexCountOf(0));
						this->d3d11->Render_SetVertexBuffer(this->vertex_buffer_id[ii]);

						//描画。
						this->d3d11->Render_Draw(this->vertex[ii]->GetVertexCountOf(0),0);
					}
				}
			}
		}
	};
}
#endif

