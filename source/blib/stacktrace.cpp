

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
#include "./vastring.h"


/** include
*/
#if defined(ROM_MASTER)

#else

	#if(BLIB_STACKTRACE_ENABLE)

		#if defined(PLATFORM_VCWIN)
	
			/** include
			*/
			#include <brownie_config/windows_include.h>

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
					ASSERT(0);
				}

				void* t_stack_list[100];
				s32 t_stack_count = ::RtlCaptureStackBackTrace(0,COUNTOF(t_stack_list),t_stack_list,WIN_NULL);

				IMAGEHLP_SYMBOL* t_symbol = nullptr;
				{
					static u8 s_symbol_data[sizeof(IMAGEHLP_SYMBOL) + 255 * sizeof(char) + sizeof(char)];
					t_symbol = reinterpret_cast< IMAGEHLP_SYMBOL* >(s_symbol_data);
					t_symbol->MaxNameLength = sizeof(s_symbol_data) - sizeof(IMAGEHLP_SYMBOL) - sizeof(char);
					t_symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
				}

				IMAGEHLP_LINE* t_line = nullptr;
				{
					static u8 s_line_data[sizeof(IMAGEHLP_LINE) + 255 * sizeof(char) + sizeof(char)] = {0};
					t_line = reinterpret_cast< IMAGEHLP_LINE* >(s_line_data);
					t_line->SizeOfStruct = sizeof(IMAGEHLP_LINE);
				}

				a_out_string += "----- stacktrace -----\n";

				for(int ii=0;ii<t_stack_count;ii++){
					if((a_index < 0)||(ii == a_index)){
						::SymGetSymFromAddr(t_process,(DWORD64)(t_stack_list[ii]),0,t_symbol);

						::SymGetLineFromAddr(t_process,(DWORD64)(t_stack_list[ii]),0,t_line);

						char t_buffer[64] = {0};

						#if defined(ROM_32BIT)
						a_out_string += VASTRING(t_buffer,sizeof(t_buffer),"0x%08x : ",t_stack_list[ii]);
						#else
						a_out_string += VASTRING(t_buffer,sizeof(t_buffer),"0x%016x : ",t_stack_list[ii]);
						#endif

						a_out_string += t_symbol->Name;
						a_out_string += "\n";
					}
				}

				a_out_string += "----- ----- -----";
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

