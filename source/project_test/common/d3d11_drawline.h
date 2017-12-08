#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �R�����B�c�R�c�P�P�B���C���`��B
*/


/** include
*/
#include "../include.h"


/** NCommon
*/
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
	
	/** DrawLine_PS_ConstantBuffer_B0
	*/
	struct DrawLine_PS_ConstantBuffer_B0 //TODO:���g�p�B
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

		DrawLine_PS_ConstantBuffer_B0()
			:
			flag1(0),
			flag2(0),
			flag3(0),
			flag4(0)
		{
		}

		nonvirtual ~DrawLine_PS_ConstantBuffer_B0()
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
		s32 ps_constantbuffer_b0_id;
		s32 vertexbuffer_id;
		s32 blendstate_id;
		s32 rasterizerstate_cull_none_id;

		/** VertexItem
		*/
		struct VertexItem
		{
			f32 x;
			f32 y;
			f32 z;

			f32 r;
			f32 g;
			f32 b;
			f32 a;
		};

		/** vertex
		*/
		sharedptr<VertexItem> vertex_pointer;
		s32 vertex_stride;
		s32 vertex_allcountof;
		s32 vertex_index;

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

						t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,0,t_offset));
						t_offset += sizeof(f32) * 4;
					}

					//�V�F�[�_�[�B
					sharedptr<NBsys::NFile::File_Object> t_vertex_fx(new NBsys::NFile::File_Object(0,L"common/drawline_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					sharedptr<NBsys::NFile::File_Object> t_pixel_fx(new NBsys::NFile::File_Object(0,L"common/drawline_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
					this->asyncresult_vertexshader.Create(false);
					this->asyncresult_pixelshader.Create(false);
					this->vertexshader_id = this->d3d11->CreateVertexShader(this->asyncresult_vertexshader,t_vertex_fx,t_layout);
					this->pixelshader_id = this->d3d11->CreatePixelShader(this->asyncresult_pixelshader,t_pixel_fx);

					//�R���X�^���g�o�b�t�@�B
					this->vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(DrawLine_VS_ConstantBuffer_B0));
					this->ps_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(1,sizeof(DrawLine_PS_ConstantBuffer_B0));

					//�o�[�e�b�N�X�o�b�t�@�B
					this->vertex_allcountof = 2 * 1024;
					this->vertex_stride = sizeof(VertexItem);
					this->vertex_pointer.reset(new VertexItem[this->vertex_allcountof],default_delete<VertexItem[]>());
					this->vertexbuffer_id = this->d3d11->CreateVertexBuffer(this->vertex_pointer.get(),this->vertex_stride,0,this->vertex_allcountof,true);

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
					this->vertex_index = 0;
				}break;
			}
		}

		/** DrawLine
		*/
		void DrawLine(const NBsys::NGeometry::Geometry_Vector3& a_start,const NBsys::NGeometry::Geometry_Vector3& a_end,const NBsys::NColor::Color_F& a_color)
		{
			this->vertex_pointer.get()[this->vertex_index].x = a_start.x;
			this->vertex_pointer.get()[this->vertex_index].y = a_start.y;
			this->vertex_pointer.get()[this->vertex_index].z = a_start.z;
			this->vertex_pointer.get()[this->vertex_index].r = a_color.r;
			this->vertex_pointer.get()[this->vertex_index].g = a_color.g;
			this->vertex_pointer.get()[this->vertex_index].b = a_color.b;
			this->vertex_pointer.get()[this->vertex_index].a = a_color.a;
			this->vertex_index++;

			this->vertex_pointer.get()[this->vertex_index].x = a_end.x;
			this->vertex_pointer.get()[this->vertex_index].y = a_end.y;
			this->vertex_pointer.get()[this->vertex_index].z = a_end.z;
			this->vertex_pointer.get()[this->vertex_index].r = a_color.r;
			this->vertex_pointer.get()[this->vertex_index].g = a_color.g;
			this->vertex_pointer.get()[this->vertex_index].b = a_color.b;
			this->vertex_pointer.get()[this->vertex_index].a = a_color.a;
			this->vertex_index++;
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
					if(this->vertex_index > 0){
						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

						//�V�F�[�_�[�B
						this->d3d11->Render_VSSetShader(this->vertexshader_id);
						this->d3d11->Render_PSSetShader(this->pixelshader_id);

						//�g�|���W�[�B
						this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::LineList);

						//�u�����h�X�e�[�^�X�B
						this->d3d11->Render_SetBlendState(this->blendstate_id);

						//�R���X�^���g�o�b�t�@�B
						DrawLine_VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
						DrawLine_PS_ConstantBuffer_B0 t_ps_constantbuffer_b0;
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
						this->d3d11->Render_ReMapVertexBuffer(this->vertexbuffer_id,this->vertex_pointer.get(),this->vertex_index * this->vertex_stride);
						this->d3d11->Render_SetVertexBuffer(this->vertexbuffer_id);

						//�`��B
						this->d3d11->Render_Draw(this->vertex_index,0);
					}
				}break;
			}
		}

	};
}

