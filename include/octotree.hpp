#include "geometry.hpp"
#include "real_nums.hpp"
#include <vector>
#include <list>
#include <map>
#include <set>

#pragma once

namespace octotree {

    class octonode_t;
    class octotree_t;

    using ListT     = typename std::list<std::pair<unsigned, geometry::figure_t>>;
    using ListIterT = typename std::list<std::pair<unsigned, geometry::figure_t>>::iterator;

    const int NUM_CHILDREN = 8;

    class octonode_t
    {
    public:
        ListT* figs_;
        ListT* parent_figs_;
        geometry::cube_t cube_;
        const octotree_t &tree_;

        std::array<octonode_t*, NUM_CHILDREN> children_;

        octonode_t(geometry::cube_t cube, ListT *parent_figs, const octotree_t& tree);
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


    void intersect(octonode_t &node, std::set<size_t> &intersect_figs_id);
    void intersect_figs(std::vector<geometry::figure_t> &figs, std::set<size_t> &intersect_figs_id);
    void intersection_in_cube(octonode_t &node, std::set<size_t> &intersect_figs_id);
    void intersect_node_with_node(octonode_t &node, octonode_t &other, std::set<size_t> &intersect_figs_id);
    void intersect_with_subtree(octonode_t &node, octonode_t &subtree, std::set<size_t> &intersect_figs_id);
    void intersect_with_children(octonode_t &node, std::set<size_t> &intersect_figs_id);

} // namespace octotree