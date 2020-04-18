#pragma once
#include <iostream>

enum class Mode
{
    replace,
    filter
};

std::ostream& operator<<(std::ostream& out, const Mode mode)
{
    out << ((mode == Mode::replace) ? "replace" : "filter");
    return out;
}