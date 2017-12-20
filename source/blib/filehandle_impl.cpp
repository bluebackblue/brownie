

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイルハンドル。実装部分。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./debugassert.h"
#include "./filehandle_impl.h"


/** NBlib
*/
namespace NBlib
{
	/** constructor
	*/
	FileHandle_Impl::FileHandle_Impl() noexcept
		:
		#if defined(PLATFORM_VCWIN)
		rawhandle(INVALID_HANDLE_VALUE),
		#endif

		isopen(false),
		readmode(false)
	{
	}

	/** destructor
	*/
	FileHandle_Impl::~FileHandle_Impl() noexcept
	{
		this->Close();
	}

	/** ReadOpen
	*/
	bool FileHandle_Impl::ReadOpen(const STLWString& a_filename)
	{
		if(this->isopen == false){
			#if defined(PLATFORM_VCWIN)
			{
				this->rawhandle = ::CreateFileW(a_filename.c_str(),GENERIC_READ,FILE_SHARE_READ,WIN_NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,WIN_NULL);
				if(this->rawhandle == INVALID_HANDLE_VALUE){
					return false;
				}
			}
			#endif

			this->readmode = true;
			this->isopen = true;
			return true;
		}else{
			return false;
		}
	}

	/** WriteOpen
	*/
	bool FileHandle_Impl::WriteOpen(const STLWString& a_filename)
	{
		if(this->isopen == false){

			#if defined(PLATFORM_VCWIN)
			{
				//OPEN_ALWAYS
				//ファイルが存在している場合そのファイルを開きます。
				//指定したファイルが存在していない場合、この関数は dwCreationDisposition パラメータで CREATE_NEW が指定されていたと仮定して新しいファイルを作成します。
				this->rawhandle = ::CreateFileW(a_filename.c_str(),GENERIC_WRITE,0x00000000,WIN_NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,WIN_NULL);
				if(this->rawhandle == INVALID_HANDLE_VALUE){
					return false;
				}
			}
			#endif

			this->readmode = false;
			this->isopen = true;
			return true;
		}else{
			return false;
		}
	}

	/** Close
	*/
	void FileHandle_Impl::Close()
	{
		if(this->isopen){
			this->isopen = false;	

			#if defined(PLATFORM_VCWIN)
			{
				::CloseHandle(this->rawhandle);
				this->rawhandle = INVALID_HANDLE_VALUE;
			}
			#endif
			
			this->readmode = false;
		}
	}

	/** Read
	*/
	bool FileHandle_Impl::Read(u8* a_buffer,s64 a_size,s64 a_offset)
	{
		if(this->isopen && a_buffer){
			s32 t_errorcount = 0;

			s64 t_index = 0;
			while(t_index < a_size){
				s64 t_blocksize = (a_size - t_index);
				if(t_blocksize > BLIB_FILEHANDLE_READWRITE_BLOCKSIZE){
					t_blocksize = BLIB_FILEHANDLE_READWRITE_BLOCKSIZE;
				}

				//読み込み。
				#if defined(PLATFORM_VCWIN)
				{
					DWORD t_fix = 0;
					bool t_ret = true;

					DWORD t_offset_low = static_cast<DWORD>((a_offset+t_index)&0xFFFFFFFF);	//下位。
					DWORD t_ret_seek = ::SetFilePointer(this->rawhandle,t_offset_low,WIN_NULL,FILE_BEGIN);
					if(t_ret_seek == INVALID_SET_FILE_POINTER){
						t_ret = false;
					}

					if(t_ret == true){
						BOOL t_ret_read = ::ReadFile(this->rawhandle,&a_buffer[t_index],static_cast<DWORD>(t_blocksize),&t_fix,WIN_NULL);
						if(t_ret_read != TRUE){
							t_ret = false;
						}
					}

					if(t_ret != true){
						t_errorcount++;
						if(t_errorcount > BLIB_FILEHANDLE_RETRYMAX){
							return false;
						}
					}else{
						t_index += static_cast<s64>(t_fix);

						if(t_fix == 0){
							//読み込み途中で終端。
							return false;
						}
					}
				}
				#endif
			}

			return true;
		}else{
			return false;
		}
	}

	/** Write
	*/
	bool FileHandle_Impl::Write(const u8* a_buffer,s64 a_size,s64 a_offset)
	{
		if((this->isopen == true) && (this->readmode == false) && a_buffer){
			s32 t_errorcount = 0;

			s64 t_index = 0;
			while(t_index < a_size){
				s64 t_blocksize = (a_size - t_index);
				if(t_blocksize > BLIB_FILEHANDLE_READWRITE_BLOCKSIZE){
					t_blocksize = BLIB_FILEHANDLE_READWRITE_BLOCKSIZE;
				}

				//書き込み。
				#if defined(PLATFORM_VCWIN)
				{
					DWORD t_fix = 0;
					bool t_ret = true;

					DWORD t_offset_low = static_cast<DWORD>((a_offset+t_index)&0xFFFFFFFF);	//下位。
					DWORD t_ret_seek = ::SetFilePointer(this->rawhandle,t_offset_low,WIN_NULL,FILE_BEGIN);
					if(t_ret_seek == INVALID_SET_FILE_POINTER){
						t_ret = false;
					}

					if(t_ret == true){
						BOOL t_ret_write = ::WriteFile(this->rawhandle,&a_buffer[t_index],static_cast<DWORD>(t_blocksize),&t_fix,WIN_NULL);
						if(t_ret_write != TRUE){
							t_ret = false;
						}
					}

					if(t_ret != true){
						t_errorcount++;
						if(t_errorcount > BLIB_FILEHANDLE_RETRYMAX){
							BOOL t_ret_flush = ::FlushFileBuffers(this->rawhandle);
							ASSERT(t_ret_flush == TRUE);
							return false;
						}
					}else{
						t_index += static_cast<s64>(t_fix);
					}
				}
				#endif
			}

			#if defined(PLATFORM_VCWIN)
			{
				BOOL t_ret_flush = ::FlushFileBuffers(this->rawhandle);
				if(t_ret_flush != TRUE){
					ASSERT(0);
				}
			}
			#endif

			return true;
		}else{
			return false;
		}
	}

	/** GetSize
	*/
	s64 FileHandle_Impl::GetSize() const
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				DWORD t_size = ::GetFileSize(this->rawhandle,WIN_NULL);
				return static_cast<s64>(t_size);
			}
			#endif
		}

		return 0;
	}

	/** IsOpen
	*/
	bool FileHandle_Impl::IsOpen() const
	{
		return this->isopen;
	}

	/** SetEOF
	*/
	void FileHandle_Impl::SetEOF(s64 a_offset)
	{
		if(this->isopen){
			#if defined(PLATFORM_VCWIN)
			{
				bool t_ret = true;

				DWORD t_offset_low = static_cast<DWORD>((a_offset)&0xFFFFFFFF);	//下位。
				DWORD t_ret_seek = ::SetFilePointer(this->rawhandle,t_offset_low,WIN_NULL,FILE_BEGIN);
				if(t_ret_seek == INVALID_SET_FILE_POINTER){
					t_ret = false;
				}

				if(t_ret == true){
					::SetEndOfFile(this->rawhandle);
				}
			}
			#endif
		}
	}

	/** GetRawHandle
	*/
	#if defined(PLATFORM_VCWIN)
	HANDLE FileHandle_Impl::GetRawHandle() const
	{
		return this->rawhandle;
	}
	#endif

}

