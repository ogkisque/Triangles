#include "octotree.hpp"
#include "geometry.hpp"

namespace octotree
{

    octotree_t::octotree_t(const std::vector<geometry::figure_t> &figs)
    {
        double max_coord = geometry::get_max_coord(figs);

        geometry::cube_t limit_cube = {-max_coord, max_coord, -max_coord, max_coord, -max_coord, max_coord};

        num_fig_ = figs.size();
        cube_max_size_ = 2 * max_coord;
        cube_min_size_ = cube_max_size_ / num_fig_;

        ListT* figs_list = new ListT;
        unsigned id = 0;
        
        for (geometry::figure_t fig : figs)
            (*figs_list).push_back(std::make_pair(id++, fig));

        root_ = new octonode_t{limit_cube, figs_list, *this};
    }

    octotree_t::~octotree_t()
    {
        octonode_t* current = root_;
        ///TODO: we need do delete tree with loop
        
        // std::array<octonode_t*> all_nodes;

        // while (current)
        // {
        //     for (size_t i = 0; i < NUM_CHILDS; i++)
        //         all_nodes.push_back(node.childs_[i])

        //     current......
        // }

    }

    octonode_t::octonode_t(geometry::cube_t cube, ListT* parent_figs, const octotree_t& tree) : 
                       cube_(cube), parent_figs_(parent_figs), tree_(tree)
    {
        figs_ = new ListT;
    }

    octonode_t::~octonode_t()
    {
        delete figs_;
    }

    void fill_octonode(octonode_t &node)
    {
        fill_figures_in_node(node);

        if (real_nums::is_less_or_equal_zero(node.cube_.x2_ - node.cube_.x1_ - node.tree_.cube_min_size_) ||
            node.figs_->size() < 3)
            return;
            
        share_cube(node);
    }

    void fill_figures_in_node(octonode_t &node)
    {
        if (!node.parent_figs_)
            return;

        for (ListIterT list_it = node.parent_figs_->begin(); list_it != node.parent_figs_->end(); list_it++)
        {
            if (geometry::is_fig_in_cube(list_it->second, node.cube_))
            {
                node.figs_->push_back(*list_it);
                node.parent_figs_->erase(list_it);
            }
        }
    }

    void share_cube(octonode_t &node)
    {
        double new_cube_size = (node.cube_.x2_ - node.cube_.x1_) / 2;

        for (int i = 0; i < NUM_CHILDREN; i++)
        {
            int mod1 = (i % 2);
            int mod2 = (i + 1) % 2;
            int mod3 = (i / 2) % 2;
            int mod4 = (i / 2 + 1) % 2;
            int mod5 = (i / 4) % 2;
            int mod6 = (i / 4 + 1) % 2;

            geometry::cube_t cube{node.cube_.x1_ + mod1 * new_cube_size,
                                  node.cube_.x2_ - mod2 * new_cube_size,
                                  node.cube_.y1_ + mod3 * new_cube_size,
                                  node.cube_.y2_ - mod4 * new_cube_size,
                                  node.cube_.z1_ + mod5 * new_cube_size,
                                  node.cube_.z2_ - mod6 * new_cube_size};

            node.children_[i] = new octonode_t{cube, node.figs_, node.tree_};

            fill_octonode(*node.children_[i]);
        }
    }


    void intersect_figs(std::vector<geometry::figure_t> &figs, std::set<size_t> &intersect_figs_id)
    {
        octotree_t tree{figs};
        fill_octonode(*(tree.root_)); // may be ref

        intersect(*(tree.root_), intersect_figs_id);
    }

    void intersect(octonode_t &node, std::set<size_t> &intersect_figs_id) 
    {
        intersection_in_cube(node, intersect_figs_id);
        intersect_with_children(node, intersect_figs_id);

        if (node.children_.size() == 0)
            return;

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            intersect(*(node.children_[child_num]), intersect_figs_id);
    }

    void intersection_in_cube(octonode_t &node, std::set<size_t> &intersect_figs_id)
    {
        for (auto it1 = node.figs_->begin(); it1 != node.figs_->end(); it1++)
        {
            for (auto it2 = std::next(it1); it2 != node.figs_->end(); it2++)
            {
                if (geometry::intersect(it1->second, it2->second))
                {
                    intersect_figs_id.insert(it1->first);
                    intersect_figs_id.insert(it2->first);
                }
            }
        }
    }

    void intersect_node_with_node(octonode_t &node, octonode_t &other, std::set<size_t> &intersect_figs_id)
    {
        for (auto node_it = node.figs_->begin(); node_it != node.figs_->end(); node_it++)
        {
            for (auto other_it = other.figs_->begin(); other_it != other.figs_->end(); other_it++)
            {
                if (geometry::intersect(node_it->second, other_it->second))
                {
                    intersect_figs_id.insert(node_it->first);
                    intersect_figs_id.insert(other_it->first);
                }
            }
        }
    }

    void intersect_with_subtree(octonode_t &node, octonode_t &subtree, std::set<size_t> &intersect_figs_id)
    {
        intersect_node_with_node(node, subtree, intersect_figs_id);

        if (subtree.children_.size() == 0)
            return;

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            intersect_with_subtree(node, *(subtree.children_[child_num]), intersect_figs_id);
    }

    void intersect_with_children(octonode_t &node, std::set<size_t> &intersect_figs_id)
    {
        if (node.children_.size() == 0)
            return;

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            intersect_with_subtree(node, *(node.children_[child_num]), intersect_figs_id);
    }

} // namespace octotree


// // fill octonodes
// void distribute_figures(octonode_t &node)
// {
//     // fill figure in node
//     for (auto list_pair : node.parent_figs_)
//     {
//         if (geometry::is_fig_in_cube(list_pair->second, node.cube_))
//         {
//             node.figs_->push_back(*list_pair);
//             node.parent_figs_->erase(list_pair);
//         }
//     }

//     if (real_nums::is_less_or_equal_zero(node.cube_.x2_ - node.cube_.x1_ - node.min_cube_size_) ||
//         node.figs_->size() < 3)
//         return;

//     // distribute figures
//     double new_cube_size = (node.cube_.x2_ - node.cube_.x1_) / 2;

//     for (int i = 0; i < NUM_CHILDS; i++)
//     {
//         int mod1 = (i % 2);
//         int mod2 = (i + 1) % 2;
//         int mod3 = (i / 2) % 2;
//         int mod4 = (i / 2 + 1) % 2;
//         int mod5 = (i / 4) % 2;
//         int mod6 = (i / 4 + 1) % 2;

//         geometry::cube_t cube{node.cube_.x1_ + mod1 * new_cube_size,
//                               node.cube_.x2_ - mod2 * new_cube_size,
//                               node.cube_.y1_ + mod3 * new_cube_size,
//                               node.cube_.y2_ - mod4 * new_cube_size,
//                               node.cube_.z1_ + mod5 * new_cube_size,
//                               node.cube_.z2_ - mod6 * new_cube_size};

//         node.childs_[i] = new octonode_t{cube, node.figs_, node.min_cube_size_};

//         distribute_figures(*node.childs_[i]);
//     }
// }