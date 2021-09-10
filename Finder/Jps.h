#ifndef JPS_H
#define JPS_H

#include <vector>
#include "PublicStruct.h"

class Jps {
public:
    Jps(int width, int height, const std::vector<std::vector<int>> &terrain) : width_(width), height_(height), terrain_(terrain) {
        closeList_ = {(const size_t)height_, std::vector<int>(width, 0)};
    }
    std::vector<Pos> find(const Pos &start, const Pos &end);

private:
    void free_nodelist();
    bool have_compel_neigbor(const Pos &pos, const Pos &dir);

private:
    int width_;
    int height_;
    std::vector<std::vector<int>> terrain_;

    std::vector<Node> openList_;
    std::vector<std::vector<int>> closeList_;
    std::vector<Node*> nodeList_;
};

#endif