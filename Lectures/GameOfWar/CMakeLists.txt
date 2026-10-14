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
# The War application
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
