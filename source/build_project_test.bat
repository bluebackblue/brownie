CALL ..\..\..\setting.bat

@ECHO: > auto_log.txt
@ECHO: > build_log.txt

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (

			@ECHO %%C %%P %%D >> build_log.txt

			@REM �w�b�_�[�쐬�B
			@ECHO #define DEF_TEST_AUTO (1) > .\project_test\brownie_config\test.h
			@ECHO #define DEF_TEST_INDEX %%D >> .\project_test\brownie_config\test.h

			@REM �r���h�B
			%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P

			@REM �ړ��B
			move .\bin\%%P\%%C\brownie.exe brownie_%%P_%%C_%%D.exe
		)
	)
)

@ECHO END >> build_log.txt

FOR /F %%D IN (TestDefine.txt) DO (
	FOR /F %%C IN (Configuration.txt) DO (
		FOR /F %%P IN (Platform.txt) DO (

			IF EXIST brownie_%%P_%%C_%%D.exe (
				@ECHO RUN : brownie_%%P_%%C_%%D.exe >> auto_log.txt
				brownie_%%P_%%C_%%D.exe
			) ELSE (
				@ECHO ERROR : brownie_%%P_%%C_%%D.exe >> auto_log.txt
			)

		)
	)
)


@ECHO END >> auto_log.txt

