@echo off

%~d0
cd /d %~dp0



:: 如果有错误就退出
rmdir /S /Q build >nul 2>&1
mkdir build
cd build
::cmake -G "Visual Studio 11 2012" .. || exit /B 1
cmake -G "Visual Studio 15 2017" .. || exit /B 1
cmake --build . --config Release || exit /B 1
::xcopy Release\cpp_python.dll .. /Y
cd ..
::rmdir /S /Q build
encodingdemo.exe || exit /B 1