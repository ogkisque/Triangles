#include "geometry.hpp"


namespace
{
    const double EPS = std::numeric_limits<double>::epsilon();

    bool equald(const double x, const double y)
    {
        return std::fabs(x - y) < EPS;
    }
}

namespace geometry
{

//  General functions

    bool is_point_on_line(const point_t& p, const line_t& l) // принадлежит ли точка отрезку
    {
        double param1 = 0;
        double param2 = 0;
        double cur_param = 0;
        
        if (!equald(l.a_, 0))
        {
            param2 = (l.p2_.x_ - l.p1_.x_) / l.a_;
            cur_param = (p.x_ - l.p1_.x_) / l.a_;
        }
        else if (!equald(l.b_, 0))
        {
            param2 = (l.p2_.y_ - l.p1_.y_) / l.b_;
            cur_param = (p.y_ - l.p1_.y_) / l.b_;
        }
        else if (!equald(l.c_, 0))
        {
            param2 = (l.p2_.z_ - l.p1_.z_) / l.c_;
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

        return std::min(param1, param2) < cur_param < std::max(param1, param2);
    }

    bool is_point_in_triangle(const point_t& p, const triangle_t& t)
    {
        plane_t plane = t.plane_;
        double temp = plane.a_ * p.x_ + plane.b_ * p.y_ + plane.c_ * p.z_ + plane.d_;
        
        if (!equald(temp, 0))
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
        double scalar3 = v1.scalar_multiply(v3);

        if (scalar1 > EPS && scalar2 > EPS && scalar3 > EPS)
            return true;

        if (scalar1 < EPS && scalar2 < EPS && scalar3 < EPS)
            return true;
        
        return false;
    }

    bool is_line_intersect_line(const line_t &line1, const line_t &line2)
    {
        assert(("Data is not valid", line1.is_valid() && line2.is_valid()));

        double param1 = 0;
        double param2 = 0;
        double param3 = 0;

        double k1 = 0;
        double k2 = 0;
        double k3 = 0;

        if (!equald(line1.a_, 0))
            k1 = line2.a_ / line1.a_;
        else
            k1 = std::numeric_limits<double>::max();
        
        if (!equald(line1.b_, 0))
            k2 = line2.b_ / line1.b_;
        else
            k2 = std::numeric_limits<double>::max();

        if (!equald(line1.c_, 0))
            k3 = line2.c_ / line1.c_;
        else
            k3 = std::numeric_limits<double>::max();

        if (!equald(line1.a_, line2.a_))
            param1 = (line1.p1_.x_ - line2.p1_.x_) / (line2.a_ - line1.a_);
        else
            param1 = std::numeric_limits<double>::max();

        if (!equald(line1.b_, line2.b_))
            param2 = (line1.p1_.y_ - line2.p1_.y_) / (line2.b_ - line1.b_);
        else
            param2 = std::numeric_limits<double>::max();

        if (!equald(line1.c_, line2.c_))
            param3 = (line1.p1_.z_ - line2.p1_.z_) / (line2.c_ - line1.c_);
        else
            param3 = std::numeric_limits<double>::max();

        if (k1 == k2 == k3) // parallel or identic
        {
            if (is_point_on_line(line1.p1_, line2)) 
            {

            }
            if (param1 == param2 == param3)
            {
                if (param1 == std::numeric_limits<double>::max())
                {
                    return 
                }
                else // different a, b, c 
                {
                    
                }
            }
        }
        else // intersect
        {
            point_t intersect_point{line1.p1_.x_ + param1 * line1.a_,
                                    line1.p1_.y_ + param1 * line1.b_,
                                    line1.p1_.z_ + param1 * line1.c_};

            return is_point_on_line(intersect_point, line1) &&
                   is_point_on_line(intersect_point, line2);
        }
        

        return false;
    }

    bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle)
    {
        if (is_line_intersect_line(line, triangle.l1_))
            return true;
        if (is_line_intersect_line(line, triangle.l2_))
            return true;
        if (is_line_intersect_line(line, triangle.l3_))
            return true;
    }

    std::variant<nullptr_t, point_t, line_t> intersect(const line_t &line, const plane_t &plane)
    {
        assert(("Data is not valid", line.is_valid() && plane.is_valid()));

        double tmp1 = line.a_ * plane.a_ + line.b_ * plane.b_ + line.c_ * plane.c_;
        double tmp2 = plane.a_ * line.p1_.x_ + plane.b_ * line.p1_.y_ + plane.c_ * line.p1_.z_ + plane.d_;
        if (tmp1 == 0)
        {
            if (tmp2 == 0)  // line on plane
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
            
            if (is_point_on_line(point_on_plane, line))
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
        }   
    }

    bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2)
    {
        if (intersect(triangle1.l1_, triangle2))
            return true;
        if (intersect(triangle1.l2_, triangle2))
            return true;
        if (intersect(triangle1.l3_, triangle2))
            return true;
    }


//  =========================== Point functions ===========================

    void point_t::print() const
    {
        std::cout << "( " << x_ << " ; " << y_ << " )" << std::endl;
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
        "z = " << p1_.z_ << " + t * " << c_ << std::endl;
    }

    double line_t::get_length() const
    {
        return sqrt((p1_.x_ - p2_.x_) * (p1_.x_ - p2_.x_) + 
                    (p1_.y_ - p2_.y_) * (p1_.y_ - p2_.y_) +
                    (p1_.z_ - p2_.z_) * (p1_.z_ - p2_.z_));
    }


//  =========================== Triangle functions ===========================

    triangle_t::triangle_t(const point_t &p1, const point_t &p2, const point_t &p3, int id) :
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
        vector_t v1{p1.x_, p1.y_, p1.z_};

        vector_t v2{p1, p2};
        vector_t v3{p1, p3};

        a_ = v2.y_ * v3.z_ - v2.z_ * v3.y_;
        b_ = v2.z_ * v3.x_ - v2.x_ * v3.z_;
        c_ = v2.z_ * v3.x_ - v2.x_ * v3.z_;
        d_ = -v1.x_ * a_ - v1.y_ * b_ - v1.z_ * c_;
    }

    bool plane_t::is_valid() const
    {
        return (a_ || b_ || c_);
    }


//  =========================== Vector functions ============================

    vector_t::vector_t(const point_t& p1, const point_t& p2) : x_(p2.x_ - p1.x_), y_(p2.y_ - p1.y_), z_(p2.z_ - p1.z_) {}
    vector_t::vector_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}

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