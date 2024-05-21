cmake_minimum_required(VERSION 3.10)

# Set your project name
project(OS_project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages
find_package(Threads REQUIRED)

# Add your executable
add_executable(MyExecutableproject /home/joudi/OS2_project/main.cpp)

# Link libraries to your executable
target_link_libraries(MyExecutableproject PRIVATE Threads::Threads)