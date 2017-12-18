CALL ..\..\..\setting.bat

%COVERITY% --dir cov-int %MSBUILD% /t:rebuild brownie.sln

@PAUSE
