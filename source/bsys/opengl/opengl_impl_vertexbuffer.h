#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGLÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_impl_include.h"
#include "./opengl_impl_rawid.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** Opengl_Impl_VertexBuffer
	*/
	class Opengl_Impl_VertexBuffer
	{
	private:
		/** data_byte
		*/
		sharedptr<u8> data_byte;

		/** size_byte
		*/
		s32 size_byte;

		/** stride_byte
		*/
		s32 stride_byte;

		/** vertexbuffer_rawid
		*/
		RawID vertexbuffer_rawid;
	
	public:
		/** constructor
		*/
		Opengl_Impl_VertexBuffer(const sharedptr<u8>& a_data_byte,s32 a_size_byte,s32 a_stride_byte)
			:
			data_byte(a_data_byte),
			size_byte(a_size_byte),
			stride_byte(a_stride_byte),
			vertexbuffer_rawid()
		{
		}

		/** destructor
		*/
		nonvirtual ~Opengl_Impl_VertexBuffer(){}

	public:
		/** SetVertexBuffer_RawID
		*/
		void SetVertexBuffer_RawID(const RawID& a_vertexbuffer_rawid)
		{
			this->vertexbuffer_rawid = a_vertexbuffer_rawid;
		}

		/** GetRawVertexBufferId
		*/
		const RawID& GetVertexBuffer_RawID() const
		{
			return this->vertexbuffer_rawid;
		}

		/** GetDataByte
		*/
		const sharedptr<u8>& GetDataByte()
		{
			return this->data_byte;
		}

		/** GetSizeByte
		*/
		s32 GetSizeByte()
		{
			return this->size_byte;
		}

		/** GetStrideByte
		*/
		s32 GetStrideByte()
		{
			return this->stride_byte;
		}

	};

}}
#endif

