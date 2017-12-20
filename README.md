# brownie library
C++ library

## License
MIT License
https://github.com/bluebackblue/brownie/blob/master/LICENSE

## coverity scan
<a href="https://scan.coverity.com/projects/brownie">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/14637/badge.svg"/>
</a>

## blib
low-level library

## bsys
mid-level library

## folder structure
フォルダ構造
* brownie
* _ source
* ___ blib [低レベルライブラリ]
* ___ bsys [中レベルライブラリ]
* ___ premake.bat
* ___ project_test [テストプロジェクト]
* _____ brownie_config
* _______ brownie_config.h
* _______ user_customize.h
* _ premake [ビルドツール]
* _ licence [使用ライセンス関連ファイル]
* ___ fovehmd
* ___ glew
* ___ glfw
* ___ libpng
* ___ mmd
* ___ saba
* ___ zlib
* sdk [blib/bsys内で使用する外部ミドルウェアの設置場所(このリポジトリには含まれていません)]
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

## test project
テストプロジェクト起動までの手順。
* step 1: RUN  ./brownie/source/premake.bat
* step 2: OPEN ./brownie/source/brownie.sln
* step 3: EDIT ./brownie/source/project_test/brownie_config/user_customize.h

## user_customize.h
テストデファインの各種説明
* DEF_TEST0: デバッグログ、デバッグブレイク、アサート。
* DEF_TEST1: 型、リスト。
* DEF_TEST2: ファイル、ＪＳＯＮ。

## brownie_config.h
制御デファインの各種説明、デフォルト値の記述

