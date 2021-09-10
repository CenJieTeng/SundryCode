#include <algorithm>
#include "Jps.h"

void Jps::free_nodelist() {
    for (auto &p : nodeList_) {
        delete p;
    }
}

bool Jps::have_compel_neigbor(const Pos &pos, const Pos &dir) {
    if (dir.x() != 0 || dir.y() != 0) {
        if (dir.x() == 0) {
            int offsetY = dir.y() > 0 ? 1 : -1;
            Pos pa1 = {pos.x() + 1, pos.y()};
            Pos pa2 = {pos.x() + 1, pos.y() + offsetY};
            if (pa1.x() >= 0 && pa1.x() < width_ && pa1.y() >= 0 && pa1.y() < height_) {
                if (pa2.x() >= 0 && pa2.x() < width_ && pa2.y() >= 0 && pa2.y() < height_) {
                    if (terrain_[pa1.y()][pa1.x()] == 0 && terrain_[pa2.y()][pa2.x()] == 1)
                        return true;
                }
            }
            Pos pb1 = {pos.x() - 1, pos.y()};
            Pos pb2 = {pos.x() - 1, pos.y() + offsetY};
            if (pb1.x() >= 0 && pb1.x() < width_ && pb1.y() >= 0 && pb1.y() < height_) {
                if (pb2.x() >= 0 && pb2.x() < width_ && pb2.y() >= 0 && pb2.y() < height_) {
                    if (terrain_[pb1.y()][pb1.x()] == 0 && terrain_[pb2.y()][pb2.x()] == 1)
                        return true;
                }
            }
        } else if (dir.y() == 0) {
            int offsetX = dir.x() > 0 ? 1 : -1;
            Pos pa1 = {pos.x(), pos.y() + 1};
            Pos pa2 = {pos.x() + offsetX, pos.y() + 1};
            if (pa1.x() >= 0 && pa1.x() < width_ && pa1.y() >= 0 && pa1.y() < height_) {
                if (pa2.x() >= 0 && pa2.x() < width_ && pa2.y() >= 0 && pa2.y() < height_) {
                    if (terrain_[pa1.y()][pa1.x()] == 0 && terrain_[pa2.y()][pa2.x()] == 1)
                        return true;
                }
            }
            Pos pb1 = {pos.x(), pos.y() - 1};
            Pos pb2 = {pos.x() + offsetX, pos.y() - 1};
            if (pb1.x() >= 0 && pb1.x() < width_ && pb1.y() >= 0 && pb1.y() < height_) {
                if (pb2.x() >= 0 && pb2.x() < width_ && pb2.y() >= 0 && pb2.y() < height_) {
                    if (terrain_[pb1.y()][pb1.x()] == 0 && terrain_[pb2.y()][pb2.x()] == 1)
                        return true;
                }
            }
        } else {
            int offsetX = dir.x() > 0 ? 1 : -1;
            Pos pa1 = {pos.x() - dir.x() + offsetX, pos.y() - dir.y()};
            Pos pa2 = {pa1.x() + offsetX, pos.y()};
            if (pa1.x() >= 0 && pa1.x() < width_ && pa1.y() >= 0 && pa1.y() < height_) {
                if (pa2.x() >= 0 && pa2.x() < width_ && pa2.y() >= 0 && pa2.y() < height_) {
                    if (terrain_[pa1.y()][pa1.x()] == 0 && terrain_[pa2.y()][pa2.x()] == 1)
                        return true;
                }
            }
            int offsetY = dir.y() > 0 ? 1 : -1;
            Pos pb1 = {pos.x() - dir.x(), pos.y() - dir.y() + offsetY};
            Pos pb2 = {pb1.x(), pos.y() + offsetY};
            if (pb1.x() >= 0 && pb1.x() < width_ && pb1.y() >= 0 && pb1.y() < height_) {
                if (pb2.x() >= 0 && pb2.x() < width_ && pb2.y() >= 0 && pb2.y() < height_) {
                    if (terrain_[pb1.y()][pb1.x()] == 0 && terrain_[pb2.y()][pb2.x()] == 1)
                        return true;
                }
            }
        }
    }
    return false;
}

std::vector<Pos> Jps::find(const Pos &start, const Pos &end) {
    const static Pos offsetL[4] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
    };
    const static Pos offsetS[5] = {
        {0, 0},
        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1}
    };

    Node startNode;
    startNode.pos_ = start;
    startNode.g_ = 0;
    openList_.push_back(startNode);

    std::vector<Pos> ret;
    while (!openList_.empty()) {
        Node curNode = openList_.back();
        openList_.pop_back();
        closeList_[curNode.pos_.y()][curNode.pos_.x()] = 1;

        for (int i = 0; i < 5; i++) {
            Pos dir = offsetS[i];
            if (dir == Pos{0, 0}) {
                for (int j = 0; j < 4; j++) {
                    Pos offsetPos(curNode.pos_);
                    while (1){
                        offsetPos = {offsetPos.x() + offsetL[j].x(), offsetPos.y() + offsetL[j].y()};
                        if (offsetPos.x() < 0 || offsetPos.x() >= width_ || offsetPos.y() < 0 || offsetPos.y() >= height_)
                            break;
                        if (terrain_[offsetPos.y()][offsetPos.x()] == 0 || closeList_[offsetPos.y()][offsetPos.x()] == 1)
                            break;
                        closeList_[offsetPos.y()][offsetPos.x()] = 1;

                        if (offsetPos.x() == end.x() && offsetPos.y() == end.y()) {
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

                        if (have_compel_neigbor(offsetPos, offsetL[j])) {
                            Node *pNode = new Node;
                            nodeList_.push_back(pNode);
                            pNode->pos_ = curNode.pos_;

                            Node node;
                            node.pos_ = offsetPos;
                            node.pNode_ = pNode;
                            openList_.push_back(node);
                        }
                    }
                }
            } else {
                Pos offsetPos(curNode.pos_);
                while (1) {
                    offsetPos = {offsetPos.x() + dir.x(), offsetPos.y() + dir.y()};
                    if (offsetPos.x() < 0 || offsetPos.x() >= width_ || offsetPos.y() < 0 || offsetPos.y() >= height_)
                        break;
                    if (terrain_[offsetPos.y()][offsetPos.x()] == 0 || closeList_[offsetPos.y()][offsetPos.x()] == 1)
                        break;

                    if (offsetPos.x() == end.x() && offsetPos.y() == end.y()) {
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

                    if (have_compel_neigbor(offsetPos, dir)) {
                        Node *pNode = new Node;
                        pNode->pos_ = curNode.pos_;
                        pNode->pNode_ = new Node(curNode);

                        Node node;
                        node.pos_ = offsetPos;
                        node.pNode_ = pNode;
                        openList_.push_back(node);
                    }

                    for (int j = 0; j < 2; j++) {
                        Pos offsetPos1 = offsetPos;
                        Pos dir1 = j == 0 ? Pos{0, dir.y()} : Pos{dir.x(), 0};
                        
                        while (1){
                            offsetPos1 = {offsetPos1.x() + dir1.x(), offsetPos1.y() + dir1.y()};
                            if (offsetPos1.x() < 0 || offsetPos1.x() >= width_ || offsetPos1.y() < 0 || offsetPos1.y() >= height_)
                                break;
                            if (terrain_[offsetPos1.y()][offsetPos1.x()] == 0 || closeList_[offsetPos1.y()][offsetPos1.x()] == 1)
                                break;
                            closeList_[offsetPos1.y()][offsetPos1.x()] = 1;

                            if (offsetPos1.x() == end.x() && offsetPos1.y() == end.y()) {
                                std::vector<Pos> ret;
                                ret.push_back(end);
                                ret.push_back(offsetPos);
                                Node *pNode = &curNode;
                                while (pNode != NULL)
                                {
                                    ret.push_back(pNode->pos_);
                                    pNode = pNode->pNode_;
                                }
                                free_nodelist();
                                return ret;
                            }

                            if (have_compel_neigbor(offsetPos1, dir1)) {
                                Node *pNode = new Node;
                                pNode->pos_ = offsetPos;
                                pNode->pNode_ = new Node(curNode);

                                Node node;
                                node.pos_ = offsetPos1;
                                node.pNode_ = pNode;
                                openList_.push_back(node);
                            }
                        }
                    }
                }
            }
        }
        std::sort(openList_.begin(), openList_.end());
    }

    free_nodelist();
    return std::vector<Pos>();
}