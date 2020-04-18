// tester-generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _ENABLE_ATOMIC_ALIGNMENT_FIX

#include "Functions.h"
#include "Helpers.h"
#include <iostream>
#include <regex>

int main()
{
    // Generate input files, comment these out if you have your own data sets
    generate_file_of_checksums(10'000, "filter.cfg");
    generate_file_of_checksums(10'000, "input.txt");
    generate_file_of_pairs(10'000, "replace.cfg");

    try
    {
        Timer timer("Test");

        // This is a simple test, we need to know how long container operations take
        // Feel free to change container types and compare results

        // Unordered set has a really fast lookup
        auto checksums_to_filter = Functions::file_of_checksums_to_container<std::unordered_set<std::string>>();

        Functions::insert_into_any_container("a2VybmwxLTJhNDNjMmI3MjM4YjdmYTI5NjI5ZTg5NWRmMzAwYTdiYTQ1MDdkYzc="s, checksums_to_filter);
        Functions::insert_into_any_container("b21lZGlhLWViZjA3Njc0MTFkYTg3NmMwMWIwMWZhOTI2MThlNjNlZTIwMWE2ODg="s, checksums_to_filter);

        // Vector seems to be faster a bit, let's use std::deque anyway
        auto input_checksums = Functions::file_of_checksums_to_container<std::deque<std::string>>("input.txt");

        Functions::insert_into_any_container("a2VybmwxLTJhNDNjMmI3MjM4YjdmYTI5NjI5ZTg5NWRmMzAwYTdiYTQ1MDdkYzc="s, input_checksums);
        Functions::insert_into_any_container("b21lZGlhLWViZjA3Njc0MTFkYTg3NmMwMWIwMWZhOTI2MThlNjNlZTIwMWE2ODg="s, input_checksums);

        // Vector seems to be faster a bit, let's use std::deque anyway
        auto checksums_to_replace = Functions::file_of_pairs_to_container<std::deque<std::pair<std::string, std::string>>>();

        Functions::insert_into_any_container(std::make_pair("^YXBkZm"s, "ZmFsc2VwLTA4OTYxNjU0MzkxOWFlODI4YzMzZTQ5YmYwMjMyMDNkYjU2ZGNiN2Q="s), checksums_to_replace);
        Functions::insert_into_any_container(std::make_pair("^a2Vybmw[a-z1-9]L"s, "dmVyaWZ5LTZmMzM3ZDdhZWMzOTZmMGVmNzA4ODM5OTcxYjFhZjRkMmMwMGE1ZjM="s), checksums_to_replace);
        Functions::insert_into_any_container(std::make_pair("^d2lu[bZ]...L"s, "dmVyaWZ5LTZmMzM3ZDdhZWMzOTZmMGVmNzA4ODM5OTcxYjFhZjRkMmMwMGE1ZjM="s), checksums_to_replace);
        
        {
            Timer timer("Find-all-elements");

            // Test lookup
            int matching_elements = 0;
            int checked_elements = 0;
            for (const auto& checksum : input_checksums)
            {
                if (Functions::is_in_container(checksums_to_filter, checksum))
                {
                    ++matching_elements;
                }

                ++checked_elements;
            }

            std::cout << "Number of matching items: " << matching_elements << ", checked: " << checked_elements << std::endl;
        }

        {
            Timer timer("Replace-all-elements");

            // Test lookup
            int matching_elements = 0;
            int checked_elements = 0;
            for (auto& checksum : input_checksums)
            {
                const auto it = std::find_if(std::execution::par_unseq, checksums_to_replace.cbegin(), checksums_to_replace.cend(), [&](const auto& pair)
                    {
                        // Any checksum can be matched by a single regular expression only
                        return std::regex_search(checksum, std::regex(pair.first));
                    });

                if (it != checksums_to_replace.end())
                {
                    ++matching_elements;

                    // Replace the checksum
                    checksum = it->second;
                }

                ++checked_elements;
            }

            std::cout << "Number of replaced items: " << matching_elements << ", checked: " << checked_elements << std::endl;
        }

    }
    catch (std::bad_alloc& exception)
    {
        std::cerr << "bad_alloc detected: " << exception.what();
    }
}