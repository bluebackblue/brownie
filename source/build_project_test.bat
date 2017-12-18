CALL ..\..\..\setting.bat

FOR /F %%C IN (Configuration.txt) DO (
	FOR /F %%P IN (Platform.txt) DO (

		%MSBUILD% brownie.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P;DefineConstants="DEF_TEST"

	)
)

@PAUSE

