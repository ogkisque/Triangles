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
        point_t(const point_t& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}

        bool operator==(const point_t& other_p) const
        {
            return this->equal(other_p);
        }
    }; // class point_t

    class line_t
    {
    public:
        point_t p1_, p2_;
        double a_  = NAN, b_  = NAN, c_  = NAN;
    
        bool is_valid() const;
        void print() const; 

        line_t(const point_t &p1, const point_t &p2);
    }; // class line_t

    class plane_t
    {
    public:
        double a, b, c, d;

        plane_t(const point_t p1, const point_t p2, const point_t p3);
    }; // class plane_t

    class triangle_t 
    {
    public:
        plane_t plane;
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;
    
        bool is_valid() const;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) : p1_(p1), p2_(p2), p3_(p3), l1_(p1, p2), l2_(p2, p3), l3_(p3, p1), plane(p1, p2, p3) {} 
    }; // class triangle_t


    bool point_belongs_to_line(const point_t& p, const line_t& l);

} // namespace geometry