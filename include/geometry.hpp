#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <utility>
#include <variant>
#include <vector>

#include "real_nums.hpp"

#pragma once

namespace geometry {

template <typename T = double> class point_t;
template <typename T = double> class line_t;
template <typename T = double> class vector_t;
template <typename T = double> class plane_t;
template <typename T = double> class triangle_t;
template <typename T = double> class cube_t;

template <typename T> class point_t {
public:
    T x_ = 0;
    T y_ = 0;
    T z_ = 0;

    void print() const {
        std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
    }

    bool is_on_line(const line_t<T> &line, bool is_on_segment) const;
    bool is_in_triangle(const triangle_t<T> &triangle) const;
    bool is_in_cube(const cube_t<T> &cube) const;

    bool operator==(const point_t<T> &other) const {
        return real_nums::equal<T>(x_, other.x_) &&
               real_nums::equal<T>(y_, other.y_) &&
               real_nums::equal<T>(z_, other.z_);
    }

    bool operator!=(const point_t<T> &other) const { return !(*this == other); }

    point_t(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

    point_t(const point_t<T> &point)
        : x_(point.x_), y_(point.y_), z_(point.z_) {}
}; // class point_t

template <typename T> class vector_t {
public:
    T x_ = 0;
    T y_ = 0;
    T z_ = 0;

    vector_t() = default;
    vector_t(const point_t<T> &p1, const point_t<T> &p2)
        : x_(p2.x_ - p1.x_), y_(p2.y_ - p1.y_), z_(p2.z_ - p1.z_) {}

    vector_t(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

    bool is_null() const { return !(x_ || y_ || z_); }

    void print() const {
        std::cout << "vector: " << x_ << " " << y_ << " " << z_ << std::endl;
    }

    vector_t vector_multiply(const vector_t<T> &other) const {
        vector_t ret_v{y_ * other.z_ - z_ * other.y_,
                       -(x_ * other.z_ - z_ * other.x_),
                       x_ * other.y_ - y_ * other.x_};

        return ret_v;
    }

    T scalar_multiply(const vector_t<T> &other) const {
        return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
    }

}; // class vector_t

template <typename T> class line_t {
public:
    point_t<T> p1_, p2_;
    T a_ = 0;
    T b_ = 0;
    T c_ = 0;

    line_t(const point_t<T> &p1, const point_t<T> &p2)
        : p1_(p1), p2_(p2), a_(p2.x_ - p1.x_), b_(p2.y_ - p1.y_),
          c_(p2.z_ - p1.z_) {}

    bool is_valid() const {
        bool is_valid = true;
        is_valid &= (a_ != NAN && b_ != NAN && c_ != NAN);
        is_valid &= (a_ || b_ || c_);

        return is_valid;
    }

    bool is_intersect_line(const line_t<T> &other) const;
    bool is_intersect_triangle_2d(const triangle_t<T> &triangle) const;
    bool is_intersect_triangle(const triangle_t<T> &triangle) const;

    std::variant<nullptr_t, point_t<T>, line_t<T>>
    get_intersection_with_plane(const plane_t<T> &plane) const;

    void print() const {
        std::cout << "line:" << std::endl
                  << "x = " << p1_.x_ << " + t * " << a_ << std::endl
                  << "y = " << p1_.y_ << " + t * " << b_ << std::endl
                  << "z = " << p1_.z_ << " + t * " << c_ << std::endl
                  << "segment:" << std::endl;
        p1_.print();
        p2_.print();
    }

    T get_length() const {
        return sqrt((p1_.x_ - p2_.x_) * (p1_.x_ - p2_.x_) +
                    (p1_.y_ - p2_.y_) * (p1_.y_ - p2_.y_) +
                    (p1_.z_ - p2_.z_) * (p1_.z_ - p2_.z_));
    }
}; // class line_t

template <typename T> class plane_t {
public:
    T a_ = 0;
    T b_ = 0;
    T c_ = 0;
    T d_ = 0;

    plane_t(const point_t<T> &p1, const point_t<T> &p2, const point_t<T> &p3) {
        vector_t p1p2{p1, p2};
        vector_t p1p3{p1, p3};

        a_ = p1p2.y_ * p1p3.z_ - p1p3.y_ * p1p2.z_;
        b_ = -p1p2.x_ * p1p3.z_ + p1p3.x_ * p1p2.z_;
        c_ = p1p2.x_ * p1p3.y_ - p1p3.x_ * p1p2.y_;

        d_ = -p1.x_ * a_ - p1.y_ * b_ - p1.z_ * c_;
    }

    bool is_valid() const { return (a_ || b_ || c_); }

    void print() const {
        std::cout << a_ << " * x + " << b_ << " * y + " << c_ << " * z + " << d_
                  << std::endl;
    }
}; // class plane_t

template <typename T> class triangle_t {
public:
    plane_t<T> plane_;
    point_t<T> p1_, p2_, p3_;
    line_t<T> l1_, l2_, l3_;

    triangle_t(const point_t<T> &p1, const point_t<T> &p2, const point_t<T> &p3)
        : p1_(p1), p2_(p2), p3_(p3), l1_(p1, p2), l2_(p2, p3), l3_(p3, p1),
          plane_(p1, p2, p3) {}

    bool is_valid() const {
        bool is_valid = l1_.is_valid() && l2_.is_valid() && l3_.is_valid();

        if (!is_valid)
            return false;

        T len1 = l1_.get_length();
        T len2 = l2_.get_length();
        T len3 = l3_.get_length();

        is_valid &= ((len1 + len2 > len3) & (len1 + len3 > len2) &
                     (len2 + len3 > len1));

        return is_valid;
    }

    bool is_intersect_triangle(const triangle_t<T> &other) const;

    void print() const {
        plane_.print();
        p1_.print();
        p2_.print();
        p3_.print();
    }
}; // class triangle_t

template <typename T> class cube_t {
public:
    T x1_, x2_, y1_, y2_, z1_, z2_;

    cube_t(T x1, T x2, T y1, T y2, T z1, T z2)
        : x1_(x1), x2_(x2), y1_(y1), y2_(y2), z1_(z1), z2_(z2) {}
}; // class cube_t

template <typename T = double>
using figure_t = std::variant<point_t<T>, line_t<T>, triangle_t<T>>;

template <typename T>
figure_t<T> figure_ctor(const point_t<T> &point1, const point_t<T> &point2,
                        const point_t<T> &point3);

template <typename T> void figure_print(const figure_t<T> &figure);

template <typename T>
bool intersect(const figure_t<T> &figure1, const figure_t<T> &figure2);

template <typename T>
bool intersect(const point_t<T> &point, const figure_t<T> &figure);

template <typename T>
bool intersect(const line_t<T> &line, const figure_t<T> &figure);

template <typename T>
bool intersect(const triangle_t<T> &triangle, const figure_t<T> &figure);

template <typename T>
bool is_fig_in_cube(const figure_t<T> &fig, const cube_t<T> &cube);

template <typename T> bool point_t<T>::is_in_cube(const cube_t<T> &cube) const {
    return (real_nums::is_more_zero<T>(x_ - cube.x1_) &&
            real_nums::is_less_zero<T>(x_ - cube.x2_) &&
            real_nums::is_more_zero<T>(y_ - cube.y1_) &&
            real_nums::is_less_zero<T>(y_ - cube.y2_) &&
            real_nums::is_more_zero<T>(z_ - cube.z1_) &&
            real_nums::is_less_zero<T>(z_ - cube.z2_));
}

template <typename T>
bool point_t<T>::is_on_line(const line_t<T> &line, bool is_on_segment) const {
    T param = 0;

    if (!real_nums::is_zero<T>(line.a_))
        param = (x_ - line.p1_.x_) / line.a_;
    else if (!real_nums::is_zero<T>(line.b_))
        param = (y_ - line.p1_.y_) / line.b_;
    else if (!real_nums::is_zero<T>(line.c_))
        param = (z_ - line.p1_.z_) / line.c_;
    else
        assert(("Line is not valid", 0));

    point_t<T> possible_point{line.p1_.x_ + line.a_ * param,
                              line.p1_.y_ + line.b_ * param,
                              line.p1_.z_ + line.c_ * param};

    if (possible_point != *this)
        return false;

    if (is_on_segment)
        return (real_nums::is_more_or_equal_zero<T>(param) &&
                real_nums::is_less_or_equal_zero<T>(param - 1));

    return true;
}

template <typename T>
bool point_t<T>::is_in_triangle(const triangle_t<T> &triangle) const {
    if (is_on_line(triangle.l1_, true) || is_on_line(triangle.l2_, true) ||
        is_on_line(triangle.l3_, true))
        return true;

    T plane_equation = triangle.plane_.a_ * x_ + triangle.plane_.b_ * y_ +
                       triangle.plane_.c_ * z_ + triangle.plane_.d_;

    if (!real_nums::is_zero<T>(plane_equation))
    {
        return false;
    }
    point_t<T> A = triangle.p1_, B = triangle.p2_, C = triangle.p3_, O = *this;

    vector_t AB{A, B};
    vector_t AO{A, O};
    vector_t v1 = AB.vector_multiply(AO);

    vector_t BC{B, C};
    vector_t BO{B, O};
    vector_t v2 = BC.vector_multiply(BO);

    vector_t CA{C, A};
    vector_t CO{C, O};
    vector_t v3 = CA.vector_multiply(CO);

    T scalar1 = v1.scalar_multiply(v2);
    T scalar2 = v2.scalar_multiply(v3);
    T scalar3 = v3.scalar_multiply(v1);

    if (real_nums::is_more_zero<T>(scalar1) &&
        real_nums::is_more_zero<T>(scalar2) &&
        real_nums::is_more_zero<T>(scalar3))
        return true;

    if (real_nums::is_less_zero<T>(scalar1) &&
        real_nums::is_less_zero<T>(scalar2) &&
        real_nums::is_less_zero<T>(scalar3))
        return true;

    return false;
}

template <typename T>
bool line_t<T>::is_intersect_line(const line_t<T> &other) const {
    assert(("Data is not valid", is_valid() && other.is_valid()));

    vector_t<T> tangent1{a_, b_, c_};
    vector_t<T> tangent2{other.a_, other.b_, other.c_};

    vector_t vec_multiply = tangent1.vector_multiply(tangent2);

    if (vec_multiply.is_null()) // parallel or identic
    {
        if (p1_.is_on_line(other, false)) // identic lines
            return p1_.is_on_line(other, true) || p2_.is_on_line(other, true);

        // parallel lines
        return false;
    }

    // intersect or in the different planes

    point_t<T> p1 = {p1_.x_, p1_.y_, p1_.z_};
    point_t<T> p2 = {other.p1_.x_, other.p1_.y_, other.p1_.z_};

    vector_t<T> delta = {p1, p2};
    vector_t<T> tanget1 = {a_, b_, c_};
    vector_t<T> tanget2 = {other.a_, other.b_, other.c_};

    T det_xy = tanget2.x_ * tanget1.y_ - tanget2.y_ * tanget1.x_;
    T det_xz = tanget2.x_ * tanget1.z_ - tanget2.z_ * tanget1.x_;
    T det_yz = tanget2.y_ * tanget1.z_ - tanget2.z_ * tanget1.y_;

    T det1 = 0, det2 = 0;
    T param1 = 0, param2 = 0;

    if (!real_nums::is_zero<T>(det_xy)) {
        det1 = tanget2.x_ * delta.y_ - tanget2.y_ * delta.x_;
        det2 = tanget1.x_ * delta.y_ - tanget1.y_ * delta.x_;

        param1 = det1 / det_xy;
        param2 = det2 / det_xy;

        if (p1.z_ + tanget1.z_ * param1 != p2.z_ + tanget2.z_ * param2)
            return false;
    } else if (!real_nums::is_zero<T>(det_xz)) {
        det1 = tanget2.x_ * delta.z_ - tanget2.z_ * delta.x_;
        det2 = tanget1.x_ * delta.z_ - tanget1.z_ * delta.x_;

        param1 = det1 / det_xz;
        param2 = det2 / det_xz;

        if (p1.y_ + tanget1.y_ * param1 != p2.y_ + tanget2.y_ * param2)
            return false;
    } else if (!real_nums::is_zero<T>(det_yz)) {
        det1 = tanget2.y_ * delta.z_ - tanget2.z_ * delta.y_;
        det2 = tanget1.y_ * delta.z_ - tanget1.z_ * delta.y_;

        param1 = det1 / det_yz;
        param2 = det2 / det_yz;

        if (p1.x_ + tanget1.x_ * param1 != p2.x_ + tanget2.x_ * param2)
            return false;
    } else // lines don't lie in the same plane
    {
        return false;
    }

    return (real_nums::is_more_or_equal_zero<T>(param1) &&
            real_nums::is_less_or_equal_zero<T>(param1 - 1)) &&
           (real_nums::is_more_or_equal_zero<T>(param2) &&
            real_nums::is_less_or_equal_zero<T>(param2 - 1));
}

template <typename T>
bool line_t<T>::is_intersect_triangle_2d(const triangle_t<T> &triangle) const {
    if (p1_.is_in_triangle(triangle) || p2_.is_in_triangle(triangle))
        return true;

    return is_intersect_line(triangle.l1_) || is_intersect_line(triangle.l2_) ||
           is_intersect_line(triangle.l3_);
}

template <typename T> struct CallLineIntersectTriangle {
    bool operator()(nullptr_t) {
        return false;
    }
    bool operator()(const point_t<T> &point) {
        return point.is_in_triangle(triangle);
    }
    bool operator()(const line_t<T> &line) {
        return line.is_intersect_triangle_2d(triangle);
    }

    const triangle_t<T> &triangle;
};

template <typename T>
bool line_t<T>::is_intersect_triangle(const triangle_t<T> &triangle) const {
    assert(("Data is not valid", is_valid() && triangle.is_valid()));

    auto intersection = get_intersection_with_plane(triangle.plane_);
    return std::visit(CallLineIntersectTriangle{triangle}, intersection);
}

template <typename T>
std::variant<nullptr_t, point_t<T>, line_t<T>>
line_t<T>::get_intersection_with_plane(const plane_t<T> &plane) const {
    assert(("Data is not valid", is_valid() && plane.is_valid()));

    vector_t<T> plane_normal = {plane.a_, plane.b_, plane.c_};
    vector_t<T> line_tangent = {a_, b_, c_};

    T scalar = plane_normal.scalar_multiply(line_tangent);
    T plane_equation =
        p1_.x_ * plane.a_ + p1_.y_ * plane.b_ + p1_.z_ * plane.c_ + plane.d_;

    if (real_nums::is_zero<T>(scalar)) // parallel or lie
    {
        if (real_nums::is_zero<T>(plane_equation))
            return *this;
        else
            return nullptr;
    } else // intersect
    {
        T param = -plane_equation / scalar;

        if (real_nums::is_more_or_equal_zero<T>(param) &&
            real_nums::is_less_or_equal_zero<T>(param - 1)) {
            point_t<T> point_on_plane{p1_.x_ + param * a_, p1_.y_ + param * b_,
                                      p1_.z_ + param * c_};

            return point_on_plane;
        }

        return nullptr;
    }
}

template <typename T>
bool triangle_t<T>::is_intersect_triangle(const triangle_t &other) const {
    return l1_.is_intersect_triangle(other) ||
           l2_.is_intersect_triangle(other) ||
           l3_.is_intersect_triangle(other) ||
           other.l1_.is_intersect_triangle(*this) ||
           other.l2_.is_intersect_triangle(*this) ||
           other.l3_.is_intersect_triangle(*this);
}

template <typename T>
figure_t<T> figure_ctor(const point_t<T> &point1, const point_t<T> &point2,
                        const point_t<T> &point3) {
    if (point1 == point2 && point2 == point3)
        return point1;
    else if (point1 == point2)
        return line_t{point1, point3};
    else if (point1 == point3)
        return line_t{point1, point2};
    else if (point2 == point3)
        return line_t{point1, point3};
    else
        return triangle_t<T>{point1, point2, point3};
}

template <typename T>
bool intersect(const figure_t<T> &figure1, const figure_t<T> &figure2) {
    return std::visit(
        [&figure2](const auto &figure1) {
            return intersect<T>(figure1, figure2);
        },
        figure1);
}

template <typename T> void print_figure(const figure_t<T> &figure) {
    std::visit([](const auto &figure) { return figure.print(); }, figure);
}

template <typename T> struct CallIntersectPoint {
    bool operator()(const point_t<T> &point2) { return point1 == point2; }
    bool operator()(const line_t<T> &line2) {
        return point1.is_on_line(line2, true);
    }
    bool operator()(const triangle_t<T> &triangle2) {
        return point1.is_in_triangle(triangle2);
    }

    const point_t<T> &point1;
};

template <typename T>
bool intersect(const point_t<T> &point, const figure_t<T> &figure) {
    return std::visit(CallIntersectPoint<T>{point}, figure);
}

template <typename T> struct CallIntersectLine {
    bool operator()(const point_t<T> &point2) {
        return point2.is_on_line(line1, true);
    }
    bool operator()(const line_t<T> &line2) {
        return line1.is_intersect_line(line2);
    }
    bool operator()(const triangle_t<T> &triangle2) {
        return line1.is_intersect_triangle(triangle2);
    }

    const line_t<T> &line1;
};

template <typename T>
bool intersect(const line_t<T> &line, const figure_t<T> &figure) {
    return std::visit(CallIntersectLine<T>{line}, figure);
}

template <typename T> struct CallIntersectTriangle {
    bool operator()(const point_t<T> &point2) {
        return point2.is_in_triangle(triangle1);
    }
    bool operator()(const line_t<T> &line2) {
        return line2.is_intersect_triangle(triangle1);
    }
    bool operator()(const triangle_t<T> &triangle2) {
        return triangle1.is_intersect_triangle(triangle2);
    }

    const triangle_t<T> &triangle1;
};

template <typename T>
bool intersect(const triangle_t<T> &triangle, const figure_t<T> &figure) {
    return std::visit(CallIntersectTriangle<T>{triangle}, figure);
}

template <typename T> struct CallFigureInCube {
    bool operator()(const point_t<T> &point) { return point.is_in_cube(cube); }

    bool operator()(const line_t<T> &line) {
        return line.p1_.is_in_cube(cube) && line.p2_.is_in_cube(cube);
    }

    bool operator()(const triangle_t<T> &triangle) {
        return triangle.p1_.is_in_cube(cube) && triangle.p2_.is_in_cube(cube) &&
               triangle.p3_.is_in_cube(cube);
    }

    const cube_t<T> &cube;
};

template <typename T>
bool is_fig_in_cube(const figure_t<T> &fig, const cube_t<T> &cube) {
    return std::visit(CallFigureInCube<T>{cube}, fig);
}

template <typename T> struct CallGetMaxCoord {
    T operator()(const point_t<T> &point) {
        return real_nums::max3<T>(std::fabs(point.x_), std::fabs(point.y_),
                                  std::fabs(point.z_));
    }

    T operator()(const line_t<T> &line) {
        return real_nums::max6<T>(
            std::fabs(line.p1_.x_), std::fabs(line.p1_.y_),
            std::fabs(line.p1_.z_), std::fabs(line.p2_.x_),
            std::fabs(line.p2_.y_), std::fabs(line.p2_.z_));
    }

    T operator()(const triangle_t<T> &triangle) {
        return real_nums::max9<T>(
            std::fabs(triangle.p1_.x_), std::fabs(triangle.p1_.y_),
            std::fabs(triangle.p1_.z_), std::fabs(triangle.p2_.x_),
            std::fabs(triangle.p2_.y_), std::fabs(triangle.p2_.z_),
            std::fabs(triangle.p3_.x_), std::fabs(triangle.p3_.y_),
            std::fabs(triangle.p3_.z_));
    }
};

template <typename T> T get_max_coord(const std::vector<figure_t<T>> &figs) {
    T max_coord = 0;

    for (auto fig : figs) {
        T cur_max_coord = std::visit(CallGetMaxCoord<T>{}, fig);
        max_coord = real_nums::max2<T>(max_coord, cur_max_coord);
    }

    return max_coord;
}
} // namespace geometry