#include "geometry.hpp"

namespace geometry
{
    //  =========================== Point functions ===========================

    point_t::point_t(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
    point_t::point_t(const point_t &point) : x_(point.x_), y_(point.y_), z_(point.z_) {}

    void point_t::print() const
    {
        std::cout << "(" << x_ << "; " << y_ << "; " << z_ << ")" << std::endl;
    }

    bool point_t::operator==(const point_t &other) const
    {
        return real_nums::equald(this->x_, other.x_) &&
               real_nums::equald(this->y_, other.y_) &&
               real_nums::equald(this->z_, other.z_); 
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


//  =========================== Square functions ============================

    square_t::square_t(const point_t& p1, const point_t& p2, const point_t& p3) :
        p1_(p1), p2_(p2), p3_(p3),
        size_(sqrt((p1.x_ - p2.x_) * (p1.x_ - p2.x_) + 
                   (p1.y_ - p2.y_) * (p1.y_ - p2.y_) +
                   (p1.z_ - p2.z_) * (p1.z_ - p2.z_))),
        plane_(p1, p2, p3)
    {}

//  ============================ Cube functions =============================

    cube_t::cube_t(const point_t& start, double x_size, double y_size, double z_size) : start_point_(start),
                                                                                        x_size_(x_size),
                                                                                        y_size_(y_size),
                                                                                        z_size_(z_size)
    {
        *planes[0] = {start_point_, {start_point_.x_ + , start_point_};
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
