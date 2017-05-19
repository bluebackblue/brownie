

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
static sharedptr< NBsys::NModel::Model_Vertex< NBsys::NModel::Model_Vertex_Data_Pos3Color4 > > s_vertex;

/** s_clear_color
*/
static NBsys::NColor::Color_F s_clear_color(0.0f,0.5f,0.5f,1.0f);

//s_matrix
static NBsys::NGeometry::Geometry_Matrix_44 s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();

//s_pcounter
u64 s_pcounter = 0ULL;

//s_vertexbuffer
sharedptr< ID3D11Buffer > s_vertexbuffer;
s32 s_vertexbuffer_stride;
s32 s_vertexbuffer_offset;
s32 s_vertexbuffer_countofvertex;

/** s_vertex_shader
*/
sharedptr< ID3D11VertexShader > s_vertex_shader;

/** s_vertex_layout
*/
sharedptr< ID3D11InputLayout > s_vertex_layout;

/** s_pixel_shader
*/
sharedptr< ID3D11PixelShader > s_pixel_shader;

/** USE_FOVE
*/
#define USE_FOVE (1)

/** s_fovehmd
*/
#if(USE_FOVE)
static sharedptr< NBsys::NFovehmd::Fovehmd > s_fovehmd;
#endif

/** Draw
*/
void Draw(sharedptr< ID3D11Buffer >& a_constant_buffer,NBsys::NGeometry::Geometry_Matrix_44& a_model_matrix,NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
{
	for(s32 xx=-10;xx<10;xx++){
		for(s32 zz=-10;zz<10;zz++){
			s32 yy = 0;

			NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_model_matrix * NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(xx*2.0f,yy*2.0f,zz*2.0f) * a_view_projection;
			NBsys::NGeometry::Geometry_Matrix_44 t_view_projection_transpose = t_view_projection.Make_Transpose();
			s_d3d11->GetImpl()->GetDeviceContext()->UpdateSubresource(a_constant_buffer.get(),0,nullptr,&t_view_projection_transpose.m[0][0],0,0);
			s_d3d11->GetImpl()->GetDeviceContext()->VSSetShader(s_vertex_shader.get(),nullptr,0);
			{
				ID3D11Buffer* t_list[] = 
				{
					a_constant_buffer.get()
				};
				s_d3d11->GetImpl()->GetDeviceContext()->VSSetConstantBuffers(0,1,t_list);
			}
			s_d3d11->GetImpl()->GetDeviceContext()->PSSetShader(s_pixel_shader.get(),nullptr,0);
			s_d3d11->GetImpl()->GetDeviceContext()->Draw(s_vertexbuffer_countofvertex,0);
		}
	}
}

/** Draw1
*/
void Draw1(sharedptr< ID3D11Buffer >& a_constant_buffer,NBsys::NGeometry::Geometry_Matrix_44& a_model_matrix,NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
{
	s32 xx = 0;
	s32 zz = 0;
	s32 yy = 0;

	NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_model_matrix * NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(xx*2.0f,yy*2.0f,zz*2.0f) * a_view_projection;
	NBsys::NGeometry::Geometry_Matrix_44 t_view_projection_transpose = t_view_projection.Make_Transpose();
	s_d3d11->GetImpl()->GetDeviceContext()->UpdateSubresource(a_constant_buffer.get(),0,nullptr,&t_view_projection_transpose.m[0][0],0,0);
	s_d3d11->GetImpl()->GetDeviceContext()->VSSetShader(s_vertex_shader.get(),nullptr,0);
	{
		ID3D11Buffer* t_list[] = 
		{
			a_constant_buffer.get()
		};
		s_d3d11->GetImpl()->GetDeviceContext()->VSSetConstantBuffers(0,1,t_list);
	}
	s_d3d11->GetImpl()->GetDeviceContext()->PSSetShader(s_pixel_shader.get(),nullptr,0);
	s_d3d11->GetImpl()->GetDeviceContext()->Draw(s_vertexbuffer_countofvertex,0);
}


/** Test_Main
*/
void Test_Main()
{
	TAGLOG("main","DEF_TEST1");

	#if(USE_FOVE)
	s_fovehmd.reset(new NBsys::NFovehmd::Fovehmd());
	while(1){
		s_fovehmd->ResetErrorCode();
		s_fovehmd->ConnectStart();
		while(s_fovehmd->ConnectUpdate() == false){
			ThreadSleep(16);
		}
		if(s_fovehmd->GetErrorCode().code == ErrorCode::Success){
			break;
		}
		ThreadSleep(16);
	}
	#endif

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());

	#if(USE_FOVE)
	s_window->Create(L"sample",static_cast<s32>(s_fovehmd->GetSingleEyeResolution().x * 2)/3,static_cast<s32>(s_fovehmd->GetSingleEyeResolution().y)/3);
	s_d3d11->Render_Create(s_window,static_cast<s32>(s_fovehmd->GetSingleEyeResolution().x * 2),static_cast<s32>(s_fovehmd->GetSingleEyeResolution().y));
	#else
	s_window->Create(L"sample",800,600);
	s_d3d11->Render_Create(s_window,800,600);
	#endif

	//モデル。
	s_vertex = NBsys::NModel::Preset_Box< NBsys::NModel::Model_Vertex_Data_Pos3Color4 >();

	//バーテックスバッファ。
	{
		s_vertexbuffer_stride = s_vertex->GetVertexStrideByte();
		s_vertexbuffer_offset = s_vertex->GetVertexOffset(0);
		s_vertexbuffer_countofvertex = s_vertex->GetVertexCountOf(0);

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
			s_vertexbuffer.reset(t_raw,release_delete< ID3D11Buffer >());
		}
		if(FAILED(t_result)){
			s_vertexbuffer.reset();
		}
	}

	//バーテックス。
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
				s_vertex_shader.reset(t_raw,release_delete< ID3D11VertexShader >());
			}
			if(FAILED(t_result)){
				s_vertex_shader.reset();
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
				s_vertex_layout.reset(t_raw,release_delete< ID3D11InputLayout >());
			}
			if(FAILED(t_result)){
				s_vertex_layout.reset();
			}
		}
	}
	
	//ピクセル。
	{
		STLString t_pixel_source = 
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
			HRESULT t_result = D3DCompile(t_pixel_source.c_str(),t_pixel_source.size(),nullptr,nullptr,nullptr,"PS","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
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
				s_pixel_shader.reset(t_raw,release_delete< ID3D11PixelShader >());
			}
			if(FAILED(t_result)){
				s_pixel_shader.reset();
			}
		}
	}

	//シェーダ。
	sharedptr< ID3D11Buffer > t_constant_buffer;
	{
		{
			D3D11_BUFFER_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.Usage = D3D11_USAGE_DEFAULT;
				t_desc.ByteWidth = sizeof(float) * 16;
				t_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				t_desc.CPUAccessFlags = 0;
			}

			ID3D11Buffer* t_raw = nullptr;
			HRESULT t_result = s_d3d11->GetImpl()->GetDevice()->CreateBuffer(&t_desc,nullptr,&t_raw);
			if(t_raw != nullptr){
				t_constant_buffer.reset(t_raw,release_delete< ID3D11Buffer >());
			}
			if(FAILED(t_result)){
				t_constant_buffer.reset();
			}
		}
	}

	s_pcounter = PerformanceCounter::GetPerformanceCounter();

	// Main loop
	while (true)
	{
		s_window->Update();
		if(s_window->IsEnd() == true){
			break;
		}

		#if(USE_FOVE)
		s_fovehmd->Update();
		#endif

		float t_delta = 0.0f;
		{
			u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
			u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
			t_delta = static_cast<float>(t_pcounter_now - s_pcounter) / t_pcounter_sec;
			if(t_delta < (1.0f / 60)){
				continue;
			}
			s_pcounter = t_pcounter_now;
		}

		//更新。
		{
			//s_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_RotationY(t_delta * 0.1f);
		}

		//レイアウト。
		s_d3d11->GetImpl()->GetDeviceContext()->IASetInputLayout(s_vertex_layout.get());

		//頂点バッファ。
		{
			ID3D11Buffer* t_list[] = {
				s_vertexbuffer.get(),
			};

			UINT t_stride = s_vertexbuffer_stride;

			UINT t_offset = 0;

			s_d3d11->GetImpl()->GetDeviceContext()->IASetVertexBuffers(0, 1, t_list, &t_stride, &t_offset);
		}

		//プリミティブ形状。
		s_d3d11->GetImpl()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));
		s_d3d11->Render_ClearDepthStencilView();
		{
			#if(0)
			{
				{
					s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

					NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetLeftViewProjection(s_near,s_far,2.0f);

					Draw(t_constant_buffer,s_matrix,t_view_projection);
				}

				{
					s_d3d11->Render_ViewPort(s_fovehmd->GetSingleEyeResolution().x,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

					NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetRightViewProjection(s_near,s_far,2.0f);

					Draw(t_constant_buffer,s_matrix,t_view_projection);
				}
			}
			#else
			{
				s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y);

				//t_camera_target
				NBsys::NGeometry::Geometry_Vector3 t_camera_target(0.0f,0.0f,0.0f);

				//t_camera_position
				NBsys::NGeometry::Geometry_Vector3 t_camera_position(1.0f,1.0f,-5.0f);

				//t_camera_up
				NBsys::NGeometry::Geometry_Vector3 t_camera_up(0.0f,1.0f,0.0f);

				//s_near
				f32 t_near = 0.1f;

				//s_far
				f32 t_far = 1000.0f;

				//s_fov_deg
				f32 t_fov_deg = 60.0f;

				NBsys::NGeometry::Geometry_Matrix_44 t_projection;
				t_projection.Set_PerspectiveProjectionMatrix(s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y,t_fov_deg,t_near,t_far);

				NBsys::NGeometry::Geometry_Matrix_44 t_view;
				t_view.Set_ViewMatrix(t_camera_target,t_camera_position,t_camera_up);
				
				{
					NBsys::NGeometry::Geometry_Vector3 t_fovehmd_position = s_fovehmd->GetCameraPosition();
					NBsys::NGeometry::Geometry_Quaternion t_fovehmd_quaternion = s_fovehmd->GetCameraQuaternion();
					NBsys::NGeometry::Geometry_Matrix_44 t_fovehmd_matrix(t_fovehmd_quaternion);

					{
						NBsys::NGeometry::Geometry_Matrix_44 t_matrix = t_fovehmd_matrix;
						t_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_fovehmd_position.x,t_fovehmd_position.y,t_fovehmd_position.z);
						t_matrix *= s_fovehmd->GetLeftEyeTranslate();
						Draw1(t_constant_buffer,t_matrix,t_view*t_projection);
					}

					{
						NBsys::NGeometry::Geometry_Matrix_44 t_matrix = t_fovehmd_matrix;
						t_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_fovehmd_position.x,t_fovehmd_position.y,t_fovehmd_position.z);
						t_matrix *= s_fovehmd->GetRightEyeTranslate();
						Draw1(t_constant_buffer,t_matrix,t_view*t_projection);
					}
				}
			}
			#endif
		}

		#if(USE_FOVE)
		{
			s_fovehmd->SetTexture(s_d3d11->GetImpl()->GetBackBuffer().get());
		}
		#endif

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

