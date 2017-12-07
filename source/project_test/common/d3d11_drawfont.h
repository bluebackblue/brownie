#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �R�����B�c�R�c�P�P�B�t�H���g�`��B
*/


/** include
*/
#include "../include.h"


/** NCommon
*/
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

		~DrawFont_VS_ConstantBuffer_B0()
		{
		}
	};
	
	/** DrawFont_PS_ConstantBuffer_B0
	*/
	struct DrawFont_PS_ConstantBuffer_B0 //TODO:���g�p�B
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
		u32 flag2;
		u32 flag3;
		u32 flag4;

		DrawFont_PS_ConstantBuffer_B0()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		~DrawFont_PS_ConstantBuffer_B0()
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

		/** fontindex
		*/
		s32 fontindex;

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
		s32 vertexbuffer_id;
		s32 blendstate_id;
		s32 rasterizerstate_cull_none_id;

		/** vertex
		*/
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>> vertex;

	public:
		/** constructor
		*/
		D3d11_DrawFont_Manager(sharedptr<NBsys::ND3d11::D3d11>& a_d3d11,s32 a_fontindex)
			:
			step(0),
			isbusy(true),
			d3d11(a_d3d11),
			fontindex(a_fontindex)
		{
		}

		/** destructor
		*/
		~D3d11_DrawFont_Manager()
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
					//���C�A�E�g�B
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

					//�V�F�[�_�[�B
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(0,L"common/drawfont_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(0,L"common/drawfont_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//�R���X�^���g�o�b�t�@�B
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawFont_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(1,sizeof(DrawFont_PS_ConstantBuffer_B0));

					//�o�[�e�b�N�X�o�b�t�@�B
					this->vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>();
					this->vertex->AddParts("root");
					s32 t_vertex_allcountof = 2 * 1024;
					this->vertex->ReserveVertex(t_vertex_allcountof);

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex_dummy = {0};
					this->vertex->AddVertex(t_vertex_dummy);
					this->vertexbuffer_id = this->d3d11->CreateVertexBuffer(this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte(),0,t_vertex_allcountof,true);
					this->vertex->ClearVertex();

					//�u�����h�X�e�[�^�X�B
					this->blendstate_id = this->d3d11->CreateBlendState(true);

					//���X�^���C�U�[�B
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
					this->vertex->ClearVertex();
				}break;
			}
		}

		/** DrawFont
		*/
		void DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color)
		{
			this->d3d11->Render_UpdateFontTexture(this->fontindex,a_string);
			this->d3d11->Render_MakeFontVertex(this->fontindex,a_string,this->vertex,a_x,a_y,a_font_size,a_color);
		}

		/** �X�V�B
		*/
		void Update(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
		{
			switch(this->step){
			case 0:
				{
				}break;
			case 1:
				{
				}break;
			case 2:
				{
					if(this->vertex.get()){
						if(this->vertex->GetVertexCountOf(0) > 0){
							NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

							//�V�F�[�_�[�B
							this->d3d11->Render_VSSetShader(this->vertexshader_id);
							this->d3d11->Render_PSSetShader(this->pixelshader_id);

							//�e�N�X�`���[�ݒ�B
							this->d3d11->Render_SetTexture(0,this->d3d11->Render_GetFontTexture(this->fontindex));

							//�g�|���W�[�B
							this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);

							//�u�����h�X�e�[�^�X�B
							this->d3d11->Render_SetBlendState(this->blendstate_id);

							//�R���X�^���g�o�b�t�@�B
							DrawFont_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
							DrawFont_PS_ConstantBuffer_B0 t_ps_constantbuffer_b0;
							{
								t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();
							}

							//�R���X�^���g�o�b�t�@�[�̓��e�X�V�B
							this->d3d11->Render_UpdateSubresource(this->vs_constantbuffer_b0_id,&t_vs_constantbuffer_b0);
							this->d3d11->Render_UpdateSubresource(this->ps_constantbuffer_b0_id,&t_ps_constantbuffer_b0);

							//�R���X�^���g�o�b�t�@�[���V�F�[�_�[�ɐݒ�B
							this->d3d11->Render_VSSetConstantBuffers(this->vs_constantbuffer_b0_id);
							this->d3d11->Render_PSSetConstantBuffers(this->ps_constantbuffer_b0_id);

							//���X�^���C�U�[�B
							this->d3d11->Render_SetRasterizerState(this->rasterizerstate_cull_none_id);

							//�o�[�e�b�N�X�o�b�t�@�B
							this->d3d11->Render_ReMapVertexBuffer(this->vertexbuffer_id,this->vertex->GetVertexPointer(),this->vertex->GetVertexStrideByte() * this->vertex->GetVertexCountOf(0));
							this->d3d11->Render_SetVertexBuffer(this->vertexbuffer_id);

							//�`��B
							this->d3d11->Render_Draw(this->vertex->GetVertexCountOf(0),0);
						}
					}
				}break;
			}
		}

	};
}

