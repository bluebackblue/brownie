

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Modeling File
*/

void* malloc(size_t a_size)
{
	return __coverity_alloc__(a_size);
}

