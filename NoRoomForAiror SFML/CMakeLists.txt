cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(NOROOMFORAIROR)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(NoRoomForAiror main.cpp TextBox.h)
target_link_libraries(NoRoomForAiror sfml-graphics sfml-audio)
