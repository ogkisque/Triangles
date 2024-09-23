#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "geometry.hpp"

// bool is_point_on_line(const point_t& p, const line_t& l, bool is_on_segment);
// bool is_point_in_triangle(const point_t& p, const triangle_t& t);
    
// bool is_line_intersect_line(const line_t &line1, const line_t &line2);
// bool is_line_intersect_triangle_2d(const line_t &line, const triangle_t &triangle);
// bool is_triangle_intersect_triangle(const triangle_t &triangle1, const triangle_t &triangle2);    std::variant<nullptr_t, point_t, line_t> intersect(const line_t &line, const plane_t &plane);
// bool intersect(const line_t &line, const triangle_t &triangle);


// IS_POINT_ON_LINE_TEST

TEST(IS_POINT_ON_LINE_TEST, test_1)
{
    geometry::point_t p1{1, 2, 3};
    geometry::point_t p2{3, 4, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p3{9, 10, 11};

    ASSERT_EQ(geometry::is_point_on_line(p3, l, false), true);
}

TEST(IS_POINT_ON_LINE_TEST, test_2)
{
    geometry::point_t p1{1, 9, 0};
    geometry::point_t p2{4, 10, 13};
    geometry::line_t l{p1, p2};

    geometry::point_t p3{31, 19, 130};

    ASSERT_EQ(geometry::is_point_on_line(p3, l, false), true);

    geometry::point_t p4{33, 18, 130};

    ASSERT_EQ(geometry::is_point_on_line(p4, l, false), false);
}

TEST(IS_POINT_ON_LINE_TEST, test_3)
{
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{12, 3, 6};

    ASSERT_EQ(geometry::is_point_on_line(p, l, false), true);
}

TEST(IS_POINT_ON_LINE_TEST, test_4)
{
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{7, 4, 5};

    ASSERT_EQ(geometry::is_point_on_line(p, l, false), false);
}

TEST(IS_POINT_ON_LINE_TEST, test_5)
{
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{7, 3, 6};

    ASSERT_EQ(geometry::is_point_on_line(p, l, false), false);
}

// IS_POINT_ON_SEGMENT_TEST

TEST(IS_POINT_ON_SEGMENT_TEST, test_1)
{
    geometry::point_t p1{1, 1, 2};
    geometry::point_t p2{3, 5, -2};
    geometry::line_t l{p1, p2};

    geometry::point_t p{2, 3, 0};

    ASSERT_EQ(geometry::is_point_on_line(p, l, true), true);
}

TEST(IS_POINT_ON_SEGMENT_TEST, test_2)
{
    geometry::point_t p1{1, 1, 2};
    geometry::point_t p2{3, 5, -2};
    geometry::line_t l{p1, p2};

    geometry::point_t p{-1, -3, 6};

    ASSERT_EQ(geometry::is_point_on_line(p, l, true), false);
}

// IS POINT IN TRIANGLE

TEST(IS_POINT_IN_TRIANGLE_TEST, test_1)
{
    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(p1, t), true);
    ASSERT_EQ(geometry::is_point_in_triangle(p2, t), true);
    ASSERT_EQ(geometry::is_point_in_triangle(p3, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_2)
{
    geometry::point_t pp{10, 20, 28};

    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_3)
{
    geometry::point_t pp{-15, 43, 26};

    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_4)
{
    geometry::point_t pp{1, 2.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_5)
{
    geometry::point_t pp{2, 0.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_6)
{
    geometry::point_t pp{3, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_7)
{
    geometry::point_t pp{4, 0.99, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_8)
{
    geometry::point_t pp{9, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3, 1};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

// IS LINE INTERSECT LINE

TEST(IS_LINE_INTERSECT_LINE_TEST, test_1)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 2, 0};
    geometry::point_t p4{3,-1, 0};

    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_2)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{4, 1,-3};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_3)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{2, 0.5, 0};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_4)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{-4, -1, 0};
    geometry::point_t p4{8, 2, 0};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_5)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{-4, -1, 0};
    geometry::point_t p4{-2, -0.5, 0};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), false);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_6)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 1, 0};
    geometry::point_t p4{4, 2, 0};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), false);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_7)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{0, 0, 2};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), false);
}
 
TEST(IS_LINE_INTERSECT_LINE_TEST, test_8)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{-3, 1, 6};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), false);
}
