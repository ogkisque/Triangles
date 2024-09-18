#include "geometry.hpp"


namespace {
    bool equal(const double x, const double y)
    {
        return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
    }
}

namespace geometry{
    
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
            bool equal = std::fabs(this->x_ - other.x_) < std::numeric_limits<double>::epsilon();
            equal &= std::fabs(this->y_ - other.y_) < std::numeric_limits<double>::epsilon();
            equal &= std::fabs(this->z_ - other.z_) < std::numeric_limits<double>::epsilon();
            return equal; 
        }

        bool line_t::is_valid() const 
        {
            bool is_valid = x0_ != NAN && y0_ != NAN && z0_ != NAN; 
            is_valid = a_ != NAN && b_ != NAN && c_ != NAN;
            is_valid &= a_ || b_ || c_;
            
            return is_valid;
        }

        void line_t::print() const 
        {
            std::cout << "line:" << a_ << " * x + " << b_ << " y + " << c_ << " = 0" << std::endl;
        }

        line_t::line_t(const point_t &p1, const point_t &p2) :  x0_(p1.x_),        y0_(p1.y_),        z0_(p1.z_),
                                                                a_(p2.x_ - p1.x_), b_(p2.y_ - p1.y_), c_(p2.z_ - p1.z_) {}

        bool triangle_t::is_valid() const
        {
            bool is_valid = l1_.is_valid() && l2_.is_valid() && l3_.line_t::is_valid(); 
            
            if (!is_valid)
                return false;

            double frac1 = 0, frac2 = 0, frac3 = 0;

            
            if (!equal(l2_.a_, 0))
                frac1 = l1_.a_ / l2_.a_;
                
            if (!equal(l2_.b_, 0))
                frac2 = l1_.b_ / l2_.b_;

            if (!equal(l2_.c_, 0))
                frac3 = l1_.c_ / l2_.c_;
            
            is_valid &= (frac1 == frac2 && frac2 == frac3);

            return is_valid;
        }
        

} // namespace geometry