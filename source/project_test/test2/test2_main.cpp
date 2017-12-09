

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


/** DEF_TEST2
*/
#if defined(DEF_TEST2)


/** include
*/
#include "./test2_main.h"


/** Test_Main
*/
void Test_Main()
{
	//ファイル開始。
	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test/test2");

	//読み込み開始。
	sharedptr<NBsys::NFile::File_Object> t_fileobject(new NBsys::NFile::File_Object(0,L"test2.json",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));

	//読み込み中。
	while(t_fileobject->IsBusy()){
		ThreadSleep(10);
	}

	//コンバート。
	for(;;){
		NBsys::NFile::File_ConvertLock_ReturnType::Id t_ret = t_fileobject->ConvertLock();
		if(t_ret == NBsys::NFile::File_ConvertLock_ReturnType::Locked){
			//未コンバート => コンバート中。
			t_fileobject->GetLoadData().get()[static_cast<s32>(t_fileobject->GetLoadSize())] = 0x00;

			//コンバート中 => コンバート済み。
			t_fileobject->ConvertUnlock();
			
			break;
		}else if(t_ret == NBsys::NFile::File_ConvertLock_ReturnType::ConvertNow){
			//コンバート中。

			//ロックに成功していないのでアンロック不要。
		}else{
			//コンバート済み。

			//ロックに成功していないのでアンロック不要。
			break;
		}
	}

	//ＪＳＯＮ解析。
	sharedptr<JsonItem> t_json(new JsonItem(reinterpret_cast<char*>(t_fileobject->GetLoadData().get())));

	//ＪＳＯＮ取得。
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

	//ＪＳＯＮ出力。
	{
		FileHandle t_filehandle;
		t_filehandle.WriteOpen(L"./project_test/test2/out.json");
		STLString t_jsonstring = t_json->ConvertJsonString();
		t_filehandle.Write(reinterpret_cast<const u8*>(t_jsonstring.c_str()),t_jsonstring.size(),0);
		t_filehandle.Close();
	}

	//ファイル終了。
	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}

#endif

