#pragma once
#include <filesystem>

#include "Modes.h"

class InputParser
{
public:
    // Parses command line parameters
    static std::pair<Mode, std::string> parse(const int argc, const char* const argv[])
    {
        constexpr int number_of_expected_parameters = 3;

        if (argc != number_of_expected_parameters)
        {
            throw std::invalid_argument("Invalid number of parameters, expected: -f|-r filename");
        }

        const Mode mode = strcmp(argv[1], "-f") == 0 ? Mode::filter : Mode::replace;

        const std::string file_name = argv[2];

        if (!std::filesystem::exists(file_name))
        {
            throw std::invalid_argument(std::string("Input file ") + file_name + " does not exist");
        }

        return { mode, file_name };
    }
};