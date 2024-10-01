#include "geometry.hpp"
#include <vector>
#include <array>

#pragma once

namespace octotree {

    class OctoNode
    {
        std::vector<geometry::figure_t> figs;
        geometry::cube_t cube;

        std::array<OctoNode*, 8> childs_;

    };

    class OctoTree
    {
        OctoNode* root_;

        size_t cubes_num;
    };





} // namespace octotree