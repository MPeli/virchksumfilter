#include "pch.h"
#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer(std::string name) noexcept : name(name)
{
    ++depth;

    this->start = std::chrono::high_resolution_clock::now();
    std::cout << this->name << " started" << std::endl;
}

Timer::~Timer()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - this->start);
    std::cout  << this->name << " ended: " << elapsed.count() << "ms" << std::endl << std::endl;

    --depth;
}

int Timer::depth = 0;