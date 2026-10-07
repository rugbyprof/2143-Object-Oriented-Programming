cmake_minimum_required(VERSION 3.20)
project(HiLo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Card, Deck and GameView come from the P01 starter so this example
# uses exactly the same building blocks you do.
set(STARTER ${CMAKE_CURRENT_SOURCE_DIR}/../../starter)

file(GLOB HILO_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(hilo ${HILO_SOURCES} ${STARTER}/src/Card.cpp ${STARTER}/src/Deck.cpp)
target_include_directories(hilo PRIVATE include ${STARTER}/include)
target_link_libraries(hilo PRIVATE ftxui::component)

if(MINGW)
  target_link_options(hilo PRIVATE -static)
endif()
