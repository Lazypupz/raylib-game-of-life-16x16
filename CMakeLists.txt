
cmake_minimum_required(VERSION 3.10)
project(GameOfLife VERSION 0.1.0 LANGUAGES C CXX)


link_directories(C:/raylib/raylib/src/raylib.h)
include(CTest)
enable_testing()

add_executable(GameOfLife main.cpp)

target_link_libraries(GameOfLife raylib timerapi kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32 wimn)
set_property(TARGET GameOfLife PROPERTY CXX_STANDARD 17)