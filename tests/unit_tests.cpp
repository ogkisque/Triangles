#include "geometry.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// IS_POINT_ON_LINE_TEST

TEST(IS_POINT_ON_LINE_TEST, test_1) {
    geometry::point_t p1{1, 2, 3};
    geometry::point_t p2{3, 4, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p3{9, 10, 11};

    ASSERT_EQ(p3.is_on_line(l, false), true);
}

TEST(IS_POINT_ON_LINE_TEST, test_2) {
    geometry::point_t p1{1, 9, 0};
    geometry::point_t p2{4, 10, 13};
    geometry::line_t l{p1, p2};

    geometry::point_t p3{31, 19, 130};

    ASSERT_EQ(p3.is_on_line(l, false), true);

    geometry::point_t p4{33, 18, 130};

    ASSERT_EQ(p4.is_on_line(l, false), false);
}

TEST(IS_POINT_ON_LINE_TEST, test_3) {
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{12, 3, 6};

    ASSERT_EQ(p.is_on_line(l, false), true);
}

TEST(IS_POINT_ON_LINE_TEST, test_4) {
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{7, 4, 5};

    ASSERT_EQ(p.is_on_line(l, false), false);
}

TEST(IS_POINT_ON_LINE_TEST, test_5) {
    geometry::point_t p1{2, 3, 4};
    geometry::point_t p2{7, 3, 5};
    geometry::line_t l{p1, p2};

    geometry::point_t p{7, 3, 6};

    ASSERT_EQ(p.is_on_line(l, false), false);
}

// IS_POINT_ON_SEGMENT_TEST

TEST(IS_POINT_ON_SEGMENT_TEST, test_1) {
    geometry::point_t p1{1, 1, 2};
    geometry::point_t p2{3, 5, -2};
    geometry::line_t l{p1, p2};

    geometry::point_t p{2, 3, 0};

    ASSERT_EQ(p.is_on_line(l, true), true);
}

TEST(IS_POINT_ON_SEGMENT_TEST, test_2) {
    geometry::point_t p1{1, 1, 2};
    geometry::point_t p2{3, 5, -2};
    geometry::line_t l{p1, p2};

    geometry::point_t p{-1, -3, 6};

    ASSERT_EQ(p.is_on_line(l, true), false);
}

// IS POINT IN TRIANGLE

TEST(IS_POINT_IN_TRIANGLE_TEST, test_1) {
    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(p1.is_in_triangle(t), true);
    ASSERT_EQ(p2.is_in_triangle(t), true);
    ASSERT_EQ(p3.is_in_triangle(t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_2) {
    geometry::point_t pp{10, 20, 28};

    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_3) {
    geometry::point_t pp{-15, 43, 26};

    geometry::point_t p1{1, 3, 2};
    geometry::point_t p2{4, 2, 4};
    geometry::point_t p3{1, 4, 3};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_4) {
    geometry::point_t pp{1, 2.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_5) {
    geometry::point_t pp{2, 0.5, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_6) {
    geometry::point_t pp{3, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), true);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_7) {
    geometry::point_t pp{4, 0.99, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_8) {
    geometry::point_t pp{9, 1, 0};

    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};
    geometry::point_t p3{1, 2.5, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), false);
}

TEST(IS_POINT_IN_TRIANGLE_TEST, test_9) {
    geometry::point_t pp{0, -9, 0};

    geometry::point_t p1{8, 9, 0};
    geometry::point_t p2{0, 4, 0};
    geometry::point_t p3{12, 18, 0};

    geometry::triangle_t t{p1, p2, p3};

    ASSERT_EQ(pp.is_in_triangle(t), false);
}

// IS LINE INTERSECT LINE

TEST(IS_LINE_INTERSECT_LINE_TEST, test_1) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 2, 0};
    geometry::point_t p4{3, -1, 0};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_2) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{4, 1, -3};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_3) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{2, 0.5, 0};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_4) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{-4, -1, 0};
    geometry::point_t p4{8, 2, 0};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), true);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_5) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{-4, -1, 0};
    geometry::point_t p4{-2, -0.5, 0};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), false);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_6) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 1, 0};
    geometry::point_t p4{4, 2, 0};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), false);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_7) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{0, 0, 2};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), false);
}

TEST(IS_LINE_INTERSECT_LINE_TEST, test_8) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{4, 1, 0};

    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 0, 5};
    geometry::point_t p4{-3, 100, 6};

    geometry::line_t l2{p3, p4};

    ASSERT_EQ(l1.is_intersect_line(l2), false);
}

// IS TRIANGLE INTERSECT TRIANGLE

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_1) {
    geometry::point_t p1{4, 2, 0};
    geometry::point_t p2{5, 6, 0};
    geometry::point_t p3{9, 2, 0};
    geometry::point_t p4{11, 2, 0};
    geometry::point_t p5{13, 10, 0};
    geometry::point_t p6{12, 2, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_2) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{5, 5, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_3) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{3, 3, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_4) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{7, 3, 0};
    geometry::point_t p3{3, 7, 0};
    geometry::point_t p4{5, 5, 0};
    geometry::point_t p5{7, 7, 0};
    geometry::point_t p6{9, 1, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_5) {
    geometry::point_t p1{-3, 2, 2};
    geometry::point_t p2{-4, 4.5, 1};
    geometry::point_t p3{-5.5, 4, -1};
    geometry::point_t p4{-5.5, 4, 0};
    geometry::point_t p5{-1, 3, 0};
    geometry::point_t p6{-3.7, -4, 10};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_6) {
    geometry::point_t p1{-5, -7, 0};
    geometry::point_t p2{0, 0, 2};
    geometry::point_t p3{6, 0, 0};
    geometry::point_t p4{0, -8, 0};
    geometry::point_t p5{3, 0, 0};
    geometry::point_t p6{0, 5, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_7) {
    //
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{0, 0, 4};
    geometry::point_t p3{4, 0, 0};

    geometry::point_t p4{8, 9, 0};
    geometry::point_t p5{0, 4, 0};
    geometry::point_t p6{12, 18, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_8) {
    //
    geometry::point_t p1{-5, 3, -4};
    geometry::point_t p2{3, -8, 0};
    geometry::point_t p3{0, 0, 6};
    geometry::point_t p4{0, 9, 0};
    geometry::point_t p5{-8, 0, 0};
    geometry::point_t p6{0, -10, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_9) {
    geometry::point_t p1{-6, 0, 0};
    geometry::point_t p2{0, 0, 3};
    geometry::point_t p3{-9, 7, 4};
    geometry::point_t p4{-3, 0, 1.5};
    geometry::point_t p5{0, 0, 7};
    geometry::point_t p6{3, 0, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_10) {
    geometry::point_t p1{-7, 0, 0};
    geometry::point_t p2{0, -7, 0};
    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{3, 0, 0};
    geometry::point_t p5{0, 3, 0};
    geometry::point_t p6{9, 0, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_11) {
    geometry::point_t p1{-7, 0, 0};
    geometry::point_t p2{0, -7, 0};
    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{3, 0, 9};
    geometry::point_t p5{0, 3, 0};
    geometry::point_t p6{9, 0, 0};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), false);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_12) {
    geometry::point_t p1{-8, 0, 0};
    geometry::point_t p2{0, -9, 0};
    geometry::point_t p3{-3.7, -3.12, 10};
    geometry::point_t p4{-7, -6.37, 0};
    geometry::point_t p5{4.66, -5.92, 0};
    geometry::point_t p6{0, 0, 5};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_13) {
    geometry::point_t p1{-1.88, 1.76, 74.9994};
    geometry::point_t p2{0.32, 0.488, 74.9994};
    geometry::point_t p3{0, -2.144, 74.9994};

    geometry::point_t p4{-0.94, 0.88, 74.9994};
    geometry::point_t p5{0.16, 0.244, 74.9994};
    geometry::point_t p6{0, -1.072, 74.9994};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_14) {
    geometry::point_t p1{-2.824, 3.076, 1.4562};
    geometry::point_t p2{0.056, 0.872, 1.4562};
    geometry::point_t p3{0, -3.348, 1.4562};

    geometry::point_t p4{-1.412, 1.538, 1.4562};
    geometry::point_t p5{0.028, 0.436, 1.4562};
    geometry::point_t p6{0, -1.674, 1.4562};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

TEST(IS_TRIANGLE_INTERSECT_TRIANGLE_TEST, test_15) {
    geometry::point_t p1{-2.824, 3.076, 5.093};
    geometry::point_t p2{0.056, 0.872, 5.093};
    geometry::point_t p3{0, -3.348, 5.093};

    geometry::point_t p4{-1.412, 1.538, 5.093};
    geometry::point_t p5{0.028, 0.436, 5.093};
    geometry::point_t p6{0, -1.674, 5.093};

    geometry::triangle_t t1{p1, p2, p3};
    geometry::triangle_t t2{p4, p5, p6};

    ASSERT_EQ(t1.is_intersect_triangle(t2), true);
}

// LINE INTERSECT PLANE

TEST(IS_LINE_INTERSECT_PLANE, test_1) {
    geometry::point_t p1{0, 0, 0};
    geometry::point_t p2{-3, -4, 3};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{-4, 0, 0};
    geometry::point_t p4{0, -5, 0};
    geometry::point_t p5{0, 0, 4};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);

    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_2) {
    geometry::point_t p1{-2, -5, -1};
    geometry::point_t p2{-6, 5, 6};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{-5, -5, 2};
    geometry::point_t p4{-3, 3, -2};
    geometry::point_t p5{6, -5, 6};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);

    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_3) {
    geometry::point_t p1{0, 0, 3};
    geometry::point_t p2{0, -3, 0};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{-6, 0, 0};
    geometry::point_t p4{0, 0, 7};
    geometry::point_t p5{0, -7, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);

    ASSERT_EQ(intersection.index(), 0);
}

TEST(IS_LINE_INTERSECT_PLANE, test_4) {
    geometry::point_t p1{-3.5046, -5.56986, 3};
    geometry::point_t p2{-3.39954, 1.64817, -1.53242};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{0, 0, 0};
    geometry::point_t p4{-3.5046, -5.56986, 3};
    geometry::point_t p5{-3.39954, 1.64817, -1.53242};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);

    ASSERT_EQ(intersection.index(), 2);
}

TEST(IS_LINE_INTERSECT_PLANE, test_5) {
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{4, 0, 0};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);
    ASSERT_EQ(intersection.index(), 2);
}

TEST(IS_LINE_INTERSECT_PLANE, test_6) {
    geometry::point_t p1{0, -9, 0};
    geometry::point_t p2{0, 0, 4};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);
    ASSERT_EQ(intersection.index(), 1);
}

TEST(IS_LINE_INTERSECT_PLANE, test_7) {
    geometry::point_t p1{0, 0, 4};
    geometry::point_t p2{4, 0, 0};
    geometry::line_t l1{p1, p2};

    geometry::point_t p3{8, 9, 0};
    geometry::point_t p4{0, 4, 0};
    geometry::point_t p5{12, 18, 0};
    geometry::triangle_t t1{p3, p4, p5};

    // std::variant<nullptr_t, point_t, line_t>
    auto intersection = l1.get_intersection_with_plane(t1.plane_);
    ASSERT_EQ(intersection.index(), 1);
}