CALL ..\..\..\setting.bat

FOR /F %%D IN (TestDefine.txt) DO (

	ECHO #define DEF_TEST_INDEX %%D > .\project_test\brownie_config\test.h

)


@PAUSE

@ECHO #define DEF_TEST_INDEX 12 > .\project_test\brownie_config\test.h
%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=Debug;Platform=Win32

@PAUSE



FOR /F %%C IN (Configuration.txt) DO (
	FOR /F %%P IN (Platform.txt) DO (

		%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P;DefineConstants="DEF_TEST_12"

	)
)

@PAUSE

