cmake_minimum_required(VERSION 3.15)
project(FiguresProject)

# Явно указываем C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка компилятора для Visual Studio
if(MSVC)
    add_compile_options(/std:c++latest)  # Для MSVC
else()
    add_compile_options(-std=c++20)      # Для GCC/Clang
endif()

# Директории с исходными файлами
include_directories(include)

# Основная программа
add_executable(FiguresApp
    main.cpp
)

# Скачивание и настройка GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Для Windows может потребоваться установка Windows SDK
if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

# Тестовый исполняемый файл
add_executable(FiguresTests
    tests/test.cpp
)

# Связывание тестов с GTest
target_link_libraries(FiguresTests gtest gtest_main)
target_include_directories(FiguresTests PRIVATE include)

# Добавление тестов в CTest
include(GoogleTest)
gtest_discover_tests(FiguresTests)