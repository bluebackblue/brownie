CALL ..\..\..\setting.bat

FOR /F %%D IN (testdefine.txt) DO (
	FOR /F %%C IN (configuration.txt) DO (
		FOR /F %%P IN (platform.txt) DO (
			@REM ヘッダー設定。
			@ECHO #define DEF_TEST_AUTO ^(1^) > .\project_test\brownie_config\test.h
			@ECHO #define DEF_TEST_INDEX ^(%%D^) >> .\project_test\brownie_config\test.h

			@REM ビルド。
			%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P >> log.txt

			@REM 移動。
			move .\bin\%%P\%%C\brownie.exe brownie_%%P_%%C_%%D.exe
		)
	)
)

@REM ヘッダー戻す。
@ECHO #define DEF_TEST_AUTO ^(0^) > .\project_test\brownie_config\test.h
@ECHO #define DEF_TEST_INDEX ^(0^) >> .\project_test\brownie_config\test.h

FOR /F %%D IN (testdefine.txt) DO (
	FOR /F %%C IN (configuration.txt) DO (
		FOR /F %%P IN (platform.txt) DO (

			IF EXIST brownie_%%P_%%C_%%D.exe (
				@ECHO RUN : brownie_%%P_%%C_%%D.exe
				brownie_%%P_%%C_%%D.exe
			) ELSE (
				@ECHO ERROR : brownie_%%P_%%C_%%D.exe
			)

		)
	)
)

