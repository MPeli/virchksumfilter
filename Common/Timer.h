#pragma once
#include <string>
#include <chrono>

class Timer {
public:
    // Starts a named timer
    explicit Timer(std::string name) noexcept;

    // Stops the timer and prints the elapsed time since the start in ms
    ~Timer();

private:
    std::string name;
    std::chrono::steady_clock::time_point start;
    static int depth;
};

