# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 4.4.3)

# Reject any attempt to use a toolchain file. We must not use one because
# we could be downloading it here. If the CMAKE_TOOLCHAIN_FILE environment
# variable is set, the cache variable will have been initialized from it.
unset(CMAKE_TOOLCHAIN_FILE CACHE)
unset(ENV{CMAKE_TOOLCHAIN_FILE})

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(ftxui-populate NONE)



include(ExternalProject)
ExternalProject_Add(ftxui-populate
                     "UPDATE_DISCONNECTED" "False" "DOWNLOAD_EXTRACT_TIMESTAMP" "TRUE" "EXTERNALPROJECT_INTERNAL_ARGUMENT_SEPARATOR" "URL" "https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v6.1.9.tar.gz"
                    SOURCE_DIR          "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-src"
                    BINARY_DIR          "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


