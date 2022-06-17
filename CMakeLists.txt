cmake_minimum_required(VERSION 3.14)

project(IsolinesTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core Svg
  )
find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS Core Svg
  )

find_package(Boost 1.79.0 REQUIRED)

add_executable(IsolinesTest
  main.cpp
  geometry.h
  test_data.h
)
target_link_libraries(IsolinesTest Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Svg Boost::Boost)
