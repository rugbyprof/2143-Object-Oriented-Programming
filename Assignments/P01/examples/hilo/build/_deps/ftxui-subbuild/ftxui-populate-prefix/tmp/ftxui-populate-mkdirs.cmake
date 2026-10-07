# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-src")
  file(MAKE_DIRECTORY "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-src")
endif()
file(MAKE_DIRECTORY
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-build"
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix"
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/tmp"
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src"
  "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/griffin/Library/Mobile Documents/com~apple~CloudDocs/_git_repos/2143-Object-Oriented-Programming/Assignments/P01/examples/hilo/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
