#include "geometry.hpp"


namespace {
    bool equald(const double x, const double y)
    {
        return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
    }
}

namespace geometry{

    bool point_belongs_to_line(const point_t& p, const line_t& l)
    {
        ///TODO: not done
        
        double param = 0;
        
        if (!equald(l.a_, 0))
            param = (p.x_ - l.p1_.x_) / l.a_;
        else if (!equald(l.b_, 0))
            param = (p.y_ - l.p1_.y_) / l.b_;
        else if (!equald(l.c_, 0))
            param = (p.z_ - l.p1_.z_) / l.c_;
        else
            // is not valid

        point_t temp_point{l.p1_.x_ + l.a_* param, l.p1_.y_ + l.b_ * param, l.p1_.z_ + l.c_ * param};

        if (!(temp_point == p))
            return false;

        point_t p1 = l.p1_;
        point_t p2 = l.p1_;
        
        if ((p.x_ > p1.x_ && p.x_ > p2.x_) || (p.x_ < p1.x_ && p.x_ < p2.x_))
            return false;
        if ((p.y_ > p1.y_ && p.y_ > p2.y_) || (p.y_ < p1.y_ && p.y_ < p2.y_))
            return false;
        if ((p.z_ > p1.z_ && p.z_ > p2.z_) || (p.z_ < p1.z_ && p.z_ < p2.z_))
            return false;

        return true;
    }

    bool point_t::is_valid() const
    {
        return (x_ != NAN && y_ != NAN && z_ != NAN);
    }
    
    void point_t::print() const
    {
        std::cout << "( " << x_ << " ; " << y_ << " )" << std::endl;
    }

    bool point_t::equal(const point_t &other) const
    {
        return equald(this->x_, other.x_) && equald(this->y_, other.y_) && equald(this->z_, other.z_); 
    }

    bool line_t::is_valid() const 
    {
        bool is_valid = p1_.is_valid() && p2_.is_valid();
        is_valid &= a_ != NAN && b_ != NAN && c_ != NAN;
        is_valid &= a_ || b_ || c_;
        
        return is_valid;
    }

    void line_t::print() const 
    {
        std::cout << "line:" << a_ << " * x + " << b_ << " y + " << c_ << " = 0" << std::endl;
    }

    line_t::line_t(const point_t &p1, const point_t &p2) :  p1_(p1), p2_(p2), a_(p2.x_ - p1.x_), b_(p2.y_ - p1.y_), c_(p2.z_ - p1.z_) {}

    bool triangle_t::is_valid() const
    {
        bool is_valid = l1_.is_valid() && l2_.is_valid() && l3_.line_t::is_valid(); 
        
        if (!is_valid)
            return false;

        double frac1 = 0, frac2 = 0, frac3 = 0;

        if (!equald(l2_.a_, 0))
            frac1 = l1_.a_ / l2_.a_;
            
        if (!equald(l2_.b_, 0))
            frac2 = l1_.b_ / l2_.b_;

        if (!equald(l2_.c_, 0))
            frac3 = l1_.c_ / l2_.c_;
        
        is_valid &= (frac1 == frac2 && frac2 == frac3);

        return is_valid;
    }

    plane_t::plane_t(const point_t p1, const point_t p2, const point_t p3)
    {
        ///TODO: c_tor plane
    }

} // namespace geometry