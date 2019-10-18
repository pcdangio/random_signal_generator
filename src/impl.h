/// \file impl.h
/// \brief Defines the impl class.
#ifndef IMPL_H
#define IMPL_H

#include "pcd/random_signal_generator/random_signal_generator.h"

#include <random>

/// \brief The private implementation class for the random_signal_generator.
class pcd::random_signal_generator::impl
{
public:
    /// \brief Initializes a new implementation class.
    impl();

    /// \brief Generates a random number between 0 and 1.
    double random_zero_one();
    /// \brief Generates a random number between -1 and 1.
    double random_pm_one();

private:
    /// \brief The random device for initializing.
    std::random_device random_device;
    /// \brief A distribution for random numbers between 0 and 1.
    std::uniform_real_distribution<double> distribution_zero_one;
    /// \brief A distribution for random numbers between -1 and 1.
    std::uniform_real_distribution<double> distribution_pm_one;
    /// \brief A random number generator.
    std::mt19937 random_generator;
};

#endif