cmake_minimum_required(VERSION 3.20)
project(ImageTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to an optimized build (Release = -O3) if no build type was given
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ------------------------------------------------------------------
# FTXUI is downloaded and built automatically the first time you
# configure. Same version as P01. (Needs internet once.)
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

add_executable(imgtool src/main.cpp)

# SYSTEM: the provided stb headers are third-party code. Marking the
# folder as a system include hides *their* warnings so you only see
# warnings about *your* code.
target_include_directories(imgtool SYSTEM PRIVATE include)

# We only need FTXUI's dom (elements) and screen (printing) parts.
target_link_libraries(imgtool PRIVATE ftxui::dom ftxui::screen)

# Same warning flags as the old g++ command. These apply to your code.
target_compile_options(imgtool PRIVATE -Wall -Wextra -pedantic)

# Windows (MSYS2 g++): bake the runtime into the .exe so it runs outside
# the MSYS2 shell without "libstdc++-6.dll not found" errors.
if(MINGW)
  target_link_options(imgtool PRIVATE -static)
endif()
