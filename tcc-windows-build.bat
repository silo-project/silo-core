cmd /c build-tcc.bat
xcopy include "%1/include" /S /Y /E /I
xcopy lib "%1/lib" /S /Y /E /I
xcopy libtcc.dll "%1" /Y