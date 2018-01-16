#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。フォント描画。
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
#include "./common_device_index.h"


/** NTest::NCommon
*/
#if((BSYS_D3D11_ENABLE)&&(BSYS_FONT_ENABLE))
#pragma warning(push)
#pragma warning(disable:4514 4710 4820)
namespace NTest{namespace NCommon
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
	struct DrawFont_PS_ConstantBuffer_B0
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

		/** dummy
		*/
		u32 dummy1;
		u32 dummy2;
		u32 dummy3;
		u32 dummy4;

		DrawFont_PS_ConstantBuffer_B0()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0),
			dummy1(0),
			dummy2(0),
			dummy3(0),
			dummy4(0)
		{
		}

		nonvirtual ~DrawFont_PS_ConstantBuffer_B0()
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
		s32 ps_constantbuffer_b0_id;
		s32 blendstate_id;
		s32 sampler_id;
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
			d3d11(a_d3d11),

			font16(),
			font32(),
			font64(),

			asyncresult_vertexshader(),
			asyncresult_pixelshader(),
			vertexshader_id(-1),
			pixelshader_id(-1),
			vs_constantbuffer_b0_id(-1),
			ps_constantbuffer_b0_id(-1),
			blendstate_id(-1),
			sampler_id(-1),
			rasterizerstate_cull_none_id(-1),
			vertex(),
			vertex_buffer_id(-1)
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
					this->d3d11->Render_SetFont(NBsys::ND3d11::D3d11_FontTextureType::SFont,this->font16,16,L"font16");

					this->font32.reset(new NBsys::NFont::Font(L"Arial",28));
					this->d3d11->Render_SetFont(NBsys::ND3d11::D3d11_FontTextureType::MFont,this->font32,32,L"font32");

					this->font64.reset(new NBsys::NFont::Font(L"Arial",60));
					this->d3d11->Render_SetFont(NBsys::ND3d11::D3d11_FontTextureType::LFont,this->font64,64,L"font64");

					//レイアウト。
					sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type> t_layout(new STLVector<NBsys::ND3d11::D3d11_Layout>::Type());
					{
						s32 t_offset = 0;

						t_offset = NBsys::NVertex::GetOffset_Position<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>();
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32_FLOAT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_Uv<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>();
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("TEXCOORD",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32_FLOAT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_Color<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>();
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_TextureIndex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>(0);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",0,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_TextureIndex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>(1);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",1,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_TextureIndex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>(2);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",2,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));

						t_offset = NBsys::NVertex::GetOffset_TextureIndex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>(3);
						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("BLENDINDICES",3,NBsys::ND3d11::D3d11_LayoutFormatType::R8_UINT,0,t_offset));
					}

					//シェーダー。
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(DeviceIndex::Common,L"drawfont_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(DeviceIndex::Common,L"drawfont_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//コンスタントバッファ。
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawFont_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawFont_PS_ConstantBuffer_B0));

					//バーテックスバッファ。
					s32 t_vertex_allcountof = 1024 * 1024;
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>();
					this->vertex->AddParts("root");
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4 t_vertex_dummy = {0};
					this->vertex->AddVertex(t_vertex_dummy);
					this->vertex_buffer_id = this->d3d11->CreateVertexBuffer(this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte(),0,t_vertex_allcountof,true);
					this->vertex->ClearVertex();

					//ブレンドスステート。
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
						this->sampler_id = this->d3d11->CreateSamplerState(t_sampler);
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
		virtual void PreRenderOnce(STLList<sharedptr<Render2D_Item_Base>>::Type& a_list)
		{
			bool t_cahnge_list[NBsys::ND3d11::D3d11_FontTextureType::Max] = {true};

			auto t_it_end = a_list.cend();
			for(auto t_it = a_list.cbegin();t_it != t_it_end;t_it++){
				if((*t_it)->itemtype == Render2D_ItemType::Font){
					const Render2D_Item_Font* t_instence = dynamic_cast<const Render2D_Item_Font*>(t_it->get());
					ASSERT(t_instence != nullptr);
					
					//フォントテクスチャー更新。
					bool t_cahnge = this->d3d11->Render_PreUpdateFontTexture(t_instence->fonttexture_type,t_instence->string);
					if(t_cahnge == true){
						t_cahnge_list[t_instence->fonttexture_type] = true;
					}
				}
			}

			//フォントテクスチャー書き込み。
			if(t_cahnge_list[NBsys::ND3d11::D3d11_FontTextureType::SFont]){
				this->d3d11->Render_WriteFontTexture(NBsys::ND3d11::D3d11_FontTextureType::SFont);
			}
			if(t_cahnge_list[NBsys::ND3d11::D3d11_FontTextureType::MFont]){
				this->d3d11->Render_WriteFontTexture(NBsys::ND3d11::D3d11_FontTextureType::MFont);
			}
			if(t_cahnge_list[NBsys::ND3d11::D3d11_FontTextureType::LFont]){
				this->d3d11->Render_WriteFontTexture(NBsys::ND3d11::D3d11_FontTextureType::LFont);
			}
			if(t_cahnge_list[NBsys::ND3d11::D3d11_FontTextureType::ExFont]){
				this->d3d11->Render_WriteFontTexture(NBsys::ND3d11::D3d11_FontTextureType::ExFont);
			}
		}

		/** 描画。
		*/
		virtual void Render(STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_start,STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_end)
		{
			auto t_clip_proc = [](bool a_clip,Rect2DType_R<f32> a_rect) -> Rect2DType_R<f32>{
				if(a_clip){
					return a_rect;
				}
				return Rect2DType_R<f32>(-1.0f,-1.0f,-1.0f,-1.0f);
			};

			Rect2DType_R<f32> t_current_clip(-1.0f,-1.0f,-1.0f,-1.0f);

			auto t_it = a_it_start;
			auto t_it_renderstart = t_it;
			if(t_it != a_it_end){
				const Render2D_Item_Font* t_instence = dynamic_cast<const Render2D_Item_Font*>(t_it->get());
				ASSERT(t_instence != nullptr);

				t_current_clip = t_clip_proc(t_instence->clip,t_instence->rect);
			}

			while(t_it != a_it_end){
				const Render2D_Item_Font* t_instence = dynamic_cast<const Render2D_Item_Font*>(t_it->get());
				ASSERT(t_instence != nullptr);

				Rect2DType_R<f32> t_instance_rect = t_clip_proc(t_instence->clip,t_instence->rect);

				if(
					(t_instance_rect.xx != t_current_clip.xx)||
					(t_instance_rect.yy != t_current_clip.yy)||
					(t_instance_rect.ww != t_current_clip.ww)||
					(t_instance_rect.hh != t_current_clip.hh)
				){
					this->RenderCall(t_it_renderstart,t_it);

					t_current_clip = t_instance_rect;

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
			const Render2D_Item_Font* t_instence_start = dynamic_cast<const Render2D_Item_Font*>(a_it_start->get());
			ASSERT(t_instence_start != nullptr);

			Rect2DType_R<f32> t_viewport(0.0f,0.0f,this->d3d11->GetSize().ww,this->d3d11->GetSize().hh);

			if(t_instence_start->clip == true){
				//クリップ処理あり。
				t_viewport = t_instence_start->rect;
			}

			//ビューポート。
			this->d3d11->Render_ViewPort(t_viewport);

			//バーテックスクリア。
			this->vertex->ClearVertex();

			this->d3d11->Render_DrawFont_ClearLockFlag(NBsys::ND3d11::D3d11_FontTextureType::SFont);
			this->d3d11->Render_DrawFont_ClearLockFlag(NBsys::ND3d11::D3d11_FontTextureType::MFont);
			this->d3d11->Render_DrawFont_ClearLockFlag(NBsys::ND3d11::D3d11_FontTextureType::LFont);
			this->d3d11->Render_DrawFont_ClearLockFlag(NBsys::ND3d11::D3d11_FontTextureType::ExFont);

			for(auto t_it = a_it_start;t_it != a_it_end;t_it++){
				const Render2D_Item_Font* t_instence = dynamic_cast<const Render2D_Item_Font*>(t_it->get());
				ASSERT(t_instence != nullptr);

				NBsys::ND3d11::D3d11_FontTextureType::Id t_fonttexture_type = t_instence->fonttexture_type;

				//フォントテクスチャー更新。
				this->d3d11->Render_PreUpdateFontTexture(t_fonttexture_type,t_instence->string);

				Rect2DType_R<f32> t_viewrect = t_instence->rect - Rect2DType_R<f32>(t_viewport.xx,t_viewport.yy,0.0f,0.0f);

				//バーテックス作成。
				this->d3d11->Render_MakeFontVertex(
					t_fonttexture_type,
					t_instence->string,
					this->vertex,
					t_viewrect,
					t_instence->alignment,
					0.0f,
					Size2DType<f32>(t_instence->size,t_instence->size),
					t_instence->color
				);
			}

			if(this->vertex->GetVertexCountOf(0) > 0){
				NBsys::NGeometry::Geometry_Matrix_44 t_view_projection;
				t_view_projection.Set_OrthographicProjectionMatrix(0,t_viewport.ww,0,t_viewport.hh,0.0f,1.0f);

				//シェーダー。
				this->d3d11->Render_VSSetShader(this->vertexshader_id);
				this->d3d11->Render_PSSetShader(this->pixelshader_id);

				//トポロジー。
				this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

				//ブレンドステート。
				this->d3d11->Render_SetBlendState(this->blendstate_id);

				//サンプラーステート。
				this->d3d11->Render_SetSamplerState(0,this->sampler_id);

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
				this->d3d11->Render_ReMapVertexBuffer(this->vertex_buffer_id,this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte() * this->vertex->GetVertexCountOf(0));
				this->d3d11->Render_SetVertexBuffer(this->vertex_buffer_id);

				//テクスチャー設定。
				this->d3d11->Render_SetTexture(0,this->d3d11->Render_GetFontTexture(NBsys::ND3d11::D3d11_FontTextureType::SFont));
				this->d3d11->Render_SetTexture(1,this->d3d11->Render_GetFontTexture(NBsys::ND3d11::D3d11_FontTextureType::MFont));
				this->d3d11->Render_SetTexture(2,this->d3d11->Render_GetFontTexture(NBsys::ND3d11::D3d11_FontTextureType::LFont));
				this->d3d11->Render_SetTexture(3,this->d3d11->Render_GetFontTexture(NBsys::ND3d11::D3d11_FontTextureType::ExFont));

				//描画。
				this->d3d11->Render_Draw(this->vertex->GetVertexCountOf(0),0);
			}
		}
	};


}}
#pragma warning(pop)
#endif

