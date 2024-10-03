#include "geometry.hpp"
#include "real_nums.hpp"
#include <vector>
#include <list>
#include <map>

#pragma once




namespace octotree {

    class octonode_t;
    class octotree_t;

    using ListT     = typename std::list<std::pair<unsigned, geometry::figure_t>>;
    using ListIterT = typename std::list<std::pair<unsigned, geometry::figure_t>>::iterator;

    const int NUM_CHILDS = 8;

    class octonode_t
    {
    public:
        ListT* figs_;
        ListT* parent_figs_;
        geometry::cube_t cube_;
        const octotree_t& tree_;

        std::array<octonode_t*, NUM_CHILDS> childs_;

        octonode_t(geometry::cube_t cube, ListT* parent_figs, const octotree_t& tree);
        ~octonode_t();
    };

    class octotree_t
    {
    public:
        octonode_t* root_;

        double cube_max_size_;
        double cube_min_size_;
        size_t num_fig_;
        
        // const std::vector<geometry::figure_t> &figs;
        // min_cube
        octotree_t(const std::vector<geometry::figure_t> &figs);
        ~octotree_t();
    };

    void fill_octonode(octonode_t &node);
    void fill_figures_in_node(octonode_t &node);
    void share_cube(octonode_t &node);

} // namespace octotree