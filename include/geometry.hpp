#include <cmath>
#include <iostream>
#include <limits>
#include <cassert>
#include <variant>

#include "real_nums.hpp"

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

        point_t(const double x, const double y, const double z);
        point_t(const point_t& other);

    }; // class point_t

    class vector_t
    {
    public:
        double x_ = 0;
        double y_ = 0;
        double z_ = 0;

        vector_t() = default;
        vector_t(const point_t& p1, const point_t& p2);
        vector_t(const double x, const double y, const double z);
        
        bool     is_null() const;
        void     print()   const;
        vector_t vector_multiply(const vector_t& other) const;
        double   scalar_multiply(const vector_t& other) const;
        
    }; // class vector_t

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

    class plane_t
    {
    public:
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
        double d_ = 0;

        bool is_valid() const;

        plane_t(const point_t &p1, const point_t &p2, const point_t &p3);
    }; // class plane_t

    class triangle_t 
    {
    public:
        plane_t plane_;
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;

        bool is_valid() const;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3);
    }; // class triangle_t

    using figure_t = std::variant<point_t, line_t, triangle_t>;

    bool is_point_on_line(const point_t& p, const line_t& l, bool is_on_segment);
    bool is_point_in_triangle(const point_t& p, const triangle_t& t);
    
    bool is_line_intersect_line(const line_t &line1, const line_t &line2);
    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle);
    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2);    std::variant<nullptr_t, point_t, line_t> intersect(const line_t &line, const plane_t &plane);
    bool is_line_intersect_triangle(const line_t &line, const triangle_t &triangle);

    std::variant<nullptr_t, point_t, line_t> get_line_plane_intersection(const line_t &line, const plane_t &plane);

    figure_t figure_ctor(const point_t &point1, const point_t &point2, const point_t &point3);
    bool intersect(const figure_t &fig1, const figure_t &fig2);
    bool intersect(const point_t &point, const figure_t &fig);
    bool intersect(const line_t &line, const figure_t &fig);
    bool intersect(const triangle_t &triangle, const figure_t &fig);
} // namespace geometry