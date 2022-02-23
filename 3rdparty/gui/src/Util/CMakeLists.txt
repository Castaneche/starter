target_sources(gui
    PRIVATE
    System.cpp
    Console.cpp
)

add_subdirectory(Timing)
add_subdirectory(Logging)
add_subdirectory(Concurrency)

