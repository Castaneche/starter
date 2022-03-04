
# Gui

This repository is a simpler version of [`mahi-gui`](https://github.com/mahilab/mahi-gui.git) tuned to my needs and up to date. It contains :

|**Library**|**Description**|
|---|---|
|[GLFW](https://www.glfw.org/)| Cross-platform windows, OpenGL contexts, and user input.  |
|[glad](https://github.com/Dav1dde/glad)| OpenGL function loader.  |
|[Dear ImGui](https://github.com/ocornut/imgui)| Immediate mode GUI toolkit for rapid prototyping.  |
|[ImPlot](https://github.com/epezent/implot)| ImGui 2D plotting extension.  |  |
|[NFD](https://github.com/btzy/nativefiledialog-extended)| Native file open/save dialogs. |
|[mahi-util](https://github.com/mahilab/mahi-util)| Only parts of the library such as : Clocks, timers, logger, events, formatting, and more. |


## Integration

Using CMake's [`FetchContent`](https://cmake.org/cmake/help/v3.11/module/FetchContent.html):

```cmake
include(FetchContent) 
FetchContent_Declare(gui GIT_REPOSITORY https://github.com/castaneche/gui.git) 
FetchContent_MakeAvailable(gui)

add_executable(my_app "main.cpp")
target_link_libraries(my_app gui)
```

Or by using a subdirectory and calling :
```cmake
add_subdirectory(gui)

target_link_libraries(my_app gui)
add_executable(my_app "main.cpp")
```

### Example Usage

```cpp
// my_app.cpp
#include <Gui.hpp>
#include <Util.hpp>

using namespace gui;
using namespace util;

// Inherit from Application
class MyApp : public Application {
public:
    // 640x480 px window
    MyApp() : Application(640,480,"My App") { }
    // Override update (called once per frame)
    void update() override {
        // App logic and/or ImGui code goes here
        ImGui::Begin("Example");
        if (ImGui::Button("Press Me!"))
          print("Hello, World!"); 
        ImGui::End();
    }
};

int main() {
    MyApp app;
    app.run();
    return 0;
}
```

## Credits

Most of the files in this repository are done by [`epezent`](https://github.com/epezent) at the 
[`MAHI Lab`](https://github.com/mahilab) and all credits go to him and people who contributed to mahi-gui and mahi-util code.