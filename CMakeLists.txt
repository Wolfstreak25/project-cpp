cmake_minimum_required(VERSION 3.15)
project(MySolution CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure SFML search path
list(APPEND CMAKE_PREFIX_PATH "C:/SFML")

# Add the project subdirectories
add_subdirectory(Engine)
add_subdirectory(Timber)
