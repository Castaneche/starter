cmake_minimum_required(VERSION 3.13.0)

#===============================================================================
# USER OPTIONS
#===============================================================================

option(GUI_NATIVE_DIAGS      "Turn ON to build native file dialog support" ON)
option(UTIL_DEFAULT_LOG      "Turn ON to enable a default log output to console/file" ON)

#===============================================================================
# FRONT MATTER
#===============================================================================

# create project
project(gui VERSION 1.0.0 LANGUAGES C CXX)

set(CXX_CMAKE_STANDARD 14)
set(CXX_CMAKE_STANDARD_REQUIRED ON)

#===============================================================================
# 3RD PARTY DEPENDENCIES
#===============================================================================

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(3rdparty/glfw)
install(TARGETS glfw EXPORT gui-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# GLAD
add_subdirectory(3rdparty/glad)
install(TARGETS glad EXPORT gui-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# NATIVE FILE DIALOG
if (GUI_NATIVE_DIAGS)
    add_subdirectory(3rdparty/nativefiledialog-extended)
	install(TARGETS nfd EXPORT gui-targets
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			)
endif()

# FMT
add_subdirectory(3rdparty/fmt)
install(TARGETS fmt EXPORT gui-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# CXXOPTS
set(CXXOPTS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cxxopts/include)

# IMGUI
set(IMGUI_HEADERS
    3rdparty/imgui/imconfig.h
    3rdparty/imgui/imgui_internal.h
    3rdparty/imgui/imgui.h
    3rdparty/imgui/imstb_rectpack.h
    3rdparty/imgui/imstb_textedit.h
    3rdparty/imgui/imstb_truetype.h
    3rdparty/imgui/imgui_stdlib.h
)

set(IMGUI_SRC
    3rdparty/imgui/imgui_demo.cpp
    3rdparty/imgui/imgui_draw.cpp
    3rdparty/imgui/imgui_widgets.cpp
    3rdparty/imgui/imgui.cpp
    3rdparty/imgui/imgui_stdlib.cpp
    3rdparty/imgui/imgui_tables.cpp
    3rdparty/imgui/backends/imgui_impl_glfw.cpp
    3rdparty/imgui/backends/imgui_impl_glfw.h
    3rdparty/imgui/backends/imgui_impl_opengl3.cpp
    3rdparty/imgui/backends/imgui_impl_opengl3.h
	3rdparty/imgui/backends/imgui_impl_win32.cpp
	3rdparty/imgui/backends/imgui_impl_win32.h
)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui)

set(IMPLOT_HEADERS 3rdparty/implot/implot.h 3rdparty/implot/implot_internal.h)
set(IMPLOT_SRC     3rdparty/implot/implot.cpp 3rdparty/implot/implot_items.cpp 3rdparty/implot/implot_demo.cpp)
set(IMPLOT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/implot)


#===============================================================================
# CREATE LIBRARY
#===============================================================================

# create target and add an alias
add_library(gui "")
set_target_properties(gui PROPERTIES DEBUG_POSTFIX -d)
target_compile_features(gui PUBLIC cxx_std_17)
install(TARGETS gui EXPORT gui-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
set_target_properties(gui PROPERTIES OUTPUT_NAME "gui")

# defines
target_compile_definitions(gui PUBLIC GUI IMGUI_IMPL_OPENGL_LOADER_GLAD)
if(GUI_NATIVE_DIAGS)
	target_compile_definitions(gui PUBLIC NATIVE_DIAGS)
endif()

# add source files
add_subdirectory(src/Gui)
add_subdirectory(src/Util)

target_sources(gui PRIVATE ${IMGUI_SRC} ${IMGUI_HEADERS})
target_sources(gui PRIVATE ${IMPLOT_SRC} ${IMPLOT_HEADERS})

# add include files
file(GLOB_RECURSE GUI_INCLUDE "include/*.hpp" "include/*.inl" "include/*.h")
target_sources(gui PRIVATE ${GUI_INCLUDE}) # for intellisense
target_include_directories(gui
	PUBLIC
		$<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${IMGUI_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${IMPLOT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CXXOPTS_INCLUDE_DIR}>
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# link libraries
target_link_libraries(gui PUBLIC glfw)
target_link_libraries(gui PUBLIC glad)
if(GUI_NATIVE_DIAGS)
	target_link_libraries(gui PUBLIC nfd)
endif()
if (WIN32)
    target_link_libraries(gui PUBLIC Shcore)
endif()
if(CMAKE_SYSTEM MATCHES "Linux")
    # https://techoverflow.net/2019/04/17/how-to-fix-gcc-undefined-reference-to-std-experimental-filesystem/
    target_link_libraries(gui PUBLIC GL stdc++fs)
endif()

# enable logger
if (UTIL_DEFAULT_LOG)
    target_compile_definitions(gui PUBLIC DEFAULT_LOG)
endif()

# link libraries
target_link_libraries(gui PUBLIC fmt::fmt)


if(UNIX)
    target_link_libraries(util PUBLIC pthread)
    if(NOT APPLE)
        target_link_libraries(util PUBLIC rt)
    endif()
endif()
if(WIN32)
    target_link_libraries(gui PUBLIC winmm pdh version)
endif()

#===============================================================================
# INSTALL
#===============================================================================

if (MSVC)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(GUI_INSTALL_POSTFIX "") # 64 bit Windows is default
    else()
        set(GUI_INSTALL_POSTFIX "-x86")
    endif()
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}${GUI_INSTALL_POSTFIX}")

# install headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY 3rdparty/glad/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${IMGUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${IMPLOT_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${CXXOPTS_INCLUDE_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})