#pragma once

#include "base64.h"
#include "Timer.h"
#include <fstream>
#include <deque>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

// Generates a string of given length
static std::string random_string(std::size_t length)
{
    static constexpr auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    thread_local std::mt19937 rg{ std::random_device{}() };

    const auto dist = std::uniform_int_distribution<std::string::size_type>{ 0, std::strlen(chars) - 1 };
    auto result = std::string(length, '\0');
    std::generate_n(begin(result), length, [&]() { return chars[dist(rg)]; });
    
    return result;
}

// Generates a file of checksums with the given number of lines
static void generate_file_of_checksums(const int number_of_lines, const std::string file_name = "filter.cfg")
{
    Timer timer("Generate-a-file-of-checksums");

    std::ofstream file_stream(file_name);
    for (int i = 0; i < number_of_lines; ++i)
    {
        std::string str = random_string(47);
        file_stream << base64_encode(reinterpret_cast<const unsigned char*>(str.c_str()), str.size()) << '\n';
    }
}

// Generates a file of pairs with the given number of lines
static void generate_file_of_pairs(const int number_of_lines, const std::string file_name = "replace.cfg")
{
    Timer timer("Generate-a-file-of-pairs");

    std::ofstream file_stream(file_name);
    for (int i = 0; i < number_of_lines; ++i)
    {
        // regex
        file_stream << "^" << random_string(6) << "           ";

        // checksum
        const std::string checksum = random_string(47);
        file_stream << base64_encode(reinterpret_cast<const unsigned char*>(checksum.c_str()), checksum.size()) << '\n';
    }
}