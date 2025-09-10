cmake_minimum_required(VERSION 3.21)
project(qt-button-demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Auto-generate MOC files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add executable
add_executable(qt-button-demo
    main.cpp
)

# Link Qt libraries
target_link_libraries(qt-button-demo
    Qt6::Core
    Qt6::Widgets
)

# Copy QSS files to build directory
configure_file(${CMAKE_SOURCE_DIR}/light_theme.qss ${CMAKE_BINARY_DIR}/light_theme.qss COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/dark_theme.qss ${CMAKE_BINARY_DIR}/dark_theme.qss COPYONLY)

# Set output directory
set_target_properties(qt-button-demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

