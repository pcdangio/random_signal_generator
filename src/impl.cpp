#include "impl.h"

using namespace pcd;

random_signal_generator::impl::impl()
{
    // Set up random distributions and generators.
    random_signal_generator::impl::random_generator = std::mt19937(random_device);
    random_signal_generator::impl::distribution_zero_one = std::uniform_real_distribution<double>(0.0, 1.0);
    random_signal_generator::impl::distribution_pm_one = std::uniform_real_distribution<double>(-1.0, 1.0);
}
double random_signal_generator::impl::random_zero_one()
{
    return distribution_zero_one(random_generator);
}
double random_signal_generator::impl::random_pm_one()
{
    return distribution_pm_one(random_generator);
}