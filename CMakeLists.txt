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
install(TARGETS pcd-random_signal_generator EXPORT pcd-random_signal_generatorConfig
        ARCHIVE DESTINATION lib)
# Install public headers.
install(DIRECTORY include/
        DESTINATION include/pcd)

# Install executable.
install(TARGETS random_signal_generator
        RUNTIME DESTINATION bin)

# Install CMake config file.
install(EXPORT pcd-random_signal_generatorConfig DESTINATION share/cmake/pcd-random_signal_generator)