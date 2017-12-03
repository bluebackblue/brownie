# brownie library
C++ library

## License
MIT License
https://github.com/bluebackblue/brownie/blob/master/LICENSE

## blib
low-level library

## bsys
mid-level library

## folder structure
フォルダ構造
* brownie
* _ source
* ___ blib
* ___ bsys
* ___ premake.bat
* ___ project_test
* _____ brownie_config
* _______ brownie_config.h
* _______ user_customize.h
* _ premake
* _ licence
* ___ fovehmd
* ___ glew
* ___ glfw
* ___ libpng
* ___ mmd
* ___ saba
* ___ zlib
* sdk
* _ gl
* ___ glew-2.0.0
* ___ glfw-3.2.1
* _ fovehmd
* ___ FOVE SDK 0.11.4
* _ png
* ___ lpng1628

## include path
以下のインクルードパスを前提にしています。
* ./brownie/source/project_test
* ./sdk

## sample solution
サンプル起動までの手順。
* step 1: RUN  ./brownie/source/premake.bat
* step 2: OPEN ./brownie/source/brownie.sln
* step 3: EDIT ./brownie/source/project_test/brownie_config/user_customize.h

## user_customize.h
テストデファインの各種説明
* TEST0: デバッグログ、デバッグブレイク、アサート。
* TEST1: 型、リスト。
* TEST2: ファイル、ＪＳＯＮ。
