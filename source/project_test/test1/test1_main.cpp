

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief インクルード。
*/


/** include
*/
#include "../entry.h"


/** Test0_Main
*/
#if defined(DEF_TEST1)


/** include
*/
#include "./test1_main.h"


/** include
*/
#include "../bsys/d3d11/d3d11_impl.h"


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
void Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,s32 a_line)
{
}
#endif


/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
void Blib_DebugBreak_Callback()
{
}
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
void Blib_DebugLog_Callback(const char* a_tag,const char* a_string)
{
}
#endif


/** s_window
*/
static sharedptr< NBsys::NWindow::Window > s_window;

/** s_d3d11
*/
static sharedptr< NBsys::ND3d11::D3d11 > s_d3d11;

//s_vertex
static sharedptr< NBsys::NModel::Model_Vertex< NBsys::NModel::Model_Vertex_Data_Pos4Color3 > > s_vertex;

/** s_clear_color
*/
static NBsys::NColor::Color_F s_clear_color(0.0f,0.5f,0.5f,1.0f);


/** Test_Main
*/
void Test_Main()
{
	TAGLOG("main","DEF_TEST1");

	s_window.reset(new NBsys::NWindow::Window());
	s_window->Create(L"sample",800,600);

	s_d3d11.reset(new NBsys::ND3d11::D3d11());
	s_d3d11->Render_Create(s_window,800,600);

	s_vertex = NBsys::NModel::Preset_Box< NBsys::NModel::Model_Vertex_Data_Pos4Color3 >();


	sharedptr< ID3D11Buffer > t_vertexbuffer;
	s32 t_vertexbuffer_stride;
	s32 t_vertexbuffer_offset;
	s32 t_vertexbuffer_countofvertex;
	{
		t_vertexbuffer_stride = s_vertex->GetVertexStrideByte();
		t_vertexbuffer_offset = s_vertex->GetVertexOffset(0);
		t_vertexbuffer_countofvertex = s_vertex->GetVertexCountOf(0);

		D3D11_BUFFER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = s_vertex->GetVertexAllCountOf() * s_vertex->GetVertexStrideByte();
			t_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			t_desc.CPUAccessFlags = 0;
		}

		D3D11_SUBRESOURCE_DATA t_subresource_data;
		{
			ZeroMemory(&t_subresource_data,sizeof(t_subresource_data));
			t_subresource_data.pSysMem = s_vertex->GetVertexPointer();
		}

		ID3D11Buffer* t_raw;
		HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreateBuffer(&t_desc,&t_subresource_data,&t_raw);
		if(t_raw != nullptr){
			t_vertexbuffer.reset(t_raw,release_delete< ID3D11Buffer >());
		}
		if(FAILED(t_result)){
			t_vertexbuffer.reset();
		}
	}

	sharedptr< ID3D11VertexShader > t_vertex_shader;
	sharedptr< ID3D11InputLayout > t_vertex_layout;
	{
		STLString t_vertex_source = 
			"float4x4 modelView;"
			"struct VSI {"
				"float4 p : POSITION0;"
				"float3 c : COLOR;"
			"};"
			"struct VSO {"
				"float4 p : SV_POSITION;"
				"float3 c : COLOR;"
			"};"
			"VSO VS(VSI i) {"
				"VSO ret;"
				"ret.p = mul(i.p, modelView);"
				"ret.c = i.c;"
				"return ret;"
			"}";

		sharedptr< ID3DBlob > t_blob;
		{
			sharedptr< ID3DBlob > t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_vertex_source.c_str(),t_vertex_source.size(),nullptr,nullptr,nullptr,"VS","vs_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete< ID3DBlob >());
			}
			if(t_raw != nullptr){
				t_blob_error.reset(t_raw_error,release_delete< ID3DBlob >());
			}
			if(FAILED(t_result)){
				t_blob.reset();
			}

			if(t_blob != nullptr){
			}else{
				std::string t_errorstring;
				if(t_blob_error != nullptr){
					t_errorstring = std::string((const char*)t_blob_error->GetBufferPointer(),t_blob_error->GetBufferSize());
				}
				TAGLOG("compile vertex","FAILED");
				TAGLOG("compile vertex",t_errorstring.c_str());
			}

			t_blob_error.reset();
		}

		
		{
			ID3D11VertexShader* t_raw = nullptr;
			HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreateVertexShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				t_vertex_shader.reset(t_raw,release_delete< ID3D11VertexShader >());
			}
			if(FAILED(t_result)){
				t_vertex_shader.reset();
			}
		}

		{
			D3D11_INPUT_ELEMENT_DESC t_layout[] = {
				{	"POSITION",		0,	DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA,	0},
				{	"COLOR",	    0,	DXGI_FORMAT_R32G32B32A32_FLOAT,		0,	12,		D3D11_INPUT_PER_VERTEX_DATA,	0},
			};

			ID3D11InputLayout* t_raw = nullptr;
			HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreateInputLayout(t_layout,COUNTOF(t_layout),t_blob->GetBufferPointer(),t_blob->GetBufferSize(),&t_raw);
			if(t_raw != nullptr){
				t_vertex_layout.reset(t_raw,release_delete< ID3D11InputLayout >());
			}
			if(FAILED(t_result)){
				t_vertex_layout.reset();
			}
		}
	}

	sharedptr< ID3D11PixelShader > t_pixel_shader;
	{
		STLString t_vertex_source = 
			"struct VSO {"
				"float4 p : SV_POSITION;"
				"float3 c : COLOR;"
			"};"
			"float4 PS(VSO i) : SV_Target {"
				"return float4(i.c.r, i.c.g, i.c.b, 1.0f);"
			"}";

		sharedptr< ID3DBlob > t_blob;
		{
			sharedptr< ID3DBlob > t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_vertex_source.c_str(),t_vertex_source.size(),nullptr,nullptr,nullptr,"PS","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete< ID3DBlob >());
			}
			if(t_raw != nullptr){
				t_blob_error.reset(t_raw_error,release_delete< ID3DBlob >());
			}
			if(FAILED(t_result)){
				t_blob.reset();
			}

			if(t_blob != nullptr){
			}else{
				std::string t_errorstring;
				if(t_blob_error != nullptr){
					t_errorstring = std::string((const char*)t_blob_error->GetBufferPointer(),t_blob_error->GetBufferSize());
				}
				TAGLOG("compile vertex","FAILED");
				TAGLOG("compile vertex",t_errorstring.c_str());
			}

			t_blob_error.reset();
		}

		{
			ID3D11PixelShader* t_raw = nullptr;

			HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreatePixelShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				t_pixel_shader.reset(t_raw,release_delete< ID3D11PixelShader >());
			}
			if(FAILED(t_result)){
				t_pixel_shader.reset();
			}
		}
	}

	sharedptr< ID3D11Buffer > t_constant_buffer;
	{
		D3D11_BUFFER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = sizeof(float) * 16;				//MATRIX
			t_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			t_desc.CPUAccessFlags = 0;
		}

		ID3D11Buffer* t_raw = nullptr;
		HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreateBuffer(&t_desc,nullptr,&t_raw);
		if(t_raw != nullptr){
		}
		if(FAILED(t_result)){
			t_constant_buffer.reset();
		}
	}






	s_d3d11->GetImpl()->GetDeviceContext()->VSSetShader(t_vertex_shader.get(),nullptr,0);

	s_d3d11->GetImpl()->GetDeviceContext()->IASetInputLayout(t_vertex_layout.get());

	s_d3d11->GetImpl()->GetDeviceContext()->PSSetShader(t_pixel_shader.get(),nullptr,0);

	{
		ID3D11Buffer* t_list_buffer[] = {
			t_vertexbuffer.get(),
		};
				
		UINT t_stride = t_vertexbuffer_stride;
		UINT t_offset = t_vertexbuffer_offset;

		s_d3d11->GetImpl()->GetDeviceContext()->IASetVertexBuffers(0,1,t_list_buffer,&t_stride,&t_offset);
		s_d3d11->GetImpl()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	{
		ID3D11Buffer* t_list[] = {
			t_constant_buffer.get(),
		};
		s_d3d11->GetImpl()->GetDeviceContext()->VSSetConstantBuffers(0,1,t_list);
	}

	while(s_window->IsEnd() == false){

		s_window->Update();

		s_d3d11->Render_ClearRenderTargetView(s_clear_color);
		s_d3d11->Render_ClearDepthStencilView();

		s_d3d11->Render_ViewPort(0.0f,0.0f,800,600);

		{
			//s_view
			NBsys::NGeometry::Geometry_Matrix_44 s_view;

			//s_projection
			NBsys::NGeometry::Geometry_Matrix_44 s_projection;

			//s_matrix
			NBsys::NGeometry::Geometry_Matrix_44 s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();


			//s_near
			f32 s_near = 1.0f;


			//s_far
			f32 s_far = 100.0f;


			//s_fov_deg
			f32 s_fov_deg = 60.0f;

			//s_camera_target
			NBsys::NGeometry::Geometry_Vector3 s_camera_target(0.0f,0.0f,0.0f);

			//s_camera_position
			NBsys::NGeometry::Geometry_Vector3 s_camera_position(0.0f,5.0f,5.0f);

			//s_camera_up
			NBsys::NGeometry::Geometry_Vector3 s_camera_up(0.0f,1.0f,0.0f);

			//プロジェクション。
			s_projection.Set_PerspectiveProjectionMatrix(BSYS_OPENGL_WIDTH,BSYS_OPENGL_HEIGHT,s_fov_deg,s_near,s_far);

			//ビュー。
			s_view.Set_ViewMatrix(s_camera_target,s_camera_position,s_camera_up);

			NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_matrix * s_view * s_projection;

			//s_d3d11->GetImpl()->GetDeviceContext()->UpdateSubresource(t_constant_buffer.get(),0,nullptr,&t_view_projection.m[0][0],0,0);
		}

		s_d3d11->GetImpl()->GetDeviceContext()->Draw(t_vertexbuffer_countofvertex,0);

		if(s_d3d11->Render_Present() == false){
			break;
		}
	}

	s_d3d11->Render_Delete();
	s_d3d11.reset();

	s_window->Delete();
	s_window.reset();

	return;
}

#endif

