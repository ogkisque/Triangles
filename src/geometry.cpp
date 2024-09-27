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
        
        double a1 = line1.a_;
        double b1 = line1.b_;
        double c1 = line1.c_;
        double a2 = line2.a_;
        double b2 = line2.b_;
        double c2 = line2.c_;
        double x1 = line1.p1_.x_;
        double y1 = line1.p1_.y_;
        double z1 = line1.p1_.z_;
        double x2 = line2.p1_.x_;
        double y2 = line2.p1_.y_;
        double z2 = line2.p1_.z_;

        double det_xy = a2 * b1 - a1 * b2;
        double det_xz = a2 * c1 - a1 * c2;
        double det_yz = b2 * c1 - b1 * c2;
        double det1 = 0;
        double det2 = 0;
        double det = 0;

        double param1 = 0;
        double param2 = 0;
        
        if (!real_nums::is_zero(det_xy))
        {
            det1 = a2 * (y2 - y1) - b2 * (x2 - x1);
            det2 = a1 * (y2 - y1) - b1 * (x2 - x1);
            det = det_xy;

            param1 = det1 / det;
            param2 = det2 / det;

            if (z1 + c1 * param1 != z2 + c2 * param2)
                return false;
        }
        else if (!real_nums::is_zero(det_xz))
        {
            det1 = a2 * (z2 - z1) - c2 * (x2 - x1);
            det2 = a1 * (z2 - z1) - c1 * (x2 - x1);
            det = det_xz;

            param1 = det1 / det;
            param2 = det2 / det;

            if (y1 + b1 * param1 != y2 + b2 * param2)
                return false;
        }
        else if (!real_nums::is_zero(det_yz))
        {
            det1 = b2 * (z2 - z1) - c2 * (y2 - y1);
            det2 = b1 * (z2 - z1) - c1 * (y2 - y1);
            det = det_yz;

            param1 = det1 / det;
            param2 = det2 / det;

            if (x1 + a1 * param1 != x2 + a2 * param2)
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
               is_line_intersect_triangle(triangle1.l3_, triangle2);
    }

} // namespace geometry