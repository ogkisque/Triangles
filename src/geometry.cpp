#include "geometry.hpp"

namespace geometry{
    
        bool point_t::is_valid() const
        {
            return (x_ != NAN && y_ != NAN);
        }
        
        void point_t::print() const
        {
            std::cout << "( " << x_ << " ; " << y_ << " )" << std::endl;
        }

        bool point_t::equal(const point_t &other) const
        {
            return (this->x_ == other.x_ && this->y_ == other.y_); 
        }

        bool line_t::is_valid() const 
        {
            return a_ || b_ || c_;
        }

        void line_t::print() const 
        {
            std::cout << "line:" << a_ << " * x + " << b_ << " y + " << c_ << " = 0" << std::endl;
        }

        line_t::line_t(const point_t &p1, const point_t &p2)
        {
            double angle = std::atan((p2.y_ - p1.y_) / (p2.x_ - p1.x_));
            double sin_angle = std::sin(angle);
            double cos_angle = std::sqrt(1 - sin_angle * sin_angle);

            point_t normal_vector{-sin_angle, cos_angle};
            a_ = -sin_angle;
            b_ =  cos_angle;
            c_ = -(p1.x_ * (-sin_angle) + p2.y_ * cos_angle);
        }

} // namespace geometry