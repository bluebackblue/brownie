﻿#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。Ｄ３Ｄ１１。ライン描画。
*/


/** include
*/
#include "../include.h"


/** NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NCommon
{
	/** DrawLine_VS_ConstantBuffer_B0
	*/
	struct DrawLine_VS_ConstantBuffer_B0
	{
		NBsys::NGeometry::Geometry_Matrix_44 view_projection;

		DrawLine_VS_ConstantBuffer_B0()
			:
			view_projection(NBsys::NGeometry::Geometry_Identity())
		{
		}

		nonvirtual ~DrawLine_VS_ConstantBuffer_B0()
		{
		}
	};
	
	/** DrawLine_PS_ConstantBuffer_B1
	*/
	struct DrawLine_PS_ConstantBuffer_B1 //TODO:未使用。
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

		DrawLine_PS_ConstantBuffer_B1()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		nonvirtual ~DrawLine_PS_ConstantBuffer_B1()
		{
		}
	};

	/** D3d11_DrawLine_Manager
	*/
	class D3d11_DrawLine_Manager
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
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Color4>> vertex;
		s32 vertex_buffer_id;

	public:
		/** constructor
		*/
		D3d11_DrawLine_Manager(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
			:
			step(0),
			isbusy(true),
			d3d11(a_d3d11)
		{
		}

		/** destructor
		*/
		nonvirtual ~D3d11_DrawLine_Manager()
		{
		}

		/** IsBusy
		*/
		bool IsBusy()
		{
			return this->isbusy;
		}

		/** Initialize_Update
		*/
		void Initialize_Update()
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

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,0,t_offset));
						t_offset += sizeof(f32) * 4;
					}

					//シェーダー。
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(0,L"common/drawline_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(0,L"common/drawline_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//コンスタントバッファ。
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawLine_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b1_id = this->d3d11->CreateConstantBuffer(1,sizeof(DrawLine_PS_ConstantBuffer_B1));

					//バーテックスバッファ。
					s32 t_vertex_allcountof = 2 * 1024;
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Color4>();
					this->vertex->AddParts("root");
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Color4 t_vertex_dummy = {0};
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
							this->isbusy = false;
						}
					}
				}break;
			}
		}

		/** クリア。
		*/
		void Clear()
		{
			this->vertex->ClearVertex();
		}

		/** DrawLine
		*/
		void DrawLine(const NBsys::NGeometry::Geometry_Vector3& a_start,const NBsys::NGeometry::Geometry_Vector3& a_end,const NBsys::NColor::Color_F& a_color)
		{
			NBsys::NVertex::Vertex_Data_Pos3Color4 t_vector;

			t_vector.color_rr = a_color.r; 
			t_vector.color_gg = a_color.g;
			t_vector.color_bb = a_color.b;
			t_vector.color_aa = a_color.a;

			//00
			{
				t_vector.pos_xx = a_start.x;
				t_vector.pos_yy = a_start.y;
				t_vector.pos_zz = a_start.z;

				this->vertex->AddVertex(t_vector);
			}

			//10
			{
				t_vector.pos_xx = a_end.x;
				t_vector.pos_yy = a_end.y;
				t_vector.pos_zz = a_end.z;

				this->vertex->AddVertex(t_vector);
			}
		}

		/** 描画。
		*/
		void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
		{
			if(this->isbusy == false){
				if(this->vertex->GetVertexCountOf(0) > 0){
					NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

					//シェーダー。
					this->d3d11->Render_VSSetShader(this->vertexshader_id);
					this->d3d11->Render_PSSetShader(this->pixelshader_id);

					//トポロジー。
					this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::LineList);

					//ブレンドステータス。
					this->d3d11->Render_SetBlendState(this->blendstate_id);

					//コンスタントバッファ。
					DrawLine_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
					DrawLine_PS_ConstantBuffer_B1 t_ps_constantbuffer_b1;
					{
						t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();
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
		}

	};
}
#endif

