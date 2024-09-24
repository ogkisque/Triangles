#include <limits>
#include <cmath>

#pragma once

namespace real_nums
{

    const double EPS = std::numeric_limits<double>::epsilon();
    const double MAX = std::numeric_limits<double>::max();

    inline bool is_zero(const double x)
    {
        return std::fabs(x) < EPS;
    }

    inline bool equald(const double x, const double y)
    {
        return std::fabs(x - y) < EPS;
    }

    inline bool is_more_zero(const double x)
    {
        return x > EPS;
    }

    inline bool is_less_zero(const double x)
    {
        return x < -EPS;
    }

    inline bool is_more_or_equal_zero(const double x)
    {
        return is_more_zero(x) || is_zero(x);
    }

    inline bool is_less_or_equal_zero(const double x)
    {
        return is_less_zero(x) || is_zero(x);
    }

} // namespace real_nums
