CALL ..\..\..\setting.bat

@ECHO: > auto_log.txt
@ECHO: > build_log.txt

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (

			@REM �w�b�_�[�쐬�B
			@ECHO #define DEF_TEST_INDEX %%D > .\project_test\brownie_config\test.h

			@REM �r���h�B
			%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P >> build_log.txt

			@REM �ړ��B
			move .\bin\%%P\%%C\brownie.exe brownie_%%P_%%C_%%D.exe
		)
	)
)

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (

			IF EXIST brownie_%%P_%%C_%%D.exe (
				brownie_%%P_%%C_%%D.exe
			) ELSE (
				@ECHO ERROR : brownie_%%P_%%C_%%D.exe >> auto_log.txt
			)

		)
	)
)

@PAUSE

