#include <cmath>
#include <iostream>
#include <limits>
#include <cassert>
#include <variant>
#include <array>
#include <utility>
#include <algorithm>
#include <vector>

#include "real_nums.hpp"

#pragma once

namespace geometry {

    class point_t
    {
    public:
        double x_ = 0; 
        double y_ = 0;
        double z_ = 0;

        void print()                          const;
        bool operator==(const point_t& other) const;
        bool operator!=(const point_t& other) const;

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
        vector_t(const point_t& point1, const point_t& point2);
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

        line_t(const point_t &point1, const point_t &point2);
    }; // class line_t

    class plane_t
    {
    public:
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
        double d_ = 0;

        bool is_valid() const;
        void print()    const;

        plane_t(const point_t &point1, const point_t &point2, const point_t &point3);
    }; // class plane_t

    class triangle_t 
    {
    public:
        plane_t plane_;
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;

        bool is_valid() const;
        void print()    const;

        triangle_t(const point_t &point1, const point_t &point2, const point_t &point3);
    }; // class triangle_t

    class cube_t
    {
    public:
        double x1_, x2_, y1_, y2_, z1_, z2_;

        cube_t(double x1, double x2, double y1, double y2, double z1, double z2);
    }; // class cube_t

    using figure_t = std::variant<point_t, line_t, triangle_t>;

    bool is_point_on_line(const point_t& point, const line_t& line, bool is_on_segment);
    bool is_point_in_triangle(const point_t& point, const triangle_t& triangle);
    
    bool is_line_intersect_line(const line_t &line1, const line_t &line2);
    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle);
    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2);
    bool is_line_intersect_triangle(const line_t &line, const triangle_t &triangle);
    bool is_point_in_cube(const point_t &point, const cube_t &cube);

    std::variant<nullptr_t, point_t, line_t> get_line_plane_intersection(const line_t &line, const plane_t &plane);
        
    figure_t figure_ctor(const point_t &point1, const point_t &point2, const point_t &point3);
    void figure_print(const figure_t& figure);
    
    bool intersect(const figure_t &figure1, const figure_t &figure2);
    bool intersect(const point_t &point, const figure_t &figure);
    bool intersect(const line_t &line, const figure_t &figure);
    bool intersect(const triangle_t &triangle, const figure_t &figure);

    bool is_fig_in_cube(const figure_t &fig, const cube_t &cube);

    double get_max_coord(const std::vector<figure_t> &figs);
} // namespace geometry