build-tcc.bat
xcopy ./include %1 /S /Y /E /I
xcopy ./library %1 /S /Y /E /I
xcopy ./libtcc.dll %1 /Y