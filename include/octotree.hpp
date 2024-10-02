#include "geometry.hpp"
#include "real_nums.hpp"
#include <vector>
#include <list>
#include <map>

#pragma once

namespace octotree {

    using ListT = typename std::list<std::pair<unsigned, geometry::figure_t>>;
    using ListIterT = typename std::list<std::pair<unsigned, geometry::figure_t>>::iterator;

    const int NUM_CHILDS = 8;

    class OctoNode
    {
    public:
        ListT* figs_;
        ListT* parent_figs_;
        geometry::cube_t cube_;
        double min_cube_size_;

        std::array<OctoNode*, NUM_CHILDS> childs_;

        OctoNode(geometry::cube_t cube, ListT* parent_figs, double min_cube_size);
    };

    class OctoTree
    {
    public:
        OctoNode* root_;
        
        OctoTree(const std::vector<geometry::figure_t> &figs, unsigned num_figs);
    };

    void distribute_figures(OctoNode &node);


} // namespace octotree