#include "geometry.hpp"

namespace geometry
{
    //  =========================== Point functions ===========================

    point_t::point_t(const double x, const double y, const double z) :
        x_(x), y_(y), z_(z) {}
    point_t::point_t(const point_t &point) : x_(point.x_), y_(point.y_), z_(point.z_) {}

    void point_t::print() const
    {
        std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
    }

    bool point_t::operator==(const point_t &other) const
    {
        return real_nums::equald(this->x_, other.x_) &&
               real_nums::equald(this->y_, other.y_) &&
               real_nums::equald(this->z_, other.z_); 
    }

    bool point_t::operator!=(const point_t& other) const
    {
        return !real_nums::equald(this->x_, other.x_) ||
               !real_nums::equald(this->y_, other.y_) ||
               !real_nums::equald(this->z_, other.z_);
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

    triangle_t::triangle_t(const point_t &p1, const point_t &p2, const point_t &p3) :
            p1_(p1), p2_(p2), p3_(p3),
            l1_(p1, p2), l2_(p2, p3), l3_(p3, p1),
            plane_(p1, p2, p3)
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

    void triangle_t::print() const
    {
        this->plane_.print();
        this->p1_.print();
        this->p2_.print();
        this->p3_.print();
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

    void plane_t::print() const
    {
        std::cout << a_ << " * x + " << b_ << " * y + " << c_ << " * z + " << d_ << std::endl;
    }

//  ============================ Cube functions =============================

    cube_t::cube_t(double x1, double x2, double y1, double y2, double z1, double z2) : 
        x1_(x1), x2_(x2), y1_(y1), y2_(y2), z1_(z1), z2_(z2) {}


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

    void vector_t::print() const 
    {
        std::cout << "vector: " << x_ << " " << y_ << " " << z_ << std::endl;
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
