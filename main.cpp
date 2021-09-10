#include <iostream>
#include <sstream>
#include <thread>
#include "Finder\AStar.h"
#include "Finder\Jps.h"

constexpr int width = 50;
constexpr int height = 50;

int main() {
    std::vector<std::vector<int>> terrain = {(const size_t)width, std::vector<int>(height, 1)};
    terrain[3][0] = 0;
    terrain[3][1] = 0;
    terrain[3][2] = 0;
    terrain[3][3] = 0;
    terrain[3][4] = 0;
    terrain[3][5] = 0;
    terrain[4][5] = 0;
    terrain[1][2] = 0;
    terrain[2][2] = 0;

    //地图较大，死寻路时，A*算法效率非常低
    //Pos start({0, 0}), end({height-1, width-1});
    // terrain[width-2][height-2] = 0;
    // terrain[width-2][height-1] = 0;
    // terrain[width-1][height-2] = 0;

    AStar finder({height, width, terrain});
    Pos start({1, 1}), end({height-1, width-1});
    time_t tick1 = clock();
    auto ret = finder.find(start, end);
    time_t tick2 = clock();
    
    Jps finder2({height, width, terrain});
    time_t tick3 = clock();
    auto ret2 = finder2.find(start, end);
    time_t tick4 = clock();

    // std::vector<Pos> showPos;
    // for (auto iter = ret.rbegin(); iter != ret.rend(); ++iter) {
    //     showPos.push_back(*iter);
    //     for (int i = 0; i < height; ++i) {
    //         for (int j = 0; j < width; ++j) {
    //             if (i == start.x() && j == start.y()) {
    //                 std::cout << "  s";
    //                 continue;
    //             }
    //             if (i == end.x() && j == end.y()) {
    //                 std::cout << "  e";
    //                 continue;
    //             }
    //             if (terrain[j][i] == 0) {
    //                 std::cout << "  b";
    //                 continue;
    //             }
    //             bool flag = false;
    //             for (auto &v : showPos) {
    //                 if (i == v.x() && j == v.y()) {
    //                     std::cout << "  x";
    //                     flag = true;
    //                     break;
    //                 }
    //             }
    //             if (flag)
    //                 continue;
    //             std::cout << "  O";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    //     //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }

    std::cout << "AStar: " << difftime(tick2, tick1) << "ms" << std::endl;
    std::cout << "Jps: " << difftime(tick4, tick3) << "ms" << std::endl;
    std::cout << "done." << std::endl;
    return 0;
}