#ifndef PUBLIC_STRUCT_H
#define PUBLIC_STRUCT_H

#include <climits>

struct Pos{
    Pos(int x = 0, int y = 0) : x_(x), y_(y) {}

    bool operator==(const Pos &pos) {
        return (x_ == pos.x_) && (y_ == pos.y_);
    }

    Pos& operator=(const Pos &pos) {
        x_ = pos.x_;
        y_ = pos.y_;
        return *this;
    }

    int x() const { return x_; }
    int y() const { return y_; }

    int x_;
    int y_;
};

struct Node{
    Node() : f_(0), g_(INT_MAX), pNode_(NULL) {}
    bool operator<(const Node &other) {
        return f_ > other.f_;
    }

    int f_;
    int g_;
    Pos pos_;
    Node *pNode_;
};

#endif