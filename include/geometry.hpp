#include <cmath>
#include <iostream>
#include <limits>
#include <cassert>
#include <variant>

#pragma once

namespace geometry {
    class point_t
    {
    public:
        double x_ = 0; 
        double y_ = 0;
        double z_ = 0;

        void print()                            const;
        bool operator==(const point_t& other_p) const;

        point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
        point_t(const point_t &point);
    }; // class point_t

    class line_t
    {
    public:
        point_t p1_, p2_;
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
    
        bool    is_valid()      const;
        void    print()         const; 
        double  get_length()    const;

        line_t(const point_t &p1, const point_t &p2);
    }; // class line_t

    class triangle_t 
    {
    public:
        plane_t plane_;
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;
        int id_ = 0;
    
        bool is_valid() const;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3, int id);
    }; // class triangle_t

    class plane_t
    {
    public:
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
        double d_ = 0;

        plane_t(const point_t &p1, const point_t &p2, const point_t &p3);
    }; // class plane_t

    bool point_belongs_to_line(const point_t& p, const line_t& l);


} // namespace geometry