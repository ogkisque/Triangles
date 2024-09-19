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


//  =========================== Point functions ===========================

    point_t::point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
    point_t::point_t(const point_t &point) : x_(point.x_), y_(point.y_), z_(point.z_) {}

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
        double x1 = p1.x_;
        double y1 = p1.y_;
        double z1 = p1.z_;
        double delta_x2 = p2.x_ - p1.x_;
        double delta_y2 = p2.y_ - p1.y_;
        double delta_z2 = p2.z_ - p1.z_;
        double delta_x3 = p3.x_ - p1.x_;
        double delta_y3 = p3.y_ - p1.y_;
        double delta_z3 = p3.z_ - p1.z_;

        a_ = delta_y2 * delta_z3 - delta_y3 * delta_z2;
        b_ = delta_z2 * delta_x3 - delta_z3 * delta_x2;
        c_ = delta_y2 * delta_z3 - delta_y3 * delta_z2;
        d_ = -x1 * a_ - y1 * b_ - z1 * c_;
    }

//  ========================== Intersection functions ==========================
    intersection::intersection(const point_t &point)
    {
        type_ = intersection::type::POINT;
        point_ = point;
    }

    

} // namespace geometry