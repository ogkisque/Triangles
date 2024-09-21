#include <iostream>
#include <cassert>
#include <vector>
#include <set>

#include "geometry.hpp"

namespace
{
    size_t input_triangles(std::vector<geometry::triangle_t> &triangles)
    {
        size_t num_triangles = 0;
        std::cin >> num_triangles;
        assert(std::cin.good());

        for (size_t i = 0; i < num_triangles; i++)
        {
            double x1, x2, x3, y1, y2, y3, z1, z2, z3;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3; 
            assert(std::cin.good());
            geometry::point_t point1{x1, y1, z1};
            geometry::point_t point2{x2, y2, z2};
            geometry::point_t point3{x3, y3, z3};
            geometry::triangle_t triangle{point1, point2, point3, i};

            if (!triangle.is_valid())
            {
                std::cout << "Incorrect data" << std::endl;
                return -1;
            }

            triangles.push_back(triangle);
        }

        return num_triangles;
    }

    void intersect_triangles(std::vector<geometry::triangle_t> &triangles,
                             size_t num_triangles,
                             std::set<size_t> &intersect_triangles_id)
    {
        for (size_t i = 0; i < num_triangles; i++)
        {
            for (size_t j = i; j < num_triangles; j++)
            {
                if (geometry::is_triangle_intersect_triangle(triangles[i], triangles[j]))
                {
                    intersect_triangles_id.insert(triangles[i].id_);
                    intersect_triangles_id.insert(triangles[j].id_);
                }
            }
        }
    }
}


int main()
{
    if(1)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{0, 2, 0};
        geometry::point_t p4{3,-1, 0};

        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == true);
        std::cout << "CORRECT1\n";
    }

    if(2)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{0, 0, 5};
        geometry::point_t p4{4, 1,-3};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == true);
        std::cout << "CORRECT2\n";
    }

    if(3)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{0, 0, 5};
        geometry::point_t p4{2, 0.5, 0};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == true);
        std::cout << "CORRECT3\n";
    }

    if(4)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{-4, -1, 0};
        geometry::point_t p4{8, 2, 0};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == true);
        std::cout << "CORRECT4\n";
    }

    if(5)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{-4, -1, 0};
        geometry::point_t p4{-2, -0.5, 0};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == false);
        std::cout << "CORRECT5\n";
    }

    if(6)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{0, 1, 0};
        geometry::point_t p4{4, 2, 0};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == false);
        std::cout << "CORRECT6\n";
    }

    if(7)
    {
        geometry::point_t p1{0, 0, 0};
        geometry::point_t p2{4, 1, 0};

        geometry::line_t  l1{p1, p2};

        geometry::point_t p3{0, 0, 5};
        geometry::point_t p4{0, 0, 2};
        
        geometry::line_t  l2{p3, p4};

        assert(geometry::is_line_intersect_line(l1, l2) == false);
        std::cout << "CORRECT7\n";
    }
}