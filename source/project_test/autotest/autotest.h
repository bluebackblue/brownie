#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �����e�X�g�B
*/


/** include
*/
#include "../include.h"


/** AutoTest
*/
class AutoTest
{
private:

	/** capture_request
	*/
	bool capture_request;

public:
	/** constructor
	*/
	AutoTest();

	/** destructor
	*/
	nonvirtual ~AutoTest();

public:
	/** �X�V�B
	*/
	void Update();

};

