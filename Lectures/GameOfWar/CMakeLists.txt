cmake_minimum_required(VERSION 3.20)

project(GameOfWar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Static linking for MinGW (Windows) so the .exe runs outside the build shell
if(MINGW)
    add_link_options(-static)
endif()

# --------------------------------------------------
# FTXUI
# --------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    ftxui
    URL https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v6.1.9.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(ftxui)

# --------------------------------------------------
# Lessons 01-07: every examples/NN_*.cpp becomes its own program
# --------------------------------------------------
file(GLOB EXAMPLES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/examples/[0-9]*.cpp"
)

foreach(SOURCE ${EXAMPLES})
    get_filename_component(NAME ${SOURCE} NAME_WE)

    add_executable(${NAME} ${SOURCE})

    target_link_libraries(${NAME} PRIVATE
        ftxui::component
    )
endforeach()

# Lessons 06-07: these programs are built from two .cpp files
target_sources(06_counter PRIVATE examples/Counter.cpp)
target_sources(07_counter_view PRIVATE examples/Counter.cpp)

# --------------------------------------------------
# Lessons 08-16: the War application
# --------------------------------------------------
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
    src/HandView.cpp
    src/Player.cpp
    src/WarGame.cpp
)

target_include_directories(war PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(war PRIVATE
    ftxui::component
)
