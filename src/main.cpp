#include <cassert>
#include <iostream>
#include <set>
#include <vector>

#include "geometry.hpp"
#include "octotree.hpp"

namespace {

size_t input_num_figs() {
    size_t num_figs = 0;
    std::cin >> num_figs;
    if (!std::cin.good())
        return 0;
    return num_figs;
}

template <typename T = double>
size_t input_figs(const size_t num_figs,
                  std::vector<geometry::figure_t<T>> &figs) {
    for (size_t i = 0; i < num_figs; i++) {
        T x1, x2, x3, y1, y2, y3, z1, z2, z3;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        if (!std::cin.good())
            return 0;

        geometry::point_t<T> point1{x1, y1, z1};
        geometry::point_t<T> point2{x2, y2, z2};
        geometry::point_t<T> point3{x3, y3, z3};

        geometry::figure_t<T> fig =
            geometry::figure_ctor<T>(point1, point2, point3);

        figs.push_back(fig);
    }

    return num_figs;
}
} // namespace

int main() {
    size_t num_figs = input_num_figs();
    if (num_figs == 0) {
        std::cout << "INCORRECT INPUT" << std::endl;
        return 1;
    }

    std::vector<geometry::figure_t<double>> figs{};
    figs.reserve(num_figs);

    if (input_figs<double>(num_figs, figs) == 0) {
        std::cout << "INCORRECT INPUT" << std::endl;
        return 1;
    }

    std::set<size_t> intersect_figs_id;
    octotree::intersect_figs<double>(figs, intersect_figs_id);

    for (size_t id : intersect_figs_id)
        std::cout << id << std::endl;
}