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
    random_signal_generator::desired_standard_deviation = desired_standard_deviation;

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
void random_signal_generator::generate(std::vector<double>& signal)
{
    // Make sure the vector is empty.
    signal.clear();
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
    for(uint8_t b = 0; b < random_signal_generator::n_bases; b++)
    {
        // Create new basis.
        basis new_basis;
        // Get random frequency from 0 to max_frequency.
        new_basis.frequency = random_signal_generator::pimpl->random_zero_one() * random_signal_generator::max_frequency;
        // Get random phase offset from 0 to 2*PI.
        new_basis.phase_offset = random_signal_generator::pimpl->random_zero_one() * 2.0 * M_PI;
        // Get random amplitude from 0 to 1/frequency.  This gives more power to lower frequencies.
        new_basis.amplitude = random_signal_generator::pimpl->random_zero_one() / new_basis.frequency;
        // Add basis to bases.
        bases.push_back(new_basis);
        }

    // Create signal.
    // Iterate over points.
    // Preallocate values for speed.
    std::vector<basis>::iterator basis;
    double point = 0;
    double t = 0;
    double N = static_cast<double>(random_signal_generator::n_points);
    double sum = 0;
    double squared_sum = 0;
    // Conduct iterations.
    for(uint32_t n = 0; n < random_signal_generator::n_points; n++)
    {
        // Build up the point via superposition of the basis vectors.
        // Initialize point.
        point = 0;
        // Calculate t as time in single period.
        t = static_cast<double>(n) / (N-1);
        // Iterate over the bases.
        for(basis = bases.begin(); basis != bases.end(); basis++)
        {
            point += basis->amplitude * std::sin(basis->phase_offset + basis->frequency*2.0*M_PI*t);
        }
        // Add point to the vector.
        signal.push_back(point);
        // Add point to mean and standard deviation calculations.
        sum += point;
        squared_sum += point*point;
    }

    // Scale signal to desired mean and standard deviation.
    // Calculate mean and standard deviation.
    double mean = sum / N;
    double standard_deviation = std::sqrt((squared_sum-2*mean*sum+N*mean*mean)/N);
    // Calculate scale factor for standard deviation adjustment.
    double stdev_scale = random_signal_generator::desired_standard_deviation / standard_deviation;
    // Iterate over points to make adjustments.
    bool add_noise = std::abs(random_signal_generator::noise_percentage) > std::numeric_limits<double>::epsilon();
    for(auto point_it = signal.begin(); point_it != signal.end(); point_it++)
    {
        *point_it = (*point_it - mean) * stdev_scale + random_signal_generator::desired_mean;
        // Add noise to the point if specified noise percentage is not zero.
        if(add_noise)
        {
            *point_it += random_signal_generator::pimpl->random_pm_one() * random_signal_generator::noise_percentage * random_signal_generator::desired_standard_deviation;
        }
    }
}