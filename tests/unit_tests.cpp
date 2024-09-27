#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "geometry.hpp"

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

    geometry::triangle_t t{p1, p2, p3};

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

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_3)
{
    geometry::point_t pp{-15, 43, 26};

    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_4)
{
    geometry::point_t pp{1, 2.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_5)
{
    geometry::point_t pp{2, 0.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_6)
{
    geometry::point_t pp{3, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_7)
{
    geometry::point_t pp{4, 0.99, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_8)
{
    geometry::point_t pp{9, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(geometry::is_point_in_triangle(pp, t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_9)
{
    geometry::point_t pp{0, -9, 0};

    geometry::point_t p1{8, 9, 0};
    geometry::point_t p2{0, 4, 0};
    geometry::point_t p3{12, 18, 0};

    geometry::triangle_t t{p1, p2, p3};

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
    geometry::point_t p4{-3, 100, 6};
    
    geometry::line_t  l2{p3, p4};


    ASSERT_EQ(geometry::is_line_intersect_line(l1, l2), false);
}

// IS TRIANGLE INTERSECT TRIANGLE

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_1)
{
    geometry::point_t p1{4, 2, 0};
    geometry::point_t p2{5, 6, 0};
    geometry::point_t p3{9, 2, 0};
    geometry::point_t p4{11, 2, 0};
    geometry::point_t p5{13, 10, 0};
    geometry::point_t p6{12, 2, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), false);
}


TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_2)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{5, 5, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_3)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{3, 3, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_4)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{5, 5, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_5)
{
    geometry::point_t p1{-3, 2, 2};
    geometry::point_t p2{-4, 4.5, 1};
    geometry::point_t p3{-5.5, 4, -1};
    geometry::point_t p4{-5.5, 4, 0};
    geometry::point_t p5{-1, 3, 0};
    geometry::point_t p6{-3.7, -4, 10};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_6)
{
    geometry::point_t p1{-5, -7, 0};
    geometry::point_t p2{0, 0, 2};
    geometry::point_t p3{6, 0, 0};
    geometry::point_t p4{0, -8, 0};
    geometry::point_t p5{3, 0, 0};
    geometry::point_t p6{0, 5, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_7)
{
    //
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{0, 0, 4};
    geometry::point_t p3{4, 0, 0};

    geometry::point_t p4{8, 9, 0};
    geometry::point_t p5{0, 4, 0};
    geometry::point_t p6{12, 18, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_8)
{
    //
    geometry::point_t p1{-5, 3, -4};
    geometry::point_t p2{3, -8, 0};
    geometry::point_t p3{0, 0, 6};
    geometry::point_t p4{0, 9, 0};
    geometry::point_t p5{-8, 0, 0};
    geometry::point_t p6{0, -10, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_9)
{
    geometry::point_t p1{-6, 0, 0};
    geometry::point_t p2{0, 0, 3};
    geometry::point_t p3{-9, 7, 4};
    geometry::point_t p4{-3, 0, 1.5};
    geometry::point_t p5{0, 0, 7};
    geometry::point_t p6{3, 0, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_10)
{
    geometry::point_t p1{-7, 0, 0};
    geometry::point_t p2{0, -7, 0};
    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{3, 0, 0};
    geometry::point_t p5{0, 3, 0};
    geometry::point_t p6{9, 0, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_11)
{
    geometry::point_t p1{-7, 0, 0};
    geometry::point_t p2{0, -7, 0};
    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{3, 0, 9};
    geometry::point_t p5{0, 3, 0};
    geometry::point_t p6{9, 0, 0};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_12)
{
    geometry::point_t p1{-8, 0, 0};
    geometry::point_t p2{0, -9, 0};
    geometry::point_t p3{-3.7, -3.12, 10};
    geometry::point_t p4{-7, -6.37, 0};
    geometry::point_t p5{4.66, -5.92, 0};
    geometry::point_t p6{0, 0, 5};
    
    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(geometry::is_triangle_intersect_triangle(t1, t2), true);
}


// LINE INTERSECT PLANE

TEST(IS_LINE_INTERSECT_PLANE, test_1)
{
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{-3, -4, 3};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{-4, 0, 0};
    geometry::point_t p4{0, -5, 0};
    geometry::point_t p5{0, 0, 4};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    
    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_2)
{
    geometry::point_t p1{-2, -5, -1};
    geometry::point_t p2{-6, 5, 6};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{-5, -5, 2};
    geometry::point_t p4{-3, 3, -2};
    geometry::point_t p5{6, -5, 6};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    
    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_3)
{
    geometry::point_t p1{0, 0, 3};
    geometry::point_t p2{0, -3, 0};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{-6, 0, 0};
    geometry::point_t p4{0, 0, 7};
    geometry::point_t p5{0, -7, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    
    ASSERT_EQ(intersection.index(), 0);
}

TEST(IS_LINE_INTERSECT_PLANE, test_4)
{
    geometry::point_t p1{-3.5046, -5.56986, 3};
    geometry::point_t p2{-3.39954, 1.64817, -1.53242};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{-3.5046, -5.56986, 3};
    geometry::point_t p5{-3.39954, 1.64817, -1.53242};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    
    ASSERT_EQ(intersection.index(), 2);
}


TEST(IS_LINE_INTERSECT_PLANE, test_5)
{
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{4, 0, 0};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    ASSERT_EQ(intersection.index(), 2);
}

TEST(IS_LINE_INTERSECT_PLANE, test_6)
{
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{0, 0, 4};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_7)
{
    geometry::point_t p1{0, 0, 4};
    geometry::point_t p2{4, 0, 0};
    geometry::line_t  l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = get_line_plane_intersection(l1, t1.plane_);
    ASSERT_EQ(intersection.index(), 1);
}