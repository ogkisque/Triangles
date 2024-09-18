#include <cmath>
#include <iostream>

#pragma once

namespace geometry {

    class point_t
    {
    public:
        double x_ = NAN; 
        double y_ = NAN;

        bool is_valid() const;
        void print() const;
        bool equal(const point_t &other_p) const;
        
        point_t(const double x, const double y) : x_(x), y_(y) {}

    }; // class point_t


    class line_t
    {
        double a_ = -1, b_ = 1, c_ = 0;

    public:
        bool is_valid() const;
        void print() const; 
        

        line_t(const point_t &p1, const point_t &p2);
        line_t(const double a, const double b, const double c) : a_(a), b_(b), c_(c) {}

    }; // class line_t

    class triangle_t 
    {
        point_t p1_, p2_, p3_;
    public:
        bool is_valid() const;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) : p1_(p1), p2_(p2), p3_(p3) {} 
    }; // 

} // namespace geometry