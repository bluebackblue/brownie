

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./http_type.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** MakeBodyString_BinaryHeader
	*/
	STLString MakeBodyString_BinaryHeader(const STLString& a_boundarystring,const STLString& a_formname,const STLString& a_filename)
	{
		STLString t_body_binaryheader;

		//バウンダリ文字列。
		{
			//------****<0D 0A>
			t_body_binaryheader += "--";
			t_body_binaryheader += "----" + a_boundarystring;
			t_body_binaryheader += "\r\n";
		}

		//Content-Disposition: form-data; name="****"; filename="****.****"<0D 0A>
		{
			t_body_binaryheader += "Content-Disposition: form-data; name=\"";
			t_body_binaryheader += a_formname;
			t_body_binaryheader += "\"; filename=\"";
			t_body_binaryheader += a_filename;
			t_body_binaryheader += "\"";
			t_body_binaryheader += "\r\n";
		}

		//Content-Type: application/octet-stream<0D 0A>
		{
			t_body_binaryheader += "Content-Type: application/octet-stream";
			t_body_binaryheader += "\r\n";
		}

		//<0D 0A>
		{
			t_body_binaryheader += "\r\n";
		}

		return t_body_binaryheader;
	}


	/** MakeBodyString_BinarFooter
	*/
	STLString MakeBodyString_BinarFooter()
	{
		STLString t_body_binaryfooter;

		//<0D 0A>
		t_body_binaryfooter += "\r\n";

		return t_body_binaryfooter;
	}


	/** MakeBodyString_TextHeader
	*/
	STLString MakeBodyString_TextHeader(const STLString& a_boundarystring,const STLString& a_formname)
	{
		STLString t_body_textheader;

		//バウンダリ文字列。
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
	STLString MakeBodyString_Header(const STLString& a_boundarystring,Http_Mode::Id a_mode,const STLString& a_path,const STLString& a_host,s32 a_binary_size)
	{
		STLString t_body;
	
		//POST リクエスト。
		{
			if(a_mode == Http_Mode::Post){
				t_body += "POST ";
			}else{
				t_body += "GET ";
			}
			t_body += a_path;
			t_body += " HTTP/1.1";
			t_body += "\r\n";
		}

		//Host: 仮想サーバ設定。
		{
			t_body += "Host: ";
			t_body += a_host;
			t_body += "\r\n";
		}

		//Connection: 持続接続設定。
		{
			#if(0)
			t_body += "Connection: keep-alive";
			#else
			t_body += "Connection: close";
			#endif

			t_body += "\r\n";
		}

		//Content-Length: コンテンツサイズ。
		if(a_mode == Http_Mode::Post){
			t_body += "Content-Length: ";
			t_body += ToString(a_binary_size);
			t_body += "\r\n";
		}

		//Cache-Control: キャッシュ設定。
		t_body += "Cache-Control: no-cache";
		t_body += "\r\n";

		//Accept: 受信可能MIME。
		t_body += "Accept: */*";
		t_body += "\r\n";

		//User-Agent: ブラウザバージョン。
		t_body += "User-Agent: ";
		t_body += BSYS_HTTP_USERAGENT;
		t_body += "\r\n";

		//Content-Type: マルチパートデータ。
		if(a_mode == Http_Mode::Post){
			t_body += "Content-Type: multipart/form-data; boundary=";
			t_body += "----" + a_boundarystring;
			t_body += "\r\n";
		}

		//Accept-Encoding: 未圧縮。
		t_body += "Accept-Encoding: identity";
		t_body += "\r\n";

		//Accept-Language: 英語。
		t_body += "Accept-Language: en";
		t_body += "\r\n";

		//終端。
		t_body += "\r\n";

		return t_body;
	}


	/** MakeBodyString_PostBinarFooter
	*/
	STLString MakeBodyString_PostBinarFooter(const STLString& a_boundarystring)
	{
		STLString t_postbinary_footer;

		//バウンダリ文字列。
		t_postbinary_footer += "--";
		t_postbinary_footer += "----" + a_boundarystring;
		t_postbinary_footer += "--";

		//終端。
		t_postbinary_footer += "\r\n";

		return t_postbinary_footer;
	}


}}
#endif

