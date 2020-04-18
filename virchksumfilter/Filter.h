#pragma once

#include <string>
#include <unordered_set>
#include <deque>
#include <regex>
#include <iostream>
#include <fstream>

#include "Modes.h"
#include "Timer.h"
#include <Functions.h>

class Filter
{
public:
    // Read standard input, filter it and print it in reverse
    static void do_work(Mode mode, const std::string& file_name)
    {
        // Unordered cointainers are optimized for lookup, they are implemented using hash tables.
        // Set ensures no duplicities
        const auto checksums_to_filter = Functions::file_of_checksums_to_container<std::unordered_set<std::string>>(file_name);

        // We do not know number of elements that might be inserted.
        // Let us assume that it is going to fit in the memory
        // Vector seems to be a bit faster but it needs continuous memory
        std::deque<std::string> valid_checksums;

        {
            Timer timer("Reading-and-filtering-console-input");

            std::string input_checksum;

            while (std::cin >> input_checksum)
            {
                // Filter checksum (input)
                if (!Functions::is_in_container(checksums_to_filter, input_checksum))
                {
                    valid_checksums.push_back(input_checksum);
                }
            }
        }

        // Print the checksums in reverse order, iterating through the entire set is O(n)
        std::for_each(valid_checksums.crbegin(), valid_checksums.crend(), [](const auto& checksum) {
            std::cout << checksum << std::endl;
            });
    }
};