#include <limits>
#include <cmath>
#include <algorithm>

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

    inline double max3(double x, double y, double z)
    {
        return std::fmax(std::fmax(x, y), z);
    }

    inline double min3(double x, double y, double z)
    {
        return std::fmin(std::fmin(x, y), z);
    }

    inline double max2(double x, double y)
    {
        return std::fmax(x, y);
    }

    inline double min2(double x, double y)
    {
        return std::fmin(x, y);
    }

} // namespace real_nums
