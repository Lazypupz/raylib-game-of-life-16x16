@echo off
set C_COMPILER=C:\raylib\w64devkit\bin\gcc.exe
set CXX_COMPILER=C:\raylib\w64devkit\bin\g++.exe
cmake -G "Ninja" -DCMAKE_C_COMPILER=%C_COMPILER% -DCMAKE_CXX_COMPILER=%CXX_COMPILER% -S . -B build
cmake --system-information | findstr "CMAKE_C_COMPILER"
