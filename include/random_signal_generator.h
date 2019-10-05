#ifndef RANDOM_SIGNAL_GENERATOR_H
#define RANDOM_SIGNAL_GENERATOR_H

#include <cstdint>
#include <vector>
#include <string>

namespace pcd
{

class random_signal_generator
{
public:

    // PARAMETERS

    /// \brief The number of points to create for the signal.
    uint32_t n_points;
    /// \brief The desired mean of the signal.
    double desired_mean;
    /// \brief The desired standard deviation of the signal.
    double desired_standard_deviation;
    /// \brief The number of basis vectors used to create the signal.
    uint8_t n_bases;
    /// \brief The maximum frequency of the signal's content.
    double max_frequency;
    /// \brief The amount of noise to superimpose on the signal, in percentage of the standard deviation.
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
    /// \return A vector containing the generated signal.
    std::vector<double>& generate();

private:
    class impl;
    impl* pimpl;
};

}

#endif