#include <ctime>
#include <cassert>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include <functional>
#include <vector>
#include <string>
#include <iomanip>
#include "concurrent_queue.h"

std::atomic_int count = 0;
std::deque<int> dq;
std::mutex lock;
void test1(int kRun)
{
    //producer
    auto t1 = std::thread([kRun](){
        for (int i = 0; i < kRun; i ++)
        {
            std::lock_guard<std::mutex> guard(lock);
            dq.push_back(i);
        }
    });

    //consumer
    std::thread ts[4];
    for (int i = 0; i < 4; i++)
    {
        ts[i] = std::thread([kRun]{
            while(count != kRun)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                if (!dq.empty())
                {
                    std::lock_guard<std::mutex> guard(lock);
                    if (!dq.empty())
                    {
                        dq.pop_front();
                        ++count;
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                }
            }
        });
    }
    t1.join();
    for (int i = 0; i < 4; i++)
    {
        ts[i].join();
    }
}

Concurrency::concurrent_queue<int> cq;
void test2(int kRun)
{
    //producer
    auto t1 = std::thread([kRun](){
        for (int i = 0; i < kRun; i ++)
        {
            cq.push(i);
        }
    });

    //consumer
    std::thread ts[4];
    for (int i = 0; i < 4; i++)
    {
        ts[i] = std::thread([kRun]{
            int item;
            while(count != kRun)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                if (cq.try_pop(item))
                {
                    ++count;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        });
    }
    t1.join();
    for (int i = 0; i < 4; i++)
    {
        ts[i].join();
    }
}

double test(std::function<void(int)> f, int kRun)
{
    count = 0;
    time_t s = clock();
    f(kRun);
    assert(count == kRun);
    return difftime(clock(), s);
}

/*
data: defined operator<< 
*/
template<typename T>
void printVec(std::vector<T> data, int w)
{
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << std::setw(w) << data[i];
    }
}

template<typename T>
void printTable(std::vector<std::string> header, std::vector<std::vector<T>> data, int w)
{
    int hw = 0;
    for (const auto &v : header)
    {
        hw = hw > v.size() ? hw : v.size();
    }
    int size = std::max(header.size(), data.size());
    std::cout << std::setiosflags(std::ios::left);
    for (int i = 0; i < size; i++)
    {
        std::string str = { (header.size() > i) ? header[i] : "" };
        std::cout << std::setw(hw) << str  << " ";
        if (data.size() > i)
        {
            printVec(data[i], w);
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::string> header = {"count", "lock queue", "concurrent queue"};
    std::vector<int> data1 = {1, 10, 100, 200}, data2, data3;
    for (int n : data1)
    {
        data2.push_back(test(test1, n));
        data3.push_back(test(test2, n));
    }
    std::vector<std::vector<int>> data = {data1, data2, data3};
    printTable(header, data, 5);
    return 0;
}