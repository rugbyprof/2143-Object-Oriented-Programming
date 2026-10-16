cmake_minimum_required(VERSION 3.20)
project(ftxui_sword_swing_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v6.1.9
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(ftxui)

add_executable(sword_swing_demo
  src/main.cpp
  src/battle.cpp
  src/sword_swing_animation.cpp
)
target_include_directories(sword_swing_demo PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_include_directories(sword_swing_demo PRIVATE src)
target_link_libraries(sword_swing_demo PRIVATE
  ftxui::component
  ftxui::dom
  ftxui::screen
)
