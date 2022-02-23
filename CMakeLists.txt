#CMakeLists.txt

cmake_minimum_required(VERSION 3.13.0)

project("starter")


if(MSVC) 
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries 
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

#use to build with fetch content (need network connection)
#include(FetchContent) 
#FetchContent_Declare(gui GIT_REPOSITORY https://github.com/Castaneche/gui.git) 
#FetchContent_MakeAvailable(gui)

add_executable(starter Main.cpp)
target_link_libraries(starter gui)

add_subdirectory(3rdparty/gui)
add_subdirectory(src)

#Copy res folder in final build directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/res DESTINATION /)