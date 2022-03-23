target_sources(gui
    PRIVATE
    Application.cpp
    Color.cpp
    imgui_custom.cpp
)

if(GUI_NATIVE_DIAGS)
    target_sources(gui PRIVATE Native.cpp)
endif()

add_subdirectory(Fonts)
