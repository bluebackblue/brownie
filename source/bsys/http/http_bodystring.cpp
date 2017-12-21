#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �g�s�s�o�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./http_type.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** MakeBodyString_DataHeader
	*/
	STLString MakeBodyString_DataHeader(const STLString& a_boundarystring,const STLString& a_formname,const STLString& a_filename)
	{
		STLString t_body_dataheader;

		//�Z�p���[�g�B
		{
			//------****<0D 0A>
			t_body_dataheader += "--";
			t_body_dataheader += "----" + a_boundarystring;
			t_body_dataheader += "\r\n";
		}

		//Content-Disposition: form-data; name="****"; filename="****.****"<0D 0A>
		{
			t_body_dataheader += "Content-Disposition: form-data; name=\"";
			t_body_dataheader += a_formname;
			t_body_dataheader += "\"; filename=\"";
			t_body_dataheader += a_filename;
			t_body_dataheader += "\"";
			t_body_dataheader += "\r\n";
		}

		//Content-Type: application/octet-stream<0D 0A>
		{
			t_body_dataheader += "Content-Type: application/octet-stream";
			t_body_dataheader += "\r\n";
		}

		//<0D 0A>
		{
			t_body_dataheader += "\r\n";
		}

		return t_body_dataheader;
	}


	/** MakeBodyString_Footer
	*/
	STLString MakeBodyString_DataFooter()
	{
		STLString t_body_datafooter;

		//<0D 0A>
		t_body_datafooter += "\r\n";

		return t_body_datafooter;
	}


	/** MakeBodyString_TextHeader
	*/
	STLString MakeBodyString_TextHeader(const STLString& a_boundarystring,const STLString& a_formname)
	{
		STLString t_body_textheader;

		//�Z�p���[�g�B
		{
			//------****<0D 0A>
			t_body_textheader += "--";
			t_body_textheader += "----" + a_boundarystring;
			t_body_textheader += "\r\n";
		}

		//Content-Disposition: form-data; name="****"<0D 0A>
		{
			t_body_textheader += "Content-Disposition: form-data; name=\"";
			t_body_textheader += a_formname;
			t_body_textheader += "\"";
			t_body_textheader += "\r\n";
		}

		//<0D 0A>
		{
			t_body_textheader += "\r\n";
		}

		return t_body_textheader;
	}


	/** MakeBodyString_DataFooter
	*/
	STLString MakeBodyString_TextFooter()
	{
		STLString t_body_textfooter;

		//<0D 0A>
		t_body_textfooter += "\r\n";

		return t_body_textfooter;
	}


	/** MakeBodyString_Header
	*/
	STLString MakeBodyString_Header(const STLString& a_boundarystring,Http_Mode::Id a_mode,const STLString& a_request,const STLString& a_host,s32 a_all_content_size)
	{
		STLString t_body;
	
		//POST ���N�G�X�g�B
		{
			if(a_mode == Http_Mode::Post){
				t_body += "POST ";
			}else{
				t_body += "GET ";
			}
			t_body += a_request;
			t_body += " HTTP/1.1";
			t_body += "\r\n";
		}

		//Host: ���z�T�[�o�ݒ�B
		{
			t_body += "Host: ";
			t_body += a_host;
			t_body += "\r\n";
		}

		//Connection: �����ڑ��ݒ�B
		{
			t_body += "Connection: keep-alive";
			t_body += "\r\n";
		}

		//Content-Length: �R���e���c�T�C�Y�B
		if(a_mode == Http_Mode::Post){
			char t_temp[32];
			t_body += "Content-Length: ";
			t_body += VASTRING(t_temp,COUNTOF(t_temp),"%ld",a_all_content_size);
			t_body += "\r\n";
		}

		//Cache-Control: �L���b�V���ݒ�B
		t_body += "Cache-Control: no-cache";
		t_body += "\r\n";

		//Accept: ��M�\MIME�B
		t_body += "Accept: */*";
		t_body += "\r\n";

		//User-Agent: �u���E�U�o�[�W�����B
		t_body += "User-Agent: brownie x.x.x";//TODO:
		t_body += "\r\n";

		//Content-Type: �}���`�p�[�g�f�[�^�B
		if(a_mode == Http_Mode::Post){
			t_body += "Content-Type: multipart/form-data; boundary=";
			t_body += "----" + a_boundarystring;
			t_body += "\r\n";
		}

		//Accept-Encoding: �����k�B
		t_body += "Accept-Encoding: identity";
		t_body += "\r\n";

		//Accept-Language: �p��B
		t_body += "Accept-Language: en";
		t_body += "\r\n";

		//�I�[�B
		t_body += "\r\n";

		return t_body;
	}


	/** MakeBodyString_PostDataFooter
	*/
	STLString MakeBodyString_PostDataFooter(const STLString& a_boundarystring)
	{
		STLString t_postdata_footer;

		t_postdata_footer += "--";
		t_postdata_footer += "----" + a_boundarystring;
		t_postdata_footer += "--";

		//�I�[�B
		t_postdata_footer += "\r\n";

		return t_postdata_footer;
	}


}}
#endif

