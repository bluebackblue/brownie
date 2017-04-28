

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スタックトレース。
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
#include "./stringtool.h"


/** include
*/
#if defined(ROM_MASTER)

#else

	#if(BLIB_STACKTRACE_ENABLE)

		#if defined(PLATFORM_VCWIN)
	
			/** include
			*/
			#include "./include_windows.h"

			/** include
			*/
			#pragma warning(disable:4091)
			#include <imagehlp.h>

			/** lib
			*/
			#pragma comment(lib,"imagehlp.lib")

		#endif

	#endif

#endif

/** NBlib
*/
namespace NBlib
{
	#if defined(ROM_MASTER)

	#else

		#if(BLIB_STACKTRACE_ENABLE)
		void StackTrace(STLString& a_out_string,s32 a_index)
		{
			a_out_string.clear();

			#if defined(PLATFORM_VCWIN)
			{
				HANDLE t_process = ::GetCurrentProcess();

				if(::SymInitialize(t_process,WIN_NULL,TRUE) != TRUE){
				}

				void* t_stack_list[100];
				s32 t_stack_count = ::RtlCaptureStackBackTrace(0,COUNTOF(t_stack_list),t_stack_list,WIN_NULL);

				SYMBOL_INFO* t_symbol = nullptr;
				{
					u8 s_symbol_data[sizeof(SYMBOL_INFO) + 255 * sizeof(char) + sizeof(char)] = {0};
					t_symbol = reinterpret_cast< SYMBOL_INFO* >(s_symbol_data);
					t_symbol->MaxNameLen   = sizeof(s_symbol_data) - sizeof(SYMBOL_INFO) - 1;
					t_symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
				}

				int t_result_count = 0;

				for(int ii=0;ii<t_stack_count;ii++){
					if((a_index < 0)||(ii == a_index)){
						::SymFromAddr(t_process,(DWORD64)(t_stack_list[ii]),0,t_symbol);

						if(t_result_count > 0){
							a_out_string += "\n";
						}

						a_out_string += t_symbol->Name;

						t_result_count++;
					}
				}
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}
		#endif

	#endif
}

