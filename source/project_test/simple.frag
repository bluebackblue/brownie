#version 400

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGLÅB
*/


/** a_vertex_color
*/
smooth in vec4 a_vertex_color;


/** èoóÕÅB
*/
out vec4 fg_FragColor;


/** main
*/
void main(void)
{
	/** fg_FragColor
	*/
	fg_FragColor = a_vertex_color;
}

