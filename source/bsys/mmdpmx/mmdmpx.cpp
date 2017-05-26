

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �l�l�c�B�o�l�w�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../file/file.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NMmdPmx
{
	struct Header
	{
		//[PMX ][pmx ]
		char	tag[4];

		f32		version;
	};

	struct HeaderEx
	{
		u8		utf8;
		u8		add_uv_num;
		u8		vertex_index_size;
		u8		texture_index_size;
		u8		material_index_size;
		u8		bone_index_size;
		u8		morph_index_size;
		u8		rigid_body_index_size;
	};

	/*
	//Model Info
	std::string modelName;							//!< \if ENGLISH \brief  The name of the model (in Japanese) \endif
													//!< \if JAPANESE \brief ���f���̖��O�i���{��Łj�B \endif
	std::string modelNameEnglish;					//!< \if ENGLISH \brief  The name of the model (in English) \endif
													//!< \if JAPANESE \brief ���f���̖��O�i�p��Łj�B \endif
	std::string comment;							//!< \if ENGLISH \brief  Comments about the model (in Japanese) \endif
													//!< \if JAPANESE \brief ���f���Ɋւ���R�����g�i���{��Łj�B \endif
	std::string commentEnglish;						//!< \if ENGLISH \brief  Comments about the model (in English) \endif
													//!< \if JAPANESE \brief ���f���Ɋւ���R�����g�i�p��Łj�B \endif
		
	//Vertex
	int vertex_continuing_datasets; 				//!< \if ENGLISH \brief  The number of vertices in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă��钸�_�̐��B \endif
	std::vector<PMXVertex*> vertices;				//!< \if ENGLISH \brief  A vector containing the vertices. \endif
													//!< \if JAPANESE \brief ���_�̔z��ivector���j \endif
		
	//Face
	int face_continuing_datasets;					//!< \if ENGLISH \brief  The number of faces in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���ʂ̐��B \endif
	std::vector<PMXFace*> faces;					//!< \if ENGLISH \brief  A vector containing the faces. \endif
													//!< \if JAPANESE \brief �ʂ̔z��ivector���j \endif
		
	//Texture
	int texture_continuing_datasets;				//!< \if ENGLISH \brief  The number of textures in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���e�N�X�`���̐��B \endif
	std::string *texturePaths;						//!< \if ENGLISH \brief  A pointer containing an array texture paths. \endif
													//!< \if JAPANESE \brief �e�N�X�`���̃p�X�̔z��ւ̃|�C���^�[�B \endif
		
	//Material
	int material_continuing_datasets;				//!< \if ENGLISH \brief  The number of materials in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���}�e���A���̐��B \endif
	std::vector<PMXMaterial*> materials;			//!< \if ENGLISH \brief  A vector containing the materials. \endif
													//!< \if JAPANESE \brief �}�e���A���̔z��ivector���j \endif
		
	//Bone
	int bone_continuing_datasets;					//!< \if ENGLISH \brief  The number of bones in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���{�[���̐��B \endif
	std::vector<PMXBone*> bones;					//!< \if ENGLISH \brief  A vector containing the bones. \endif
													//!< \if JAPANESE \brief �{�[���̔z��ivector���j \endif
		
	//Morph (Emotion data)
	int morph_continuing_datasets;					//!< \if ENGLISH \brief  The number of morphs in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă��郂�[�t�̐��B \endif
	std::vector<PMXMorph*> morphs;					//!< \if ENGLISH \brief  A vector containing the bones. \endif
													//!< \if JAPANESE \brief ���[�t�̔z��ivector���j \endif
		
	//Display Frame
	int display_frame_continuing_datasets;			//!< \if ENGLISH \brief  The number of display frames in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���\���g�̐��B \endif
	std::vector<PMXDisplayFrame*> displayFrames;	//!< \if ENGLISH \brief  A vector containing the display frames. \endif
													//!< \if JAPANESE \brief �\���g�̔z��ivector���j \endif
		
	//Rigid Body
	int rigid_body_continuing_datasets;				//!< \if ENGLISH \brief  The number of rigidbodies in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă��鍄�̂̐��B \endif
	std::vector<PMXRigidBody*> rigidBodies;			//!< \if ENGLISH \brief  A vector containing the rigidbodies. \endif
													//!< \if JAPANESE \brief ���̂̔z��ivector���j \endif
		
	//Joint
	int joint_continuing_datasets;					//!< \if ENGLISH \brief  The number of joints in the PMX model. \endif
													//!< \if JAPANESE \brief PMX���f���Ɋi�[����Ă���W���C���g�̐��B \endif
	std::vector<PMXJoint*> joints;					//!< \if ENGLISH \brief  A vector containing the joints. \endif
	*/


	bool Load(sharedptr< NFile::File_Object >& a_file)
	{
		if(a_file->IsBusy() == true){
			return false;
		}

		sharedptr< u8 >& t_data = a_file->GetLoadData();

		u8* t_raw = t_data.get();

		Header* t_header = reinterpret_cast< Header* >(t_raw);
		t_raw += 8;	//sizeof(Header)

		u8 t_header_ex_size = *reinterpret_cast< u8* >(t_raw);
		t_raw += 1;	//sizeof(u8) 

		HeaderEx* t_header_ex = reinterpret_cast< HeaderEx* >(t_raw);
		t_raw += t_header_ex_size;

		STLWString t_mode_name_jp;
		{
			u32 t_size;
			reinterpret_cast< u8* >(&t_size)[0] = t_raw[0];
			reinterpret_cast< u8* >(&t_size)[1] = t_raw[1];
			reinterpret_cast< u8* >(&t_size)[2] = t_raw[2];
			reinterpret_cast< u8* >(&t_size)[3] = t_raw[3];
			t_raw += 4;	//sizeof(u32)

			if(t_size > 0){
				if(t_header_ex->utf8){
					CharToWchar(reinterpret_cast< char* >(t_raw),t_mode_name_jp);
				}else{
					t_mode_name_jp = reinterpret_cast< wchar* >(t_raw);
				}
			}
			t_raw += t_size;
		}

		STLWString t_mode_name_en;
		{
			u32 t_size;
			reinterpret_cast< u8* >(&t_size)[0] = t_raw[0];
			reinterpret_cast< u8* >(&t_size)[1] = t_raw[1];
			reinterpret_cast< u8* >(&t_size)[2] = t_raw[2];
			reinterpret_cast< u8* >(&t_size)[3] = t_raw[3];
			t_raw += 4;	//sizeof(u32)

			if(t_size > 0){
				if(t_header_ex->utf8){
					CharToWchar(reinterpret_cast< char* >(t_raw),t_mode_name_en);
				}else{
					t_mode_name_en = reinterpret_cast< wchar* >(t_raw);
				}
			}
			t_raw += t_size;
		}

		STLWString t_commnet_jp;
		{
			u32 t_size;
			reinterpret_cast< u8* >(&t_size)[0] = t_raw[0];
			reinterpret_cast< u8* >(&t_size)[1] = t_raw[1];
			reinterpret_cast< u8* >(&t_size)[2] = t_raw[2];
			reinterpret_cast< u8* >(&t_size)[3] = t_raw[3];
			t_raw += 4;	//sizeof(u32)

			if(t_size > 0){
				if(t_header_ex->utf8){
					CharToWchar(reinterpret_cast< char* >(t_raw),t_commnet_jp);
				}else{
					t_commnet_jp = reinterpret_cast< wchar* >(t_raw);
				}
			}
			t_raw += t_size;
		}

		STLWString t_commnet_en;
		{
			u32 t_size;
			reinterpret_cast< u8* >(&t_size)[0] = t_raw[0];
			reinterpret_cast< u8* >(&t_size)[1] = t_raw[1];
			reinterpret_cast< u8* >(&t_size)[2] = t_raw[2];
			reinterpret_cast< u8* >(&t_size)[3] = t_raw[3];
			t_raw += 4;	//sizeof(u32)

			if(t_size > 0){
				if(t_header_ex->utf8){
					CharToWchar(reinterpret_cast< char* >(t_raw),t_commnet_en);
				}else{
					t_commnet_en = reinterpret_cast< wchar* >(t_raw);
				}
			}
			t_raw += t_size;
		}

		{
			u32 t_vertex_count;
			reinterpret_cast< u8* >(&t_vertex_count)[0] = t_raw[0];
			reinterpret_cast< u8* >(&t_vertex_count)[1] = t_raw[1];
			reinterpret_cast< u8* >(&t_vertex_count)[2] = t_raw[2];
			reinterpret_cast< u8* >(&t_vertex_count)[3] = t_raw[3];
			t_raw += 4;	//sizeof(u32)
		}

		return true;
	}

}}
#endif

