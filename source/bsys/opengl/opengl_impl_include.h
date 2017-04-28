#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * @brief OpenGLÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#if(BSYS_OPENGL_ENABLE)

	#define GLEW_STATIC

	#include <glew-2.0.0/include/GL/glew.h>
	#include <glfw-3.2.1/include/GLFW/glfw3.h>
	#include <glfw-3.2.1/include/GLFW/glfw3native.h>

#endif

