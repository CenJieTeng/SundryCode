#include <ctime>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include "concurrent_queue.h"

std::atomic_int count = 0;
const int kRun = 100;

std::deque<int> dq;
std::mutex lock;
void test1()
{
    //producer
    auto t1 = std::thread([](){
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
        ts[i] = std::thread([]{
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
void test2()
{
    //producer
    auto t1 = std::thread([](){
        for (int i = 0; i < kRun; i ++)
        {
            cq.push(i);
        }
    });

    //consumer
    std::thread ts[4];
    for (int i = 0; i < 4; i++)
    {
        ts[i] = std::thread([]{
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

void test(void(*f)(), const char *str)
{
    count = 0;
    time_t s = clock();
    f();
    std::cout << str << difftime(clock(), s) << "ms" << std::endl;
    std::cout << count << std::endl;
}

int main()
{
    
    test(test1, "test1: ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    test(test2, "test2: ");

    return 0;
}