

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(DEF_TEST_INDEX == 2)
namespace NTest
{
	/** File_Allocator
	*/
	class File_Allocator : public NBsys::NFile::File_Allocator
	{
	public:
		
		/** constructor
		*/
		File_Allocator()
		{
		}

		/** destructor
		*/
		virtual ~File_Allocator()
		{
		}

	public:

		/** Alloc
		*/
		virtual void* Alloc(u32 a_size)
		{
			return ::malloc(a_size);
		}

		/** Free
		*/
		virtual void Free(void* a_pointer)
		{
			return ::free(a_pointer);
		}

	};


	/** Test_Main
	*/
	void Test_Main()
	{
		//ファイル開始。
		NBsys::NFile::StartSystem(1);
		NBsys::NFile::SetRoot(0,L"./project_test/test" DEF_TEST_STRING);

		//読み込み開始。
		sharedptr<NBsys::NFile::File_Object> t_fileobject(new NBsys::NFile::File_Object(0,L"test2.json",-1,new File_Allocator,1));

		//読み込み中。
		while(t_fileobject->IsBusy()){
			ThreadSleep(10);
		}

		if(t_fileobject->GetErrorCode() != ErrorCode::Success){
			t_fileobject.reset();
		}

		if(t_fileobject){

			//コンバート。
			for(;;){
				NBsys::NFile::File_ConvertLock_ReturnType::Id t_ret = t_fileobject->ConvertLock();
				if(t_ret == NBsys::NFile::File_ConvertLock_ReturnType::Locked){
					//未コンバート => コンバート中。

					//コンバート中 => コンバート済み。
					t_fileobject->GetLoadData().get()[static_cast<s32>(t_fileobject->GetLoadSize())] = 0x00;
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
				if(t_json->IsExistItem("name1") == true){
					STLString t_value = *t_json->GetItem("name1")->GetStringData();
					DEBUGLOG("name1 = %s\n",t_value.c_str());
				}
				if(t_json->IsExistItem("name2") == true){
					s32 t_value = t_json->GetItem("name2")->GetInteger();
					DEBUGLOG("name1 = %d\n",t_value);
				}
				if(t_json->IsExistItem("name3") == true){
					f32 t_value = t_json->GetItem("name3")->GetFloat();
					DEBUGLOG("name1 = %f\n",t_value);
				}
				if(t_json->IsExistItem("name4") == true){
					bool t_value = t_json->GetItem("name4")->GetBoolData();
					DEBUGLOG("name1 = %d\n",t_value?1:0);
				}
			}

			//ＪＳＯＮ出力。
			{
				FileHandle t_filehandle;
				t_filehandle.WriteOpen(L"./project_test/test2/out.json");
				STLString t_jsonstring = t_json->ConvertJsonString();
				t_filehandle.Write(reinterpret_cast<const u8*>(t_jsonstring.c_str()),t_jsonstring.size(),0);
				t_filehandle.SetEOF(t_jsonstring.size());
				t_filehandle.Close();
			}
		}

		//ファイル終了。
		NBsys::NFile::EndSystemRequest();
		NBsys::NFile::EndWaitSystem();

		return;
	}


}
#endif

