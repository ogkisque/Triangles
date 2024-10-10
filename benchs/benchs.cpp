#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <time.h>

#include "geometry.hpp"
#include "octotree.hpp"
#include "hayai.hpp"
#include "hayai_main.hpp"

namespace
{
    std::vector<geometry::figure_t> FIGS;
    size_t NUM_FIGS;

    double get_random(double min, double max)
    {
        const long max_rand = 1000000L;
        return min + (max - min) * (random() % max_rand) / max_rand;
    }
    
    size_t get_figs1(std::vector<geometry::figure_t> &figs)
    {
        size_t num_figs = 0;
        std::ifstream in("benchs/data.dat");
        assert(in.is_open());

        double x1, x2, x3, y1, y2, y3, z1, z2, z3;
        in >> num_figs;
        while (in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3)
        {
            geometry::point_t point1{x1, y1, z1};
            geometry::point_t point2{x2, y2, z2};
            geometry::point_t point3{x3, y3, z3};

            geometry::figure_t fig = geometry::figure_ctor(point1, point2, point3);
            figs.push_back(fig);
        }

        return num_figs;
    }

    size_t get_figs(std::vector<geometry::figure_t> &figs)
    {
        double x1, x2, x3, y1, y2, y3, z1, z2, z3;
        size_t num_figs = 10000;
        
        for (int i = 0; i < num_figs; i++)
        {
            x1 = get_random(-100, 100);
            y1 = get_random(-100, 100);
            z1 = get_random(-100, 100);
            
            x2 = x1 + get_random(-2, 2);
            y2 = y1 + get_random(-2, 2);
            z2 = z1 + get_random(-2, 2);
            
            x3 = x1 + get_random(-2, 2);
            y3 = y1 + get_random(-2, 2);
            z3 = z1 + get_random(-2, 2);

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
            for (size_t j = i + 1; j < num_figs; j++)
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

BENCHMARK(IntersectBenchs, BenchOctotree, 1, 1)
{
    std::set<size_t> intersect_figs_id;
    octotree::intersect_figs(FIGS, intersect_figs_id);
}

BENCHMARK(IntersectBenchs, BenchDefault, 1, 1)
{
    std::set<size_t> intersect_figs_id;
    intersect_figs(FIGS, NUM_FIGS, intersect_figs_id);
}

int main()
{
    srandom(time(NULL));
    NUM_FIGS = get_figs(FIGS);
    hayai::MainRunner runner;
    return runner.Run();
}