#include "random_signal_generator/random_signal_generator.h"

#include "cxxopts.hpp"
#include <fstream>

void write_output(std::ostream& stream, std::vector<std::vector<double>>& signals)
{
    // Check if signals is empty before continuing.
    // This is needed as we use front() and back().
    if(signals.empty())
    {
        return;
    }

    // Get the number of points in each signal.
    uint32_t n_points = signals.front().size();
    // Get the number of signals.
    uint32_t n_signals = signals.size();

    // Output as CSV.
    for(uint32_t i = 0; i < n_points; i++)
    {
        for(uint32_t j = 0; j < n_signals - 1; j++)
        {
            stream << std::to_string(signals[j][i]) << ',';
        }
        stream << std::to_string(signals.back()[i]) << '\n';
    }
}

int main(int argc, char** argv)
{
    // Set up random_signal_generator with default parameters.
    pcd::random_signal_generator rsg(100, 25.0, 10.0);

    // Set up default output file string.
    std::string output_path = "";

    // Set up default n_signals.
    uint32_t n_signals = 1;

    // Parse user arguments.
    // Set up options.
    cxxopts::Options options("random_signal_generator", "A command line tool for generating random signals.");
    options.add_options()
        ("p,n_points", "The length of the generated signal in data points. DEFAULT: 100", cxxopts::value<uint32_t>())
        ("m,desired_mean", "The desired mean amplitude of the generated signal. DEFAULT: 25.0", cxxopts::value<double>())
        ("d,desired_standard_deviation", "The desired standard deviation in the amplitude of the generated signal. DEFAULT: 10.0", cxxopts::value<double>())
        ("b,n_bases", "The number of bases to use for generating the signal. DEFAULT: 50", cxxopts::value<uint8_t>())
        ("f,max_frequency", "The maximum frequency of the generated signal over number of points specified. DEFAULT: 10.0", cxxopts::value<double>())
        ("n,noise_percentage", "The amount of Gaussian noise to add as a percentage of the desired standard deviation. DEFAULT: 0.0", cxxopts::value<double>())
        ("o,output_file", "The desired CSV output file to write the signal to. If not specified, outputs to screen.", cxxopts::value<std::string>())
        ("s,n_signals", "The number of random signals to generate. DEFAULT: 1", cxxopts::value<uint32_t>())
        ("h,help", "Display help.");
    try
    {
        // Parse options.
        auto arguments = options.parse(argc, argv);
        // Update parameters if provided.
        if(arguments.count("p"))
        {
            rsg.n_points = arguments["p"].as<uint32_t>();
        }
        if(arguments.count("m"))
        {
            rsg.desired_mean = arguments["m"].as<double>();
        }
        if(arguments.count("d"))
        {
            rsg.desired_standard_deviation = arguments["d"].as<double>();
        }
        if(arguments.count("b"))
        {
            rsg.n_bases = arguments["b"].as<uint8_t>();
        }
        if(arguments.count("f"))
        {
            rsg.max_frequency = arguments["f"].as<double>();
        }
        if(arguments.count("n"))
        {
            rsg.noise_percentage = arguments["n"].as<double>();
        }
        if(arguments.count("o"))
        {
            output_path = arguments["o"].as<std::string>();
        }
        if(arguments.count("s"))
        {
            n_signals = arguments["s"].as<uint32_t>();
        }
        if(arguments.count("h"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }
    }
    catch(const cxxopts::OptionParseException& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Create vectors for storing signals.
    std::vector<std::vector<double>> signals;

    // Run the generator.
    for(uint32_t i = 0; i < n_signals; i++)
    {
        std::cout << "Generating signal " << i + 1 << " of " << n_signals << "...\r";
        std::cout.flush();

        std::vector<double> signal;
        signals.push_back(signal);
        rsg.generate(signals[i]);
    }
    std::cout << std::endl << "Done generating signals." << std::endl;

    // Write output.
    if(!output_path.empty())
    {
        std::cout << "Writing to file \"" << output_path << "\"..." << std::endl;
        try
        {
            std::ofstream output_file;
            output_file.open(output_path, std::ios::out);
            write_output(output_file, signals);
            output_file.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return 2;
        }
    }
    else
    {
        std::cout << "Writing to console..." << std::endl;
        write_output(std::cout, signals);
    }

    std::cout << "Done." << std::endl;

    return 0;
}