#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。レクト描画。
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
	
	/** DrawRect_PS_ConstantBuffer_B1
	*/
	struct DrawRect_PS_ConstantBuffer_B1
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

		DrawRect_PS_ConstantBuffer_B1()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		nonvirtual ~DrawRect_PS_ConstantBuffer_B1()
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
		s32 ps_constantbuffer_b1_id;
		s32 blendstate_id;
		s32 rasterizerstate_cull_none_id;

		/** vertex
		*/
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>> vertex;
		s32 vertex_buffer_id;

	public:
		/** constructor
		*/
		DrawRect_Material(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
			:
			step(0),
			is_initialized(false),
			d3d11(a_d3d11)
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
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(0,L"common/drawrect_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(0,L"common/drawrect_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//コンスタントバッファ。
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawRect_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b1_id = this->d3d11->CreateConstantBuffer(1,sizeof(DrawRect_PS_ConstantBuffer_B1));

					//バーテックスバッファ。
					s32 t_vertex_allcountof = 2 * 1024;
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>();
					this->vertex->AddParts("root");
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex_dummy = {0};
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
		virtual void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection,STLList<Render2D_Item>::const_iterator a_it_start,STLList<Render2D_Item>::const_iterator a_it_end)
		{
			//バーテックスクリア。
			this->vertex->ClearVertex();

			for(STLList<Render2D_Item>::const_iterator t_it = a_it_start;t_it != a_it_end;t_it++){
				
				//バーテックス作成。

				NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vector;

				t_vector.color_rr = t_it->data.color.r; 
				t_vector.color_gg = t_it->data.color.g;
				t_vector.color_bb = t_it->data.color.b;
				t_vector.color_aa = t_it->data.color.a;

				//00
				{
					t_vector.pos_xx = t_it->data.x;
					t_vector.pos_yy = t_it->data.y;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//10
				{
					t_vector.pos_xx = t_it->data.x + t_it->data.w;
					t_vector.pos_yy = t_it->data.y;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//01
				{
					t_vector.pos_xx = t_it->data.x;
					t_vector.pos_yy = t_it->data.y + t_it->data.h;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//01
				{
					t_vector.pos_xx = t_it->data.x;
					t_vector.pos_yy = t_it->data.y + t_it->data.h;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//10
				{
					t_vector.pos_xx = t_it->data.x + t_it->data.w;
					t_vector.pos_yy = t_it->data.y;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}

				//11
				{
					t_vector.pos_xx = t_it->data.x + t_it->data.w;
					t_vector.pos_yy = t_it->data.y + t_it->data.h;
					t_vector.pos_zz = static_cast<f32>(t_it->data.z);

					t_vector.uv_xx = 0.0f;
					t_vector.uv_yy = 0.0f;

					this->vertex->AddVertex(t_vector);
				}
			}

			if(this->vertex->GetVertexCountOf(0) > 0){
				NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

				//シェーダー。
				this->d3d11->Render_VSSetShader(this->vertexshader_id);
				this->d3d11->Render_PSSetShader(this->pixelshader_id);

				//トポロジー。
				this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

				//ブレンドステータス。
				this->d3d11->Render_SetBlendState(this->blendstate_id);

				//コンスタントバッファ。
				DrawRect_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
				DrawRect_PS_ConstantBuffer_B1 t_ps_constantbuffer_b1;
				{
					t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();
					t_ps_constantbuffer_b1.flag1 = 0x00000000;
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

