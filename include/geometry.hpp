#include <cmath>
#include <iostream>

#pragma once

namespace geometry {

    class point_t
    {
    public:
        double x_ = NAN; 
        double y_ = NAN;

        bool is_valid() const
        {
            return (x_ != NAN && y_ != NAN);
        }
        
        void print() const
        {
            std::cout << "( " << x_ << " ; " << y_ << " )" << std::endl;
        }

        bool equal(const point_t &other) const
        {
            return (this->x_ == other.x_ && this->y_ == other.y_); 
        }

        point_t(const double x, const double y) : x_(x), y_(y) {}

    }; // class point_t


    class line_t
    {
        double a_ = -1, b_ = 1, c_ = 0;

    public:
        void print() const 
        {
            std::cout << "line:" << a_ << " * x + " << b_ << " y + " << c_ << " = 0" << std::endl;
        }

        bool is_valid() const
        {
            return a_ || b_ || c_;
        }

        line_t(const point_t &p1, const point_t &p2)
        {
            double angle = std::atan((p2.y_ - p1.y_) / (p2.x_ - p1.x_));
            double sin_angle = std::sin(angle);
            double cos_angle = std::sqrt(1 - sin_angle * sin_angle);

            point_t normal_vector{-sin_angle, cos_angle};
            a_ = -sin_angle;
            b_ =  cos_angle;
            c_ = -(p1.x_ * (-sin_angle) + p2.y_ * cos_angle);
        }
        
        line_t(const double a, const double b, const double c) : a_(a), b_(b), c_(c) {}

    }; // class Line

} // namespace geometry