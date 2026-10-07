cmake_minimum_required(VERSION 3.20)
project(CardGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------
# FTXUI is downloaded and built automatically the first time you
# configure. You do NOT install it yourself. (Needs internet once.)
# ------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(ftxui
  URL https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v6.1.9.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(ftxui)

set(FTXUI_LIBS ftxui::component)  # pulls in ftxui::dom and ftxui::screen

# Milestone 0: toolchain check. Build and run this first.
add_executable(check check/check.cpp)
target_link_libraries(check PRIVATE ${FTXUI_LIBS})

# The game. Every .cpp in src/ is compiled automatically.
# (Added a new .cpp file? Re-run the cmake configure step.)
file(GLOB GAME_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game ${GAME_SOURCES})
target_include_directories(game PRIVATE include)
target_link_libraries(game PRIVATE ${FTXUI_LIBS})

# Windows (MSYS2 g++): bake the runtime into the .exe so it runs outside
# the MSYS2 shell without "libstdc++-6.dll not found" errors.
if(MINGW)
  target_link_options(check PRIVATE -static)
  target_link_options(game  PRIVATE -static)
endif()
