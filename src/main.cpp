#include <iostream>
#include <cassert>
#include <vector>
#include <set>

#include "geometry.hpp"

namespace
{
    size_t input_figs(std::vector<geometry::figure_t> &figs)
    {
        size_t num_figs = 0;
        std::cin >> num_figs;
        assert(std::cin.good());

        for (size_t i = 0; i < num_figs; i++)
        {
            double x1, x2, x3, y1, y2, y3, z1, z2, z3;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3; 
            assert(std::cin.good());
            geometry::point_t point1{x1, y1, z1};
            geometry::point_t point2{x2, y2, z2};
            geometry::point_t point3{x3, y3, z3};
            
            geometry::figure_t fig = geometry::figure_ctor(point1, point2, point3);

            figs.push_back(fig);
        }

        return num_figs;
    }

    void intersect_figs(std::vector<geometry::figure_t> &figs,
                        size_t num_figs,
                        std::set<size_t> &intersect_figs_id)
    {
        for (size_t i = 0; i < num_figs; i++)
        {
            for (size_t j = i; j < num_figs; j++)
            {
                if (geometry::intersect(figs[i], figs[j]))
                {
                    intersect_figs_id.insert(i);
                    intersect_figs_id.insert(j);
                }
            }
        }
    }
}

int main()
{
    std::vector<geometry::figure_t> figs;
    size_t num_figs = input_figs(figs);

    std::set<size_t> intersect_figs_id;
    intersect_figs(figs, num_figs, intersect_figs_id);

    for (size_t id : intersect_figs_id)
        std::cout << id << std::endl;
}