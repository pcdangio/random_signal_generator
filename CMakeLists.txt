cmake_minimum_required(VERSION 3.5)

# Define project.
project(random_signal_generator
        VERSION 1.0.0)

# Set up includes.
include_directories(include)
include_directories(external/cxxopts/include)

# Build library.
add_library(pcd-random_signal_generator STATIC src/random_signal_generator.cpp src/impl.cpp)

# Build executable.
add_executable(random_signal_generator src/main.cpp)
target_link_libraries(random_signal_generator pcd-random_signal_generator)

# Install library.
set_target_properties(pcd-random_signal_generator PROPERTIES PUBLIC_HEADER include/random_signal_generator.h)
install(TARGETS pcd-random_signal_generator EXPORT pcd-random_signal_generatorConfig
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/pcd)

# Install CMake config file.
install(EXPORT pcd-random_signal_generatorConfig DESTINATION share/cmake/pcd-random_signal_generator)