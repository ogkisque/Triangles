#include "octotree.hpp"

namespace octotree
{

    OctoTree::OctoTree(const std::vector<geometry::figure_t> &figs, unsigned num_figs)
    {
        geometry::cube_t limit_cube = geometry::get_limit_cube(figs[0]);
        double x_min = limit_cube.x1_;
        double x_max = limit_cube.x2_;
        double y_min = limit_cube.y1_;
        double y_max = limit_cube.y2_;
        double z_min = limit_cube.z1_;
        double z_max = limit_cube.z2_;

        for (geometry::figure_t fig : figs)
        {
            geometry::cube_t limit_cube = geometry::get_limit_cube(fig);
            x_min = real_nums::min2(x_min, limit_cube.x1_);
            x_max = real_nums::max2(x_min, limit_cube.x2_);
            y_min = real_nums::min2(x_min, limit_cube.y1_);
            y_max = real_nums::max2(x_min, limit_cube.y2_);
            z_min = real_nums::min2(x_min, limit_cube.z1_);
            z_max = real_nums::max2(x_min, limit_cube.z2_);
        }

        double max_size = real_nums::max3(x_max - x_min, y_max - y_min, z_max - z_min);
        double max_size_half = max_size / 2;
        if (max_size != x_max - x_min)
        {
            x_min -= max_size_half;
            x_max += max_size_half;
        }
        if (max_size != y_max - y_min)
        {
            y_min -= max_size_half;
            y_max += max_size_half;
        }
        if (max_size != z_max - z_min)
        {
            z_min -= max_size_half;
            z_max += max_size_half;
        }

        limit_cube = {x_min, x_max, y_min, y_max, z_min, z_max};

        ListT* figs_list = new ListT;
        unsigned id = 0;
        for (geometry::figure_t fig : figs)
        {
            (*figs_list).push_back(std::make_pair(id, fig));
            id++;
        }

        root_ = new OctoNode{limit_cube, figs_list, max_size / num_figs};
    }

    OctoNode::OctoNode(geometry::cube_t cube, ListT* parent_figs, double min_cube_size) : 
                       cube_(cube), parent_figs_(parent_figs), min_cube_size_(min_cube_size)
    {
        figs_ = new ListT;
    }

    void distribute_figures(OctoNode &node)
    {
        for (ListIterT fig = node.parent_figs_->begin(); fig != node.parent_figs_->end(); fig++)
        {
            if (geometry::is_fig_in_cube(fig->second, node.cube_))
            {
                node.figs_->push_back(*fig);
                node.parent_figs_->erase(fig);
            }
        }

        if (real_nums::is_less_or_equal_zero(node.cube_.x2_ - node.cube_.x1_ - node.min_cube_size_) ||
            node.figs_->size() < 3)
            return;

        double cube_size_half = (node.cube_.x2_ - node.cube_.x1_) / 2;

        for (int i = 0; i < NUM_CHILDS; i++)
        {
            int mod1 = i % 2;
            int mod2 = (i + 1) % 2;
            int mod3 = i / 2 % 2;
            int mod4 = (i + 1) / 2 % 2;
            int mod5 = i / 4 % 2;
            int mod6 = (i + 1) / 4 % 2;

            geometry::cube_t cube{node.cube_.x1_ + mod1 * cube_size_half,
                                  node.cube_.x2_ - mod2 * cube_size_half,
                                  node.cube_.y1_ + mod3 * cube_size_half,
                                  node.cube_.y2_ - mod4 * cube_size_half,
                                  node.cube_.z1_ + mod5 * cube_size_half,
                                  node.cube_.z2_ - mod6 * cube_size_half};
            node.childs_[i] = new OctoNode{cube, node.figs_, node.min_cube_size_};

            distribute_figures(*node.childs_[i]);
        }
    }

} // namespace octotree

