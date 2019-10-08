/// \file random_signal_generator.h
/// \brief Defines the random_signal_generator class.
#ifndef RANDOM_SIGNAL_GENERATOR_H
#define RANDOM_SIGNAL_GENERATOR_H

#include <cstdint>
#include <vector>
#include <string>

/// \brief Includes all PCD software.
namespace pcd
{
/// \brief A class for generating random signals.
class random_signal_generator
{
public:

    // PARAMETERS

    /// \brief The number of points to create for the signal.
    /// \details This specifies the length of the generated signal as a number of points.
    uint32_t n_points;
    /// \brief The desired mean of the signal.
    /// \details This specifies the average amplitude of the generated signal.
    double desired_mean;
    /// \brief The desired standard deviation of the signal.
    /// \details This specifies the standard deviation of the generated signal's amplitude from desired_mean.
    double desired_standard_deviation;
    /// \brief (OPTIONAL) The number of basis vectors used to create the signal. DEFAULT = 50
    /// \details This controls the number of random sine waves that are superimposed to create the random signal.
    /// More bases increase the complexity of the signal but takes longer to compute.
    uint8_t n_bases;
    /// \brief (OPTIONAL) The maximum frequency of the signal's content, in Hz. DEFAULT = 10.0
    /// \details This controls the maximum number of peaks/valleys in the signal over the specified number of points.
    double max_frequency;
    /// \brief (OPTIONAL) The amount of noise to superimpose on the signal, in percentage of the desired standard deviation. DEFAULT = 0.0
    /// \details This enables Gaussian (white) noise to be added to the random signal.
    double noise_percentage;


    // CONSTRUCTORS

    /// \brief Instantiates a new random_signal_generator.
    /// \param n_points The number of points desired in the generated signal.
    /// \param desired_mean The desired mean value of the generated signal.
    /// \param desired_standard_deviation The desired standard deviation of the generated signal.
    random_signal_generator(uint32_t n_points, double desired_mean, double desired_standard_deviation);
    ~random_signal_generator();


    // METHODS

    /// \brief Generates a new randomized signal with the currently set parameters.
    /// \param signal A vector for storing the generated signal.
    void generate(std::vector<double>& signal);

private:
    class impl;
    impl* pimpl;
};

}

#endif