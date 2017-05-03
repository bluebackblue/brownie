#version 400

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** ライト。ビュー。プロジェクション。
*/
uniform mat4 a_view_projection;


/** 頂点。
*/
in vec3 a_position;


/** カラー。
*/
in vec4 a_color;


/** カラー。
*/
smooth out vec4 a_vertex_color;


/** main
*/
void main(void)
{
	vec4 t_new_vertex = vec4(a_position.x,a_position.y,a_position.z,1.0);

	gl_Position = a_view_projection * t_new_vertex;

	a_vertex_color = a_color;
}

