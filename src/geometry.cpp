#include "geometry.hpp"


namespace
{
    bool equald(const double x, const double y)
    {
        return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
    }
}

namespace geometry
{

//  General functions

    bool point_belongs_to_line(const point_t& p, const line_t& l) // принадлежит ли точка отрезку
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

    bool point_belongs_to_plane(const point_t& p, const triangle_t& t) // принадлежит ли точка треугольнику
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

        if (scalar1 >= 0 && scalar2 >= 0 && scalar3 >= 0)
            return true;

        if (scalar1 < 0 && scalar2 < 0 && scalar3 < 0)
            return true;
        
        return false;
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


//  =========================== Vector functions ============================

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