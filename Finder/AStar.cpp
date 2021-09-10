#include <algorithm>
#include "AStar.h"

void AStar::free_nodelist() {
    for (auto &p : nodeList_) {
        delete p;
    }
}

std::vector<Pos> AStar::find(const Pos &start, const Pos &end) {
    const static Pos offset[8] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},

        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1}
    };

    Node startNode;
    startNode.pos_ = start;
    startNode.g_ = 0;
    openList_.push_back(startNode);

    while (!openList_.empty()) {
        Node curNode = openList_.back();
        openList_.pop_back();
        closeList_[curNode.pos_.y()][curNode.pos_.x()] = 1;

        for (int i = 0; i < 8; i++) {
            Node offsetNode;
            offsetNode.pos_ = { curNode.pos_.x() + offset[i].x(), curNode.pos_.y() + offset[i].y() };
            if (offsetNode.pos_.x() == end.x() && offsetNode.pos_.y() == end.y()) {
                std::vector<Pos> ret;
                ret.push_back(end);
                Node *pNode = &curNode;
                while (pNode != NULL)
                {
                    ret.push_back(pNode->pos_);
                    pNode = pNode->pNode_;
                }
                free_nodelist();
                return ret;
            }
            if (offsetNode.pos_.x() < 0 || offsetNode.pos_.x() >= width_ || offsetNode.pos_.y() < 0 || offsetNode.pos_.y() >= height_)
                continue;
            if (terrain_[offsetNode.pos_.y()][offsetNode.pos_.x()] == 0 || closeList_[offsetNode.pos_.y()][offsetNode.pos_.x()] == 1)
                continue;

            for (auto iter = openList_.begin(); iter != openList_.end(); ++iter) {
                if (iter->pos_ == offsetNode.pos_) {
                    offsetNode.g_ = iter->g_;
                    openList_.erase(iter);
                    break;
                }
            }
            
            int g = curNode.g_ + 1;
            if (g < offsetNode.g_) {
                offsetNode.g_ = g;
                offsetNode.pNode_ = new Node(curNode);
                nodeList_.push_back(offsetNode.pNode_);
                offsetNode.f_ = abs(offsetNode.pos_.x() - end.x()) + abs(offsetNode.pos_.y() - end.y()) + g;
                openList_.push_back(offsetNode);
            }
        };
        std::sort(openList_.begin(), openList_.end());
    }

    free_nodelist();
    return std::vector<Pos>();
}