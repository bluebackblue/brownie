CALL ..\..\..\setting.bat

%COVERITY% --dir cov-int "%MSBUILD%" /t:Rebuild brownie.sln

@PAUSE
