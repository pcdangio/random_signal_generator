# random_signal_generator

random_signal_generator is a c++ library utility that generates a smooth, random data signal.

Randomly generated signals are useful data sets for testing and tuning algorithms.  Common applications include:
- Machine Learning
- Signal Processing
- Control Theory
- Forecasting

**License:** [MIT](https://choosealicense.com/licenses/mit/)

## Table of Contents:
1. [Installation](#installation): How to install the utility on your system.
2. [Usage](#usage): How to use the library in your code.
3. [How It Works](#howitworks): Explains how the random signals are generated.

## 1: Installation <a id="installation"></a>

First, download the latest source code from [GitHub](https://github.com/pcdangio/random_signal_generator/releases).

Next, run the following commands in the repo's directory to build the library from source and install it to your system:

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

This will build and install the library to the default CMAKE_INSTALL_PREFIX path, which is:
- **Linux:** ```/usr/local```
- **Windows:** ```C:/Program Files/random_signal_generator```

You may change the install path by passing ```-DCMAKE_INSTALL_PREFIX "some_path"``` when calling cmake.

## 2: Usage <a id="usage"></a>

This section will explain how to use the library within your project.

### 2.1: Code

The following example displays how to use the utility:

```cpp
#include <pcd/random_signal_generator.h>

int main(int argc, char** argv)
{
    // These parameters are required for every random_signal_generator:
    // - n_points: Controls the length of the signal as a number of points.
    // - desired_mean: The desired average "y" value of the signal.
    // - desired_standard_deviation: The desired spread of "y" values in the random signal.
    int n_points = 200;
    double desired_mean = 35;
    double desired_standard_deviation = 1;

    // Instantiate a random_signal_generator.
    pcd::random_signal_generator rsg(n_points, desired_mean, desired_standard_deviation);

    // The required parameters listed above can be changed at any time if desired:
    // rsg.n_points = 200;
    // rsg.desired_mean = 42.6;
    // rsg.desired_standard_deviation = 5.0;

    // The following parameters are optional, and can be set/changed at any time. See documentation for full explanations.
    // rsg.n_bases: The number of basis vectors used to generate the random signal. Default value is 50.
    // rsg.max_frequency: The maximum possible frequency (in Hz) of the basis vectors. Default value is 10.0 Hz.
    // rsg.noise_percentage: The amount of Guassian noise to add to the random signal, as a decimal percentage of the desired standard deviation. Default value is 0.

    // Generate the random signal.
    // First, create an empty vector for storing the generated signal.
    std::vector<double> random_signal;
    // Next, use the utility to actually generate the signal and populate it in the vector.
    rsg.generate(random_signal);

    // random_signal now contains a vector of points that represent the generated random signal.

    return 0;
}
```

### 2.2: Compiling

The following example shows how to build your project on Linux and link it against the pcd-random_signal_generator static library:

**NOTE** This example assumes that you have installed the library and it's headers to a location on your library PATH.

```cmake
cmake_minimum_required(VERSION 3.5)

project(rsg_test)

add_executable(main main.cpp)
target_link_libraries(main libpcd-random_signal_generator.a)
```

## 3: How It Works <a id="howitworks"></a>

This utility leverages Fourier Composition to generate random signals.

[Fourier Series](https://en.wikipedia.org/wiki/Fourier_series) analysis can be used to decompose any periodic signal into an infinite number of sine waves.  It then stands that you can use a series of sine waves to compose a new signal.  The random_signal_generator library uses this concept to generate pseudo-random signals.  The algorithm generates a series of random sine waves, which are then combined into a new signal.

Random sine waves are calculated by choosing a random amplitude, frequency, and phase offset for each wave.  It is important to note that this algorithm differs from standard Fourier Composition in that the sine waves are NOT harmonic.  This limitation allows for non-periodic random signals to be generated.  Another feature of this algorithm is that lower frequency waves tend to have higher amplitude, which gives more base structure to the generated signal (e.g. rising, falling, etc.).

Once the random sine waves are generated, they are superimposed (added) together to create the random signal that is output by the utility.