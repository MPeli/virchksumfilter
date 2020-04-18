#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <unordered_set>
#include <execution>
#include <string>

#include "Timer.h"
#include <set>
#include <deque>

using namespace std::string_literals;

class Functions {

public:
    // Checks whether a value is in a container
    template<typename T1, typename T2>
    static inline bool is_in_container(const T1& container, const T2& value)
    {
        if constexpr (std::is_same<T1, std::deque<T2>>::value ||
            std::is_same<T1, std::vector<T2>>::value)
        {
            return std::find(std::execution::par_unseq, container.cbegin(), container.cend(), value) != container.end();
        }
        else
        {
            // Constant on average, worst case linear in the size of the container.
            // Returns the number of elements (1 or 0)
            return container.count(value);
        }
    }

    // Diferrent containers have different input methods (push_back, insert...)
    // We want to use a single function for all container types
    template <typename T1, typename T2>
    static inline void insert_into_any_container(T1&& value, T2& container)
    {
        if constexpr (std::is_same<T2, std::deque<std::remove_reference_t<T1>>>::value ||
            std::is_same<T2, std::vector<std::remove_reference_t<T1>>>::value)
        {
            container.push_back(std::forward<T1>(value));
        }
        else
        {
            container.insert(std::forward<T1>(value));
        }
    }

    // Reads a file of checksums and stores its content in a container
    template <typename T>
    static T file_of_checksums_to_container(const std::string file_name = "filter.cfg")
    {
        Timer timer("File-of-checksums-to-container-" + file_name);

        T checksums;

        std::ifstream file_stream(file_name);
        std::string input_line;

        // The input hash has 64 characters
        // You could try reading the whole file at once or by 64-byte chunks
        // Let's keep it simple for today
        while (file_stream >> input_line)
        {
            insert_into_any_container(input_line, checksums);
        }

        return checksums;
    }

    // Reads a file of pairs (regex, checksum) and stores its content in a container
    template <typename T>
    static T file_of_pairs_to_container(const std::string file_name = "replace.cfg")
    {
        Timer timer("File-of-pairs-to-container-" + file_name);

        T checksums;

        std::ifstream file_stream(file_name);

        std::string regex;
        std::string checksum;
        while (file_stream >> regex >> checksum)
        {
            insert_into_any_container(std::make_pair(regex, checksum), checksums);
        }

        return checksums;
    }
};