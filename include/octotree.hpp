#include "geometry.hpp"
#include <vector>
#include <list>
#include <map>

#pragma once

namespace octotree {

    class OctoNode
    {
        std::map<unsigned, geometry::figure_t> figs_;
        geometry::cube_t cube_;

        std::array<OctoNode*, 8> childs_;
        OctoNode* parent_;

        OctoNode(std::map<unsigned, geometry::figure_t> &figs,
                 double x1, double x2, double y1, double y2, double z1, double z2);
    };

    class OctoTree
    {
        OctoNode* root_;

        OctoTree(const std::vector<geometry::figure_t> &figs, unsigned num_figs);
    };





} // namespace octotree