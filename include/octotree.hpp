#include "geometry.hpp"
#include "real_nums.hpp"
#include <list>
#include <map>
#include <set>
#include <vector>

#pragma once

namespace octotree {

class octonode_t;
class octotree_t;

using ListT = typename std::list<std::pair<unsigned, geometry::figure_t>>;
using ListIterT =
    typename std::list<std::pair<unsigned, geometry::figure_t>>::iterator;

const int NUM_CHILDREN = 8;

class octonode_t {
public:
    ListT *figs_;
    ListT *parent_figs_;
    geometry::cube_t cube_;
    const octotree_t &tree_;

    std::array<octonode_t *, NUM_CHILDREN> children_ = {};

    void fill_octonode();

    octonode_t(geometry::cube_t cube, ListT *parent_figs,
               const octotree_t &tree)
        : cube_(cube), parent_figs_(parent_figs), tree_(tree) {
        figs_ = new ListT;
    }
    ~octonode_t() {
        delete figs_;

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++) {
            if (children_[child_num] == nullptr)
                continue;

            delete children_[child_num];
        }
    }

    void fill_figures_in_node() {
        if (parent_figs_ == nullptr)
            return;

        for (ListIterT list_it = parent_figs_->begin();
             list_it != parent_figs_->end(); list_it++) {
            if (geometry::is_fig_in_cube(list_it->second, cube_)) {
                ListIterT temp = list_it;
                list_it--;
                figs_->push_back(*temp);
                parent_figs_->erase(temp);
            }
        }
    }

    void share_cube() {
        double new_cube_size = (cube_.x2_ - cube_.x1_) / 2;

        for (int i = 0; i < NUM_CHILDREN; i++) {
            int mod1 = (i % 2);
            int mod2 = (i + 1) % 2;
            int mod3 = (i / 2) % 2;
            int mod4 = (i / 2 + 1) % 2;
            int mod5 = (i / 4) % 2;
            int mod6 = (i / 4 + 1) % 2;

            geometry::cube_t cube{cube_.x1_ + mod1 * new_cube_size,
                                  cube_.x2_ - mod2 * new_cube_size,
                                  cube_.y1_ + mod3 * new_cube_size,
                                  cube_.y2_ - mod4 * new_cube_size,
                                  cube_.z1_ + mod5 * new_cube_size,
                                  cube_.z2_ - mod6 * new_cube_size};

            children_[i] = new octonode_t{cube, figs_, tree_};
            children_[i]->fill_octonode();
        }
    }

    void intersect(std::set<size_t> &intersect_figs_id) {
        intersection_in_cube(intersect_figs_id);

        if (children_[0] == nullptr)
            return;

        intersect_with_children(intersect_figs_id);

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            children_[child_num]->intersect(intersect_figs_id);
    }

    void intersection_in_cube(std::set<size_t> &intersect_figs_id) {
        for (auto it1 = figs_->begin(); it1 != figs_->end(); it1++) {
            for (auto it2 = std::next(it1); it2 != figs_->end(); it2++) {
                if (geometry::intersect(it1->second, it2->second)) {
                    intersect_figs_id.insert(it1->first);
                    intersect_figs_id.insert(it2->first);
                }
            }
        }
    }

    void intersect_node_with_node(octonode_t &other,
                                  std::set<size_t> &intersect_figs_id) {
        for (auto &&[id1, fig1] : *figs_) {
            for (auto &&[id2, fig2] : *other.figs_) {
                if (geometry::intersect(fig1, fig2)) {
                    intersect_figs_id.insert(id1);
                    intersect_figs_id.insert(id2);
                }
            }
        }
    }

    void intersect_with_subtree(octonode_t &subtree,
                                std::set<size_t> &intersect_figs_id) {
        intersect_node_with_node(subtree, intersect_figs_id);

        if (subtree.children_[0] == nullptr)
            return;

        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            intersect_with_subtree(*(subtree.children_[child_num]),
                                   intersect_figs_id);
    }

    void intersect_with_children(std::set<size_t> &intersect_figs_id) {
        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            intersect_with_subtree(*children_[child_num], intersect_figs_id);
    }
}; // class octonode_t

class octotree_t {
public:
    octonode_t *root_;

    double cube_max_size_;
    double cube_min_size_;
    size_t num_fig_;

    octotree_t(const std::vector<geometry::figure_t> &figs) {
        double max_coord = geometry::get_max_coord(figs);

        geometry::cube_t limit_cube = {-max_coord, max_coord,  -max_coord,
                                       max_coord,  -max_coord, max_coord};

        num_fig_ = figs.size();
        cube_max_size_ = 2 * max_coord;
        cube_min_size_ = cube_max_size_ / num_fig_;

        unsigned id = 0;

        root_ = new octonode_t{limit_cube, nullptr, *this};

        for (geometry::figure_t fig : figs)
            (*root_->figs_).push_back(std::make_pair(id++, fig));
    }

    ~octotree_t() { delete root_; }
}; // class octotree_t

void octonode_t::fill_octonode() {
    fill_figures_in_node();

    if (real_nums::is_less_or_equal_zero(cube_.x2_ - cube_.x1_ -
                                         tree_.cube_min_size_) ||
        figs_->size() < 3) {
        for (size_t child_num = 0; child_num < NUM_CHILDREN; child_num++)
            children_[child_num] = nullptr;

        return;
    }

    share_cube();
}

void intersect_figs(std::vector<geometry::figure_t> &figs,
                    std::set<size_t> &intersect_figs_id) {
    octotree_t tree{figs};
    tree.root_->fill_octonode();
    tree.root_->intersect(intersect_figs_id);
}

} // namespace octotree