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

        void print() const
        {
            std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
        }
        
        bool operator==(const point_t& other) const
        {
            return real_nums::equald(x_, other.x_) &&
                   real_nums::equald(y_, other.y_) &&
                   real_nums::equald(z_, other.z_); 
        }
        
        bool operator!=(const point_t& other) const
        {
            return !(*this == other);
        }

        point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
        point_t(const point_t &point) : x_(point.x_), y_(point.y_), z_(point.z_) {}
    }; // class point_t

    class vector_t
    {
    public:
        double x_ = 0;
        double y_ = 0;
        double z_ = 0;

        vector_t() = default;
        vector_t(const point_t& p1, const point_t& p2) : x_(p2.x_ - p1.x_), y_(p2.y_ - p1.y_), z_(p2.z_ - p1.z_) {}
        vector_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
    
        bool is_null() const
        {
            return !(x_ || y_ || z_);
        }

        void print() const 
        {
            std::cout << "vector: " << x_ << " " << y_ << " " << z_ << std::endl;
        }

        vector_t vector_multiply(const vector_t& other) const
        {
            vector_t ret_v{ y_ * other.z_ - z_ * other.y_,
                          -(x_ * other.z_ - z_ * other.x_), 
                            x_ * other.y_ - y_ * other.x_};

            return ret_v;
        }

        double scalar_multiply(const vector_t& other) const
        {
            return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
        }
        
    }; // class vector_t

    class line_t
    {
    public:
        point_t p1_, p2_;
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
    
        line_t(const point_t &p1, const point_t &p2) : p1_(p1), p2_(p2),
                                                       a_(p2.x_ - p1.x_),
                                                       b_(p2.y_ - p1.y_),
                                                       c_(p2.z_ - p1.z_) {}

        bool is_valid() const 
        {
            bool is_valid = true;
            is_valid &= (a_ != NAN && b_ != NAN && c_ != NAN);
            is_valid &= (a_ || b_ || c_);
            
            return is_valid;
        }

        void print() const 
        {
            std::cout << "line:" << std::endl <<
            "x = " << p1_.x_ << " + t * " << a_ << std::endl <<
            "y = " << p1_.y_ << " + t * " << b_ << std::endl <<
            "z = " << p1_.z_ << " + t * " << c_ << std::endl <<
            "segment:" << std::endl;
            p1_.print();
            p2_.print();
        }

        double get_length() const
        {
            return sqrt((p1_.x_ - p2_.x_) * (p1_.x_ - p2_.x_) + 
                        (p1_.y_ - p2_.y_) * (p1_.y_ - p2_.y_) +
                        (p1_.z_ - p2_.z_) * (p1_.z_ - p2_.z_));
        }
    }; // class line_t

    class plane_t
    {
    public:
        double a_ = 0;
        double b_ = 0;
        double c_ = 0;
        double d_ = 0;

        plane_t(const point_t &p1, const point_t &p2, const point_t &p3)
        {
            vector_t p1p2{p1, p2};
            vector_t p1p3{p1, p3};

            a_ =   p1p2.y_ * p1p3.z_ - p1p3.y_ * p1p2.z_;
            b_ = - p1p2.x_ * p1p3.z_ + p1p3.x_ * p1p2.z_;
            c_ =   p1p2.x_ * p1p3.y_ - p1p3.x_ * p1p2.y_;
            
            d_ = - p1.x_ * a_ - p1.y_ * b_ - p1.z_ * c_;
        }

        bool is_valid() const
        {
            return (a_ || b_ || c_);
        }

        void print() const
        {
            std::cout << a_ << " * x + " << b_ << " * y + " << c_ << " * z + " << d_ << std::endl;
        }
    }; // class plane_t

    class triangle_t 
    {
    public:
        plane_t plane_;
        point_t p1_, p2_, p3_;
        line_t l1_, l2_, l3_;

        triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) : p1_(p1), p2_(p2), p3_(p3),
                                                                                          l1_(p1, p2), l2_(p2, p3), l3_(p3, p1),
                                                                                          plane_(p1, p2, p3) {}

        bool is_valid() const
        {
            bool is_valid = l1_.is_valid() && l2_.is_valid() && l3_.is_valid(); 
            
            if (!is_valid)
                return false;

            double len1 = l1_.get_length();
            double len2 = l2_.get_length();
            double len3 = l3_.get_length();

            is_valid &= ((len1 + len2 > len3) & (len1 + len3 > len2) & (len2 + len3 > len1));

            return is_valid;
        }

        void print() const
        {
            plane_.print();
            p1_.print();
            p2_.print();
            p3_.print();
        }

    }; // class triangle_t

    class cube_t
    {
    public:
        double x1_, x2_, y1_, y2_, z1_, z2_;

        cube_t(double x1, double x2, double y1, double y2, double z1, double z2) : 
        x1_(x1), x2_(x2), y1_(y1), y2_(y2), z1_(z1), z2_(z2) {}
    }; // class cube_t

    using figure_t = std::variant<point_t, line_t, triangle_t>;

    bool is_point_on_line(const point_t& point, const line_t& line, bool is_on_segment);
    bool is_point_in_triangle(const point_t& point, const triangle_t& triangle);
    bool is_line_intersect_line(const line_t &line1, const line_t &line2);
    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle);
    bool is_line_intersect_triangle(const line_t &line, const triangle_t &triangle);
    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2);
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

    bool is_point_on_line(const point_t& point, const line_t& line, bool is_on_segment)
    {
        double param = 0;
        
        if (!real_nums::is_zero(line.a_))
            param = (point.x_ - line.p1_.x_) / line.a_;
        else if (!real_nums::is_zero(line.b_))
            param = (point.y_ - line.p1_.y_) / line.b_;
        else if (!real_nums::is_zero(line.c_))
            param = (point.z_ - line.p1_.z_) / line.c_;
        else
            assert(("Line is not valid", 0));

        point_t possible_point{line.p1_.x_ + line.a_ * param,
                               line.p1_.y_ + line.b_ * param,
                               line.p1_.z_ + line.c_ * param};

        if (possible_point != point)
            return false;

        if (is_on_segment)
            return (real_nums::is_more_or_equal_zero(param) && real_nums::is_less_or_equal_zero(param - 1)); 

        return true;
    }

    bool is_point_in_triangle(const point_t& point, const triangle_t& triangle)
    {
        if (is_point_on_line(point, triangle.l1_, true) ||
            is_point_on_line(point, triangle.l2_, true) ||
            is_point_on_line(point, triangle.l3_, true))
            return true;

        double plane_equation = triangle.plane_.a_ * point.x_ + \
                                triangle.plane_.b_ * point.y_ + \
                                triangle.plane_.c_ * point.z_ + triangle.plane_.d_;
        
        if (!real_nums::is_zero(plane_equation))
            return false;
        
        point_t A = triangle.p1_, B = triangle.p2_, C = triangle.p3_, O = point;

        vector_t AB{A, B};
        vector_t AO{A, O};
        vector_t v1 = AB.vector_multiply(AO);

        vector_t BC{B, C};
        vector_t BO{B, O};
        vector_t v2 = BC.vector_multiply(BO);

        vector_t CA{C, A};
        vector_t CO{C, O};
        vector_t v3 = CA.vector_multiply(CO);

        double scalar1 = v1.scalar_multiply(v2);
        double scalar2 = v2.scalar_multiply(v3);
        double scalar3 = v3.scalar_multiply(v1);

        if (real_nums::is_more_zero(scalar1) &&
            real_nums::is_more_zero(scalar2) && 
            real_nums::is_more_zero(scalar3))
            return true;

        if (real_nums::is_less_zero(scalar1) &&
            real_nums::is_less_zero(scalar2) && 
            real_nums::is_less_zero(scalar3))
            return true;
        
        return false;
    }
    

    bool is_line_intersect_line(const line_t &line1, const line_t &line2)
    {
        assert(("Data is not valid", line1.is_valid() && line2.is_valid()));

        vector_t tangent1{line1.a_, line1.b_, line1.c_};
        vector_t tangent2{line2.a_, line2.b_, line2.c_};
        
        vector_t vec_multiply = tangent1.vector_multiply(tangent2);

        if (vec_multiply.is_null()) // parallel or identic
        {
            if (is_point_on_line(line1.p1_, line2, false)) // identic lines
                return is_point_on_line(line1.p1_, line2, true) || is_point_on_line(line1.p2_, line2, true);

            // parallel lines
            return false;
        }

        // intersect or in the different planes

        point_t p1 = {line1.p1_.x_, line1.p1_.y_, line1.p1_.z_};
        point_t p2 = {line2.p1_.x_, line2.p1_.y_, line2.p1_.z_};

        vector_t delta   = {p1, p2};
        vector_t tanget1 = {line1.a_, line1.b_, line1.c_};
        vector_t tanget2 = {line2.a_, line2.b_, line2.c_};

        double det_xy = tanget2.x_ * tanget1.y_ - tanget2.y_ * tanget1.x_;
        double det_xz = tanget2.x_ * tanget1.z_ - tanget2.z_ * tanget1.x_;
        double det_yz = tanget2.y_ * tanget1.z_ - tanget2.z_ * tanget1.y_;
        
        double det1 = 0, det2 = 0;
        double param1 = 0, param2 = 0;

        if (!real_nums::is_zero(det_xy))
        {
            det1 = tanget2.x_ * delta.y_ - tanget2.y_ * delta.x_;
            det2 = tanget1.x_ * delta.y_ - tanget1.y_ * delta.x_;

            param1 = det1 / det_xy;
            param2 = det2 / det_xy;

            if (p1.z_ + tanget1.z_ * param1 != p2.z_ + tanget2.z_ * param2)
                return false;
        }
        else if (!real_nums::is_zero(det_xz))
        {
            det1 = tanget2.x_ * delta.z_ - tanget2.z_ * delta.x_;
            det2 = tanget1.x_ * delta.z_ - tanget1.z_ * delta.x_;

            param1 = det1 / det_xz;
            param2 = det2 / det_xz;

            if (p1.y_ + tanget1.y_ * param1 != p2.y_ + tanget2.y_ * param2)
                return false;
        }
        else if (!real_nums::is_zero(det_yz))
        {
            det1 = tanget2.y_ * delta.z_ - tanget2.z_ * delta.y_;
            det2 = tanget1.y_ * delta.z_ - tanget1.z_ * delta.y_;

            param1 = det1 / det_yz;
            param2 = det2 / det_yz;

            if (p1.x_ + tanget1.x_ * param1 != p2.x_ + tanget2.x_ * param2)
                return false;
        }
        else // lines don't lie in the same plane
        {
            return false;
        }

        return (real_nums::is_more_or_equal_zero(param1) && real_nums::is_less_or_equal_zero(param1 - 1)) &&
               (real_nums::is_more_or_equal_zero(param2) && real_nums::is_less_or_equal_zero(param2 - 1));
    }

    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle)
    {
        if (is_point_in_triangle(line.p1_, triangle) || is_point_in_triangle(line.p2_, triangle))
            return true;

        return is_line_intersect_line(line, triangle.l1_) ||
               is_line_intersect_line(line, triangle.l2_) ||
               is_line_intersect_line(line, triangle.l3_);
    }

    struct CallLineIntersectTriangle
    {
        bool operator()(nullptr_t)
        {
            return false;
        }
        bool operator()(const point_t &point)
        {
            return is_point_in_triangle(point, triangle);
        }
        bool operator()(const line_t &line)
        {
            return is_line_intersect_triangle_2d(line, triangle);
        }

        const triangle_t& triangle;
    };

    bool is_line_intersect_triangle(const line_t &line, const triangle_t &triangle)
    {
        assert(("Data is not valid", line.is_valid() && triangle.is_valid()));

        auto intersection = get_line_plane_intersection(line, triangle.plane_);
        return std::visit(CallLineIntersectTriangle{triangle}, intersection);
    }

    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2)
    {
        return is_line_intersect_triangle(triangle1.l1_, triangle2) ||
               is_line_intersect_triangle(triangle1.l2_, triangle2) ||
               is_line_intersect_triangle(triangle1.l3_, triangle2) ||
               is_line_intersect_triangle(triangle2.l1_, triangle1) ||
               is_line_intersect_triangle(triangle2.l2_, triangle1) ||
               is_line_intersect_triangle(triangle2.l3_, triangle1);
    }

    bool is_point_in_cube(const point_t &point, const cube_t &cube)
    {
        return (real_nums::is_more_zero(point.x_ - cube.x1_) &&
                real_nums::is_less_zero(point.x_ - cube.x2_) &&
                real_nums::is_more_zero(point.y_ - cube.y1_) &&
                real_nums::is_less_zero(point.y_ - cube.y2_) &&
                real_nums::is_more_zero(point.z_ - cube.z1_) &&
                real_nums::is_less_zero(point.z_ - cube.z2_));
    }

    std::variant<nullptr_t, point_t, line_t> get_line_plane_intersection(const line_t &line, const plane_t &plane)
    {
        assert(("Data is not valid", line.is_valid() && plane.is_valid()));

        vector_t plane_normal = {plane.a_, plane.b_, plane.c_};
        vector_t line_tangent = {line.a_,  line.b_,  line.c_ };

        double scalar = plane_normal.scalar_multiply(line_tangent);
        double plane_equation = line.p1_.x_ * plane.a_ + line.p1_.y_ * plane.b_ + line.p1_.z_ * plane.c_ + plane.d_; 

        if (real_nums::is_zero(scalar)) // parallel or lie
        {
            if (real_nums::is_zero(plane_equation))
                return line;
            else
                return nullptr;
        }
        else // intersect
        {
            double param = -plane_equation / scalar;

            if (real_nums::is_more_or_equal_zero(param) && real_nums::is_less_or_equal_zero(param - 1))
            {
                point_t point_on_plane{line.p1_.x_ + param * line.a_,
                                       line.p1_.y_ + param * line.b_,
                                       line.p1_.z_ + param * line.c_};

                return point_on_plane;
            }

            return nullptr;
        }
    }

    figure_t figure_ctor(const point_t &point1, const point_t &point2, const point_t &point3)
    {
        if (point1 == point2 && point2 == point3)
            return point1;
        else if (point1 == point2)
            return line_t{point1, point3};
        else if (point1 == point3)
            return line_t{point1, point2};
        else if (point2 == point3)
            return line_t{point1, point3};
        else
            return triangle_t{point1, point2, point3};
    }

    struct CallPrint
    {
        void operator()(const point_t &point)
        {
            point.print();
        }
        void operator()(const line_t &line)
        {
            line.print();
        }
        void operator()(const triangle_t &triangle)
        {
            triangle.print();
        }
    };

    void figure_print(const figure_t& figure)
    {
        std::visit(CallPrint{}, figure);
    }

    struct CallIntersectFigure
    {
        bool operator()(const point_t &point1)
        {
            return intersect(point1, figure2);
        }
        bool operator()(const line_t &line1)
        {
            return intersect(line1, figure2);
        }
        bool operator()(const triangle_t &triangle1)
        {
            return intersect(triangle1, figure2);
        }

        const figure_t& figure2;
    };

    struct CallIntersectPoint
    {
        bool operator()(const point_t &point2)
        {
            return point1 == point2;
        }
        bool operator()(const line_t &line2)
        {
            return is_point_on_line(point1, line2, true);
        }
        bool operator()(const triangle_t &triangle2)
        {
            return is_point_in_triangle(point1, triangle2);
        }

        const point_t& point1;
    };

    struct CallIntersectLine
    {
        bool operator()(const point_t &point2)
        {
            return is_point_on_line(point2, line1, true);
        }
        bool operator()(const line_t &line2)
        {
            return is_line_intersect_line(line1, line2);
        }
        bool operator()(const triangle_t &triangle2)
        {
            return is_line_intersect_triangle(line1, triangle2);
        }

        const line_t& line1;
    };

    struct CallIntersectTriangle
    {
        bool operator()(const point_t &point2)
        {
            return is_point_in_triangle(point2, triangle1);
        }
        bool operator()(const line_t &line2)
        {
            return is_line_intersect_triangle(line2, triangle1);
        }
        bool operator()(const triangle_t &triangle2)
        {
            return is_triangle_intersect_triangle(triangle1, triangle2);
        }

        const triangle_t& triangle1;
    };

    bool intersect(const figure_t &figure1, const figure_t &figure2)
    {
        return std::visit(CallIntersectFigure{figure2}, figure1);
    }

    bool intersect(const point_t &point, const figure_t &figure)
    {
        return std::visit(CallIntersectPoint{point}, figure);
    }

    bool intersect(const line_t &line, const figure_t &figure)
    {
        return std::visit(CallIntersectLine{line}, figure);
    }

    bool intersect(const triangle_t &triangle, const figure_t &figure)
    {
        return std::visit(CallIntersectTriangle{triangle}, figure);
    }

    struct CallFigureInCube
    {
        bool operator()(const point_t &point)
        {
            return is_point_in_cube(point, cube);
        }

        bool operator()(const line_t &line)
        {
            return is_point_in_cube(line.p1_, cube) &&
                   is_point_in_cube(line.p2_, cube);
        }

        bool operator()(const triangle_t &triangle)
        {
            return is_point_in_cube(triangle.p1_, cube) &&
                   is_point_in_cube(triangle.p2_, cube) &&
                   is_point_in_cube(triangle.p3_, cube);
        }

        const cube_t &cube;
    };
    
    bool is_fig_in_cube(const figure_t &fig, const cube_t &cube)
    {
        return std::visit(CallFigureInCube{cube}, fig);
    }

    struct CallGetMaxCoord
    {
        double operator()(const point_t &point)
        {
            return real_nums::max3(std::fabs(point.x_), std::fabs(point.y_), std::fabs(point.z_));
        }

        double operator()(const line_t &line)
        {
            return real_nums::max6(std::fabs(line.p1_.x_), std::fabs(line.p1_.y_), std::fabs(line.p1_.z_),
                                   std::fabs(line.p2_.x_), std::fabs(line.p2_.y_), std::fabs(line.p2_.z_));
        }

        double operator()(const triangle_t &triangle)
        {
            return real_nums::max9(std::fabs(triangle.p1_.x_), std::fabs(triangle.p1_.y_), std::fabs(triangle.p1_.z_),
                                   std::fabs(triangle.p2_.x_), std::fabs(triangle.p2_.y_), std::fabs(triangle.p2_.z_),
                                   std::fabs(triangle.p3_.x_), std::fabs(triangle.p3_.y_), std::fabs(triangle.p3_.z_));
        }
    };

    double get_max_coord(const std::vector<figure_t> &figs)
    {
        double max_coord = 0;

        for (auto fig : figs)
        {
            double cur_max_coord = std::visit(CallGetMaxCoord{}, fig);
            max_coord = real_nums::max2(max_coord, cur_max_coord);
        }

        return max_coord;
    }
} // namespace geometry