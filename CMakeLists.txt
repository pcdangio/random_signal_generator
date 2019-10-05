cmake_minimum_required(VERSION 3.5)

# Define project.
project(random_signal_generator)

# Set up includes.
include_directories(include)

# Build library.
add_library(pcd-random_signal_generator STATIC src/random_signal_generator.cpp src/impl.cpp)

# Install library.
install(TARGETS pcd-random_signal_generator DESTINATION lib)