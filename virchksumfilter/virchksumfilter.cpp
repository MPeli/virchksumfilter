// virchksumfilter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include "Timer.h"
#include "InputParser.h"
#include "Filter.h"
#include "Replacer.h"

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    // Disables the synchronization between the C and C++ standard streams
    std::ios_base::sync_with_stdio(false);

    try
    {
        Timer timer("Main-loop");

        const auto& [mode, file_name] = InputParser::parse(argc, argv);

        std::cout << "File: " << file_name << ", mode: " << mode << std::endl;

        if (mode == Mode::filter)
        {
            Filter::do_work(mode, file_name);
        }
        else
        {
            Replacer::do_work(mode, file_name);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}