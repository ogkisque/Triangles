#include "geometry.hpp"

namespace
{
    const double EPS = std::numeric_limits<double>::epsilon();
    const double MAX = std::numeric_limits<double>::max();

    bool is_zero(const double x)
    {
        return std::fabs(x) < EPS;
    }

    inline bool equald(const double x, const double y)
    {
        return std::fabs(x - y) < EPS;
    }

    bool is_more_zero(const double x)
    {
        return x > EPS;
    }

    bool is_less_zero(const double x)
    {
        return x < -EPS;
    }

    bool is_more_or_equal_zero(const double x)
    {
        return is_more_zero(x) || is_zero(x);
    }

    bool is_less_or_equal_zero(const double x)
    {
        return is_less_zero(x) || is_zero(x);
    }
}

namespace geometry
{

//  General functions

    bool is_point_on_line(const point_t& p, const line_t& l, bool is_on_segment)
    {
        double cur_param = 0;
        
        if (!is_zero(l.a_))
        {
            cur_param = (p.x_ - l.p1_.x_) / l.a_;
        }
        else if (!is_zero(l.b_))
        {
            cur_param = (p.y_ - l.p1_.y_) / l.b_;
        }
        else if (!is_zero(l.c_))
        {
            cur_param = (p.z_ - l.p1_.z_) / l.c_;
        }
        else
        {
            assert(("Line is not valid", 0));
        }

        point_t temp_point{l.p1_.x_ + l.a_ * cur_param,
                           l.p1_.y_ + l.b_ * cur_param,
                           l.p1_.z_ + l.c_ * cur_param};

        if (!(temp_point == p))
            return false;

        if (is_on_segment)
            return 0 <= cur_param && cur_param <= 1; 

        return true;
    }

    bool is_point_in_triangle(const point_t& p, const triangle_t& t)
    {       
        double plane_equation = t.plane_.a_ * p.x_ + t.plane_.b_ * p.y_ + t.plane_.c_ * p.z_ + t.plane_.d_;
        
        if (!is_zero(plane_equation))
            return false;
        
        point_t A = t.p1_, B = t.p2_, C = t.p3_, O = p;

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

        if (is_more_or_equal_zero(scalar1) && is_more_or_equal_zero(scalar2) && is_more_or_equal_zero(scalar3))
            return true;

        if (is_less_or_equal_zero(scalar1) && is_less_or_equal_zero(scalar2) && is_less_or_equal_zero(scalar3))
            return true;
        
        return false;
    }

    bool is_line_intersect_line(const line_t &line1, const line_t &line2)
    {
        assert(("Data is not valid", line1.is_valid() && line2.is_valid()));

        line1.print();
        line2.print();

        vector_t tangent1{line1.a_, line1.b_, line2.c_};
        vector_t tangent2{line2.a_, line2.b_, line2.c_};

        vector_t vec_multiply = tangent1.vector_multiply(tangent2);

        if (vec_multiply.is_null()) // parallel or identic
        {
            if (is_point_on_line(line1.p1_, line2, false)) // identic lines
            {
                return is_point_on_line(line1.p1_, line2, true) || is_point_on_line(line1.p2_, line2, true);
            }

            // parallel
            return false;
        }

        // intersect
        
        point_t start1 = line1.p1_;
        point_t start2 = line1.p2_;

        double param1 = 0;
        double param2 = 0;


        if (!is_zero(line1.a_))
        {
            double coef1 = line1.a_ * line2.b_ - line1.b_ * line2.a_;
            double free_coef1 = line1.a_ * (start1.y_ - start2.y_) - line1.b_ * (start1.x_ - start2.x_);
            
            if (is_zero(coef1))
            {
                if (!is_zero(free_coef1))
                    assert(("param2 not exist", 0));
                else
                {
                    double coef2 = line1.b_ * line2.c_ - line1.c_ * line2.b_;
                    double free_coef2 = line1.b_ * (start1.z_ - start2.z_) - line1.c_ * (start1.y_ - start2.y_);
                    
                    // param2 = 0;
                }
            }
            else
            {
                param2 = free_coef1 / coef1;
            }
            param1 = (start2.x_ - start1.x_ + line1.a_ * param1) / line1.a_;
            
            printf("param1 = %lg, param2 = %lg\n", param1, param2);

            // if (!equald(start1.z_ + line1.c_ * param1, start2.z_ + line2.c_ * param2))
            //     return false;
        }
        else if (!is_zero(line1.b_))
        {
            // double coef = line1.b_ * line2.c_ - line1.c_ * line2.b_;
            // double free_coef = line1.b_ * (start1.z_ - start2.z_) - line1.c_ * (start1.y_ - start2.y_);

            double coef1 = line2.a_;
            double free_coef1 = start1.x_ - start2.x_;

            if (is_zero(coef1))
            {
                if (!is_zero(free_coef1))
                    assert(("param2 not exist", 0));
                else
                {
                    double coef2 = line1.b_ * line2.c_ - line1.c_ * line2.b_;
                    double free_coef2 = line1.b_ * (start1.z_ - start2.z_) - line1.c_ * (start1.y_ - start2.y_);
                    
                    // param2 = 0;
                }
            }
            else
            {
                param2 = free_coef1 / coef1;
            }

            param1 = (start2.y_ - start1.y_ + line2.b_ * param2) / line1.b_;

            if (!equald(start1.z_ + line1.c_ * param1, start2.z_ + line2.c_ * param2))
                return false;
            
            printf("param1 = %lg, param2 = %lg\n", param1, param2);
        }
        else if (!is_zero(line1.c_))
        {
            double coef1 = line1.a_;
            double free_coef1 = start1.x_ - start2.x_;
            
            if (is_zero(coef1))
            {
                if (!is_zero(free_coef1))
                    assert(("param2 not exist", 0));
                else
                {
                    double coef2 = line1.b_;
                    double free_coef2 = start1.y_ - start2.y_;

                    if (is_zero(coef2))
                    {
                        assert(("param2 not exist", 0));
                    }
                    else
                    {
                        param2 = free_coef2 / coef2;
                    }
                }
            }
            else
            {
                param2 = free_coef1 / coef1;
            }

            // if (!equald(start1.y_, start2.y_ + line2.b_ * param2))
            //     return false;
            
            param1 = (start2.z_ - start1.z_ + line2.c_ * param2) / line1.c_; 

            printf("param1 = %lg, param2 = %lg\n", param1, param2);
        }
        else
        {
            assert(("line1 is not valid", 0));
        }

        printf("param1 = %lg, param2 = %lg\n", param1, param2);

        point_t p1{start1.x_ + line1.a_ * param1, start1.y_ + line1.b_ * param1, start1.z_ + line1.c_ * param1};
        point_t p2{start2.x_ + line2.a_ * param2, start2.y_ + line2.b_ * param2, start2.z_ + line2.c_ * param2};

        p1.print();
        p2.print();

        return (p1 == p2);
    }

    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle)
    {
        return is_line_intersect_line(line, triangle.l1_) ||
               is_line_intersect_line(line, triangle.l2_) ||
               is_line_intersect_line(line, triangle.l3_);
    }

    std::variant<nullptr_t, point_t, line_t> intersect(const line_t &line, const plane_t &plane)
    {
        assert(("Data is not valid", line.is_valid() && plane.is_valid()));

        double tmp1 = line.a_ * plane.a_ + line.b_ * plane.b_ + line.c_ * plane.c_;
        double tmp2 = plane.a_ * line.p1_.x_ + plane.b_ * line.p1_.y_ + plane.c_ * line.p1_.z_ + plane.d_; // function
        
        if (is_zero(tmp1))
        {
            if (is_zero(tmp2))  // line on plane
                return line;
            else            // line parallel to plane
                return nullptr;
        }
        else                // line intersect plane
        {
            double param = tmp2 / tmp1;
            point_t point_on_plane{line.p1_.x_ + param * line.a_,
                                   line.p1_.y_ + param * line.b_,
                                   line.p1_.z_ + param * line.c_};
            
            if (is_point_on_line(point_on_plane, line, true))
                return point_on_plane;
            else
                return nullptr;
        }
    }

    bool intersect(const line_t &line, const triangle_t &triangle)
    {
        assert(("Data is not valid", line.is_valid() && triangle.is_valid()));

        auto intersection = intersect(line, triangle.plane_);
        switch (intersection.index())
        {
            case 0:
                return false;
            case 1:
                return is_point_in_triangle(std::get<point_t>(intersection), triangle);
            case 2:
                return is_line_intersect_triangle_2d(std::get<line_t>(intersection), triangle);
            default:
                assert(("incorect std::variant type", 0));
        }
    }

    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2)
    {
        return intersect(triangle1.l1_, triangle2) ||
               intersect(triangle1.l2_, triangle2) ||
               intersect(triangle1.l3_, triangle2);
    }


//  =========================== Point functions ===========================

    point_t::point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
    point_t::point_t(const point_t &point) : x_(point.x_), y_(point.y_), z_(point.z_) {}

    void point_t::print() const
    {
        std::cout << "(" << x_ << "; " << y_ << "; " << z_ << ")" << std::endl;
    }

    bool point_t::operator==(const point_t &other) const
    {
        return equald(this->x_, other.x_) && equald(this->y_, other.y_) && equald(this->z_, other.z_); 
    }


//  =========================== Line functions ============================

    line_t::line_t(const point_t &p1, const point_t &p2) :  
        p1_(p1), p2_(p2),
        a_(p2.x_ - p1.x_),
        b_(p2.y_ - p1.y_),
        c_(p2.z_ - p1.z_)
        {}

    bool line_t::is_valid() const 
    {
        bool is_valid = true;
        is_valid &= (a_ != NAN && b_ != NAN && c_ != NAN);
        is_valid &= (a_ || b_ || c_);
        
        return is_valid;
    }

    void line_t::print() const 
    {
        std::cout << "line:" << std::endl <<
        "x = " << p1_.x_ << " + t * " << a_ << std::endl <<
        "y = " << p1_.y_ << " + t * " << b_ << std::endl <<
        "z = " << p1_.z_ << " + t * " << c_ << std::endl <<
        "segment:" << std::endl;
        p1_.print();
        p2_.print();
    }

    double line_t::get_length() const
    {
        return sqrt((p1_.x_ - p2_.x_) * (p1_.x_ - p2_.x_) + 
                    (p1_.y_ - p2_.y_) * (p1_.y_ - p2_.y_) +
                    (p1_.z_ - p2_.z_) * (p1_.z_ - p2_.z_));
    }


//  =========================== Triangle functions ===========================

    triangle_t::triangle_t(const point_t &p1, const point_t &p2, const point_t &p3, size_t id) :
            p1_(p1), p2_(p2), p3_(p3),
            l1_(p1, p2), l2_(p2, p3), l3_(p3, p1),
            plane_(p1, p2, p3), id_(id)
            {}

    bool triangle_t::is_valid() const
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


//  ============================ Plane functions ============================

    plane_t::plane_t(const point_t &p1, const point_t &p2, const point_t &p3)
    {
        vector_t p1p2{p1, p2};
        vector_t p1p3{p1, p3};

        a_ =   p1p2.y_ * p1p3.z_ - p1p3.y_ * p1p2.z_;
        b_ = - p1p2.x_ * p1p3.z_ + p1p3.x_ * p1p2.z_;
        c_ =   p1p2.x_ * p1p3.y_ - p1p3.x_ * p1p2.y_;
        
        d_ = - p1.x_ * a_ - p1.y_ * b_ - p1.z_ * c_;
    }

    bool plane_t::is_valid() const
    {
        return (a_ || b_ || c_);
    }


//  =========================== Vector functions ============================

    vector_t::vector_t(const point_t& p1, const point_t& p2) : x_(p2.x_ - p1.x_), 
                                                               y_(p2.y_ - p1.y_), 
                                                               z_(p2.z_ - p1.z_) 
                                                               {}
    vector_t::vector_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}

    bool vector_t::is_null() const
    {
        return !(x_ || y_ || z_);
    }

    vector_t vector_t::vector_multiply(const vector_t& other) const
    {
        vector_t ret_v{ this->y_ * other.z_ - this->z_ * other.y_, 
                      -(this->x_ * other.z_ - this->z_ * other.x_), 
                        this->x_ * other.y_ - this->y_ * other.x_ };

        return ret_v;
    }

    double vector_t::scalar_multiply(const vector_t& other) const
    {
        return (this->x_ * other.x_ + this->y_ * other.y_ + this->z_ * other.z_);
    }

} // namespace geometry