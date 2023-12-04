cmake_minimum_required(VERSION 3.17)
project(NoRoomForAiror)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(NoRoomForAiror Processor.cpp SplayTree.cpp
        Processor.h
        Airline.cpp
        Airline.h
        rapidcsv.h
		TextBox.h
        main.cpp)

target_link_libraries(NoRoomForAiror sfml-graphics sfml-audio)