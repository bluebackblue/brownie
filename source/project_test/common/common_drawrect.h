#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。レクト描画。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** include
*/
#include "./common_render2d.h"


/** NTest::NCommon
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NTest{namespace NCommon
{
	/** DrawRect_VS_ConstantBuffer_B0
	*/
	struct DrawRect_VS_ConstantBuffer_B0
	{
		NBsys::NGeometry::Geometry_Matrix_44 view_projection;

		DrawRect_VS_ConstantBuffer_B0()
			:
			view_projection(NBsys::NGeometry::Geometry_Identity())
		{
		}

		nonvirtual ~DrawRect_VS_ConstantBuffer_B0()
		{
		}
	};
	
	/** DrawRect_PS_ConstantBuffer_B0
	*/
	struct DrawRect_PS_ConstantBuffer_B0
	{
		/**

		00000000 00000000 00000000 00000001 : use texture
		00000000 00000000 00000000 00000010 :
		00000000 00000000 00000000 00000100 :
		00000000 00000000 00000000 00001000 :
		00000000 00000000 00000000 00010000 :
		00000000 00000000 00000000 00100000 :
		00000000 00000000 00000000 01000000 :
		00000000 00000000 00000000 10000000 :

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

		DrawRect_PS_ConstantBuffer_B0()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		nonvirtual ~DrawRect_PS_ConstantBuffer_B0()
		{
		}
	};


	/** DrawRect_Material
	*/
	class DrawRect_Material : public Render2D_Material_Base
	{
	private:
		/** step
		*/
		s32 step;

		/** is_initialized
		*/
		bool is_initialized;

		/** padding
		*/
		padding64(0,3);
		padding32(0,3);

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

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
		s32 samplerstate_id;
		s32 rasterizerstate_cull_none_id;

		/** padding
		*/
		padding64(1,4);

		/** vertex
		*/
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>> vertex;
		s32 vertex_buffer_id;

		/** padding
		*/
		padding64(2,4);

	public:
		/** constructor
		*/
		DrawRect_Material(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
			:
			step(0),
			is_initialized(false),
			d3d11(a_d3d11),
			asyncresult_vertexshader(),
			asyncresult_pixelshader(),
			vertexshader_id(-1),
			pixelshader_id(-1),
			vs_constantbuffer_b0_id(-1),
			ps_constantbuffer_b0_id(-1),
			blendstate_id(-1),
			samplerstate_id(-1),
			rasterizerstate_cull_none_id(-1),
			vertex(),
			vertex_buffer_id(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~DrawRect_Material()
		{
		}

		/** 初期化。
		*/
		virtual void Initialize_Update()
		{
			switch(this->step){
			case 0:
				{
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
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(1,L"drawrect_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(1,L"drawrect_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//コンスタントバッファ。
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawRect_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawRect_PS_ConstantBuffer_B0));

					//バーテックスバッファ。
					s32 t_vertex_allcountof = 2 * 1024;
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>();
					this->vertex->AddParts("root");
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex_dummy = {0};
					this->vertex->AddVertex(t_vertex_dummy);
					this->vertex_buffer_id = this->d3d11->CreateVertexBuffer(this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte(),0,t_vertex_allcountof,true);
					this->vertex->ClearVertex();

					//ブレンドステート。
					this->blendstate_id = this->d3d11->CreateBlendState(true);

					//サンプラーステート。
					{
						NBsys::ND3d11::D3d11_Sampler t_sampler;
						{
							t_sampler.textureaddrestype_u = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
							t_sampler.textureaddrestype_v = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
							t_sampler.textureaddrestype_w = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
							t_sampler.filtertype = NBsys::ND3d11::D3d11_FilterType::MIN_MAG_MIP_POINT;
						}
						this->samplerstate_id = this->d3d11->CreateSamplerState(t_sampler);
					}

					//ラスタライザー。
					this->rasterizerstate_cull_none_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

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
		virtual void PreRenderOnce(STLList<sharedptr<Render2D_Item_Base>>::Type& /*a_list*/)
		{
		}

		/** 描画。
		*/
		virtual void Render(STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_start,STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_end)
		{
			s32 t_current_texture_id = -1;

			auto t_it = a_it_start;
			auto t_it_renderstart = t_it;
			if(t_it != a_it_end){
				const Render2D_Item_Rect* t_instence = dynamic_cast<const Render2D_Item_Rect*>(t_it->get());

				t_current_texture_id = t_instence->texture_id;
			}

			while(t_it != a_it_end){
				const Render2D_Item_Rect* t_instence = dynamic_cast<const Render2D_Item_Rect*>(t_it->get());

				if(t_instence->texture_id != t_current_texture_id){
					this->RenderCall(t_it_renderstart,t_it);

					t_current_texture_id = t_instence->texture_id;
					t_it_renderstart = t_it;
				}

				t_it++;
			}

			if(t_it_renderstart != a_it_end){
				this->RenderCall(t_it_renderstart,a_it_end);
			}
		}

		/** 描画。
		*/
		void RenderCall(STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_start,STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_end)
		{
			//ビューポート。
			this->d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(this->d3d11->GetWidth()),static_cast<f32>(this->d3d11->GetHeight()));

			//バーテックスクリア。
			this->vertex->ClearVertex();

			const Render2D_Item_Rect* t_instence_start = dynamic_cast<const Render2D_Item_Rect*>(a_it_start->get());

			s32 t_texture_id = t_instence_start->texture_id;

			for(auto t_it = a_it_start;t_it != a_it_end;t_it++){
				const Render2D_Item_Rect* t_instence = dynamic_cast<const Render2D_Item_Rect*>(t_it->get());

				//バーテックス作成。

				NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vector;

				t_vector.color_rr = t_instence->color.r(); 
				t_vector.color_gg = t_instence->color.g();
				t_vector.color_bb = t_instence->color.b();
				t_vector.color_aa = t_instence->color.a();

				//00
				{
					t_vector.pos_xx = t_instence->x;
					t_vector.pos_yy = t_instence->y;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//10
				{
					t_vector.pos_xx = t_instence->x + t_instence->w;
					t_vector.pos_yy = t_instence->y;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 1.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//01
				{
					t_vector.pos_xx = t_instence->x;
					t_vector.pos_yy = t_instence->y + t_instence->h;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 1.0f;

					this->vertex->AddVertex(t_vector);
				}

				//01
				{
					t_vector.pos_xx = t_instence->x;
					t_vector.pos_yy = t_instence->y + t_instence->h;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 1.0f;

					this->vertex->AddVertex(t_vector);
				}

				//10
				{
					t_vector.pos_xx = t_instence->x + t_instence->w;
					t_vector.pos_yy = t_instence->y;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 1.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//11
				{
					t_vector.pos_xx = t_instence->x + t_instence->w;
					t_vector.pos_yy = t_instence->y + t_instence->h;
					t_vector.pos_zz = 0.0f;

					t_vector.uv_xx = 1.0f;
					t_vector.uv_yy = 1.0f;

					this->vertex->AddVertex(t_vector);
				}
			}

			if(this->vertex->GetVertexCountOf(0) > 0){
				NBsys::NGeometry::Geometry_Matrix_44 t_view_projection;
				t_view_projection.Set_OrthographicProjectionMatrix(0,static_cast<f32>(this->d3d11->GetWidth()),0,static_cast<f32>(this->d3d11->GetHeight()),0.0f,1.0f);

				//シェーダー。
				this->d3d11->Render_VSSetShader(this->vertexshader_id);
				this->d3d11->Render_PSSetShader(this->pixelshader_id);

				//トポロジー。
				this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

				//ブレンドステート。
				this->d3d11->Render_SetBlendState(this->blendstate_id);

				//サンプラーステート。
				this->d3d11->Render_SetSamplerState(0,this->samplerstate_id);

				//コンスタントバッファ。
				DrawRect_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
				DrawRect_PS_ConstantBuffer_B0 t_ps_constantbuffer_b0;
				{
					t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();

					if(t_texture_id >= 0){
						t_ps_constantbuffer_b0.flag1 = 0x00000001;
					}else{
						t_ps_constantbuffer_b0.flag1 = 0x00000000;
					}
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
				this->d3d11->Render_ReMapVertexBuffer(this->vertex_buffer_id,this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte() * this->vertex->GetVertexCountOf(0));
				this->d3d11->Render_SetVertexBuffer(this->vertex_buffer_id);

				//テクスチャー設定。
				if(t_texture_id >= 0){
					this->d3d11->Render_SetTexture(0,t_texture_id);
				}else{
					this->d3d11->Render_SetTexture(0,-1);
				}

				//描画。
				this->d3d11->Render_Draw(this->vertex->GetVertexCountOf(0),0);
			}
		}

	};


}}
#pragma warning(pop)
#endif

