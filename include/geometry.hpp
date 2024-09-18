#include <cmath>
#include <iostream>

#pragma once

namespace geometry {
    class point_t
    {
    public:
        double x_ = NAN; 
        double y_ = NAN;
        double z_ = NAN;

        bool is_valid() const;
        void print() const;
        bool equal(const point_t &other_p) const;
        
        point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}

    }; // class point_t


    class line_t
    {
    public:
        double x0_ = NAN, y0_ = NAN, z0_ = NAN;
        double a_  = NAN, b_  = NAN, c_  = NAN;
    
        bool is_valid() const;
        void print() const; 

        line_t(const point_t &p1, const point_t &p2);
        // line_t(const double a, const double b, const double c) : a_(a), b_(b), c_(c) {}

    }; // class line_t

    class triangle_t 
    {
    public:
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;
    
        bool is_valid() const;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) : p1_(p1), p2_(p2), p3_(p3), l1_(p1, p2), l2_(p2, p3), l3_(p3, p1) {} 
    }; // 

} // namespace geometry