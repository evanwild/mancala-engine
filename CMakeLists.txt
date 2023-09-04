cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(MancalaEngine)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/8a6feabf04bec8fb125e0df0ad1195c42350725f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  MancalaEngine
  src/main.cpp
  src/mancala.cpp
  src/minimax.cpp
)

add_executable(
    EngineTests
    src/unittest.cpp
    src/mancala.cpp
    src/minimax.cpp
)

target_link_libraries(
  EngineTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(EngineTests)
