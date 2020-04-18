#pragma once
#include <string>
#include <unordered_map>
#include <deque>
#include <regex>
#include <iostream>
#include <fstream>

#include "Modes.h"
#include "Timer.h"

class Replacer
{
public:
    // Read standard input, replace some values and print it in reverse
    static void do_work(Mode mode, const std::string& file_name)
    {
        // A containter to store regex and checksum
        const auto checksums_to_replace = Functions::file_of_pairs_to_container<std::deque<std::pair<std::string, std::string>>>(file_name);

        std::deque<std::string> checksums_to_print;

        {
            Timer timer("Reading-and-replacing-console-input");

            std::string input_checksum;

            while (std::cin >> input_checksum)
            {
                // Replace checksums which match a regular expression

                // Let's run it in parallel, the algorithm should take an advantage of windows thread pool
                // Visual C++ implements parallel and parallel unsequenced policies the same way
                // Reconsider this strategy if it does not meet you criteria
                // See https://devblogs.microsoft.com/cppblog/using-c17-parallel-algorithms-for-better-performance/
                const auto it = std::find_if(std::execution::par_unseq, checksums_to_replace.cbegin(), checksums_to_replace.cend(), [&](const auto& pair)
                {
                    return std::regex_search(input_checksum, std::regex(pair.first));
                });

                // Replace input
                if (it != checksums_to_replace.end())
                {
                    checksums_to_print.push_back(it->second);
                }
                else
                {
                    checksums_to_print.push_back(input_checksum);
                }
            }
        }

        // Print the container in reverse, iterating through the entire set is O(n)
        std::for_each(checksums_to_print.crbegin(), checksums_to_print.crend(), [](const auto& checksum) {
            std::cout << checksum << std::endl;
            });
    }
};