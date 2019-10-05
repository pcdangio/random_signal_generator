#include "random_signal_generator.h"
#include "impl.h"

#include <random>

using namespace pcd;

// CONSTRUCTORS
random_signal_generator::random_signal_generator(uint32_t n_points, double desired_mean, double desired_standard_deviation)
{
    // Set up pimpl.
    random_signal_generator::pimpl = new random_signal_generator::impl();

    // Store given values.
    random_signal_generator::n_points = n_points;
    random_signal_generator::desired_mean = desired_mean;
    random_signal_generator::desired_standard_deviation;

    // Set defaults for rest.
    random_signal_generator::n_bases = 50;
    random_signal_generator::max_frequency = 10;
    random_signal_generator::noise_percentage = 0.0;
}
random_signal_generator::~random_signal_generator()
{
    // Clean up pimpl.
    delete random_signal_generator::pimpl;
}

// METHODS
std::vector<double>& random_signal_generator::generate()
{
    // Create vector for signal.
    std::vector<double> signal;
    // Reserve enough space for the amount of points.
    signal.reserve(random_signal_generator::n_points);

    // Setup bases.
    // Create vector of bases.
    struct basis
    {
        double frequency;
        double phase_offset;
        double amplitude;
    };
    std::vector<basis> bases;
    bases.reserve(random_signal_generator::n_bases);
    // Generate bases.
    for(uint32_t b = 0; b < random_signal_generator::n_bases; b++)
    {
        // Create new basis.
        basis new_basis;
        // Get random frequency from 0 to max_frequency.
        new_basis.frequency = random_signal_generator::pimpl->random_zero_one() * random_signal_generator::max_frequency;
        // Get random phase offset from 0 to 2*PI.
        new_basis.phase_offset = random_signal_generator::pimpl->random_zero_one() * M_2_PI;
        // Get random amplitude from 0 to 1/frequency.  This gives more power to lower frequencies.
        new_basis.amplitude = random_signal_generator::pimpl->random_zero_one() * 1.0 / new_basis.frequency;
        // Add basis to bases.
        bases.push_back(new_basis);
    }
}