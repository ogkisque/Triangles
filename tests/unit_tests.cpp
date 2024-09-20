#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "geometry.hpp"

// bool is_point_on_line(const point_t& p, const line_t& l, bool is_on_segment);
// bool is_point_in_triangle(const point_t& p, const triangle_t& t);
    
// bool is_line_intersect_line(const line_t &line1, const line_t &line2);
// bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle);
// bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2);    std::variant<nullptr_t, point_t, line_t> intersect(const line_t &line, const plane_t &plane);
// bool intersect(const line_t &line, const triangle_t &triangle);

TEST(test1, is_point_on_line_test)
{
    geometry::point_t p1{1, 2, 3};
    geometry::point_t p2{3, 4, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p3{9, 10, 11};

    ASSERT_EQ(geometry::is_point_on_line(p3, l, false), true);
    ASSERT_EQ(geometry::is_point_on_line(p3, l, true), false);
}

TEST(test2, is_point_on_line_test)
{

}