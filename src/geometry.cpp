#include "geometry.hpp"

namespace geometry
{

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
        return (real_nums::is_more_or_equal_zero(point.x_ - cube.x1_) &&
                real_nums::is_less_or_equal_zero(point.x_ - cube.x2_) &&
                real_nums::is_more_or_equal_zero(point.y_ - cube.y1_) &&
                real_nums::is_less_or_equal_zero(point.y_ - cube.y2_) &&
                real_nums::is_more_or_equal_zero(point.z_ - cube.z1_) &&
                real_nums::is_less_or_equal_zero(point.z_ - cube.z2_));
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
                   is_point_in_cube(triangle.p1_, cube);
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
            return real_nums::max3(std::abs(point.x_), std::abs(point.y_), std::abs(point.z_));
        }

        double operator()(const line_t &line)
        {
            return real_nums::max6(std::abs(line.p1_.x_), std::abs(line.p1_.y_), std::abs(line.p1_.z_),
                                   std::abs(line.p2_.x_), std::abs(line.p2_.y_), std::abs(line.p2_.z_));
        }

        double operator()(const triangle_t &triangle)
        {
            return real_nums::max9(std::abs(triangle.p1_.x_), std::abs(triangle.p1_.y_), std::abs(triangle.p1_.z_),
                                   std::abs(triangle.p2_.x_), std::abs(triangle.p2_.y_), std::abs(triangle.p2_.z_),
                                   std::abs(triangle.p3_.x_), std::abs(triangle.p3_.y_), std::abs(triangle.p3_.z_));
        }
    };

    double get_max_coord(const std::vector<figure_t> &figs)
    {
        double max_coord = 0;

        for (auto fig : figs)
        {
            double cur_max_coord = std::visit(CallGetMaxCoord{}, fig);
            max_coord = (max_coord < cur_max_coord) ? cur_max_coord : max_coord;
        }

        return max_coord;
    }



} // namespace geometry