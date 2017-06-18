

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �C���N���[�h�B
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST2
*/
#if defined(DEF_TEST2)


/** include
*/
#include "./test2_main.h"


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


/** Test_Main
*/
void Test_Main()
{
	//�t�@�C���J�n�B
	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test/test2");

	//�ǂݍ��݊J�n�B
	sharedptr< NBsys::NFile::File_Object > t_fileobject(new NBsys::NFile::File_Object(0,L"test2.json",-1,sharedptr< NBsys::NFile::File_Allocator >(),1));

	//�ǂݍ��ݒ��B
	while(t_fileobject->IsBusy()){
		ThreadSleep(10);
	}

	//�R���o�[�g�B
	{
		NBsys::NFile::File_ConvertLock_ReturnType::Id t_ret = t_fileobject->ConvertLock();
		if(t_ret == NBsys::NFile::File_ConvertLock_ReturnType::Locked){
			//���R���o�[�g => �R���o�[�g���B
			t_fileobject->GetLoadData().get()[static_cast<s32>(t_fileobject->GetLoadSize())] = 0x00;
			t_fileobject->ConvertUnlock();
		}else{
			//�R���o�[�g���B
			//�R���o�[�g�ς݁B
		}
	}

	//�i�r�n�m��́B
	sharedptr< JsonItem > t_json(new JsonItem(reinterpret_cast<char*>(t_fileobject->GetLoadData().get())));

	//�i�r�n�m�擾�B
	if(t_json->GetValueType() == JsonItem::ValueType::AssociativeArray){
		if(t_json->IsExistItem("name") == true){
			STLString t_name = *t_json->GetItem("name")->GetStringData();
			DEBUGLOG("name = %s\n",t_name.c_str());
		}
		if(t_json->IsExistItem("value") == true){
			s32 t_value = t_json->GetItem("value")->GetInteger();
			DEBUGLOG("value = %d\n",t_value);
		}
	}

	//�i�r�n�m�o�́B
	{
		FileHandle t_filehandle;
		t_filehandle.WriteOpen(L"./project_test/test2/out.json");
		STLString t_jsonstring = t_json->ConvertJsonString();
		t_filehandle.Write(reinterpret_cast< const u8* >(t_jsonstring.c_str()),t_jsonstring.size(),0);
		t_filehandle.Close();
	}

	//�t�@�C���I���B
	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}

#endif

