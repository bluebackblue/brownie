#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÉÇÉfÉãÅB
*/


/** include
*/
#include "./model_presest.h"


/** NBsys::NModel
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NModel
{
	/** Preset_Plane
	*/
	template < typename T > inline sharedptr< Model_Vertex< T > > Preset_Plane()
	{
		sharedptr< Model_Vertex< T > > t_plane(new Model_Vertex< T >());

		t_plane->AddParts("plane");

		{
			T t_vertex;

			SetColor< T >(t_vertex,1.0f,1.0f,1.0f,1.0f);

			f32 t_ww = 10.0f;
			f32 t_hh = 10.0f;

			for(s32 yy=-5;yy<5;++yy){
				f32 t_y0 = t_hh * yy;
				f32 t_y1 = t_y0 + t_hh - 0.1f;

				for(s32 xx=-5;xx<5;++xx){
					f32 t_x0 = t_ww * xx;
					f32 t_x1 = t_x0 + t_ww - 0.1f;

					{
						SetPos< T >(t_vertex,t_x0,0.0f,t_y0);
						SetUv< T >(t_vertex,0.0f,0.0f);
						t_plane->AddVertex(t_vertex);
					}

					{
						SetPos< T >(t_vertex,t_x1,0.0f,t_y0);
						SetUv< T >(t_vertex,1.0f,0.0f);
						t_plane->AddVertex(t_vertex);
					}

					{
						SetPos< T >(t_vertex,t_x0,0.0f,t_y1);
						SetUv< T >(t_vertex,0.0f,1.0f);
						t_plane->AddVertex(t_vertex);
					}

					{
						SetPos< T >(t_vertex,t_x1,0.0f,t_y1);
						SetUv< T >(t_vertex,1.0f,1.0f);
						t_plane->AddVertex(t_vertex);
					}

					{
						SetPos< T >(t_vertex,t_x0,0.0f,t_y1);
						SetUv< T >(t_vertex,0.0f,1.0f);
						t_plane->AddVertex(t_vertex);
					}

					{
						SetPos< T >(t_vertex,t_x1,0.0f,t_y0);
						SetUv< T >(t_vertex,1.0f,0.0f);
						t_plane->AddVertex(t_vertex);
					}
				}
			}
		}

		return t_plane;
	}

	/** Preset_Box
	*/
	template < typename T > inline sharedptr< Model_Vertex< T > > Preset_Box()
	{
		sharedptr< Model_Vertex< T > > t_box(new Model_Vertex< T >());

		t_box->AddParts("box");

		{
			T t_vertex;

			SetUv< T >(t_vertex,0.0f,0.0f);

			{
				//z:blue.
				SetColor< T >(t_vertex,0.0f,0.0f,1.0f,1.0f);

				SetPos< T >(t_vertex,-0.5f,-0.5f, 0.5f);//0
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f,-0.5f, 0.5f);//1
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f, 0.5f);//2
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex,-0.5f, 0.5f, 0.5f);//3
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f, 0.5f);//0
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f, 0.5f);//2
				t_box->AddVertex(t_vertex);
			}
			{
				SetColor< T >(t_vertex,1.0f,0.9f,0.9f,1.0f);

				SetPos< T >(t_vertex, 0.5f,-0.5f,-0.5f);//4
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f,-0.5f);//5
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f, 0.5f,-0.5f);//6
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex, 0.5f, 0.5f,-0.5f);//7
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f,-0.5f,-0.5f);//4
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f, 0.5f,-0.5f);//6
				t_box->AddVertex(t_vertex);
			}
			{
				//x:red.
				SetColor< T >(t_vertex,1.0f,0.0f,0.0f,1.0f);

				SetPos< T >(t_vertex, 0.5f,-0.5f, 0.5f);//1
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f,-0.5f,-0.5f);//4
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f,-0.5f);//7
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex, 0.5f, 0.5f, 0.5f);//2
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f,-0.5f, 0.5f);//1
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f,-0.5f);//7
				t_box->AddVertex(t_vertex);
			}
			{
				SetColor< T >(t_vertex,0.9f,0.9f,1.0f,1.0f);

				SetPos< T >(t_vertex,-0.5f,-0.5f,-0.5f);//5
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f, 0.5f);//0
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f, 0.5f, 0.5f);//3
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex,-0.5f, 0.5f,-0.5f);//6
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f,-0.5f);//5
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f, 0.5f, 0.5f);//3
				t_box->AddVertex(t_vertex);
			}
			{
				//y:green
				SetColor< T >(t_vertex,0.0f,1.0f,0.0f,1.0f);

				SetPos< T >(t_vertex,-0.5f, 0.5f, 0.5f);//3
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f, 0.5f);//2
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f,-0.5f);//7
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex,-0.5f, 0.5f,-0.5f);//6
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f, 0.5f, 0.5f);//3
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f, 0.5f,-0.5f);//7
				t_box->AddVertex(t_vertex);
			}
			{
				SetColor< T >(t_vertex,0.9f,1.0f,0.9f,1.0f);

				SetPos< T >(t_vertex, 0.5f,-0.5f, 0.5f);//1
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f, 0.5f);//0
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f,-0.5f);//5
				t_box->AddVertex(t_vertex);

				SetPos< T >(t_vertex, 0.5f,-0.5f,-0.5f);//4
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex, 0.5f,-0.5f, 0.5f);//1
				t_box->AddVertex(t_vertex);
				SetPos< T >(t_vertex,-0.5f,-0.5f,-0.5f);//5
				t_box->AddVertex(t_vertex);
			}
		}

		return t_box;
	}

}}
#endif

