#version 400

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL�B
*/


/** ���C�g�B�r���[�B�v���W�F�N�V�����B
*/
uniform mat4 a_view_projection;


/** ���_�B
*/
in vec3 a_position;


/** �J���[�B
*/
in vec4 a_color;


/** �J���[�B
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

