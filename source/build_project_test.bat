CALL ..\..\..\setting.bat

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (
			@REM �w�b�_�[�ݒ�B
			@ECHO #define DEF_TEST_AUTO ^(1^) > .\project_test\brownie_config\test.h
			@ECHO #define DEF_TEST_INDEX ^(%%D^) >> .\project_test\brownie_config\test.h

			@REM �r���h�B
			%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P

			@REM �ړ��B
			move .\bin\%%P\%%C\brownie.exe brownie_%%P_%%C_%%D.exe
		)
	)
)

@REM �w�b�_�[�߂��B
@ECHO #define DEF_TEST_AUTO ^(0^) > .\project_test\brownie_config\test.h
@ECHO #define DEF_TEST_INDEX ^(0^) >> .\project_test\brownie_config\test.h

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (

			IF EXIST brownie_%%P_%%C_%%D.exe (
				@ECHO RUN : brownie_%%P_%%C_%%D.exe
				brownie_%%P_%%C_%%D.exe
			) ELSE (
				@ECHO ERROR : brownie_%%P_%%C_%%D.exe
			)

		)
	)
)

