#ifndef COMMON_HPP
#define COMMON_HPP
#include <iostream>
#include <iomanip>

//获取数组大小
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//获取数组大小
template<typename T, int N>
constexpr size_t static_array_size(T (&arr)[N]){ return N; }

#define USTD_STATIC_CHECK(expr) static_assert(expr, "USTD_STATIC_CHECK");

//数据快速拷贝，添加静态检查
#define ARRAYCPY(dst, src)\
do\
{\
    USTD_STATIC_CHECK(sizeof(dst) == sizeof(src)); \
    USTD_STATIC_CHECK(sizeof(dst[0]) == sizeof(src[0]));\
    memcpy(dst, src, sizeof(dst));\
} while(0)

//打印可变参数列表
void print() { std::cout << std::endl; }
template<typename T, typename ...Args>
void print(T first, Args... args)
{
    std::cout << first << " ";
    print(args...);
}

template<typename T, size_t N, typename ...Args>
void print(T (&arr)[N], Args... args)
{
    for (const auto& i : arr)
    {
        std::cout << i << " ";
    }
    print(args...);
}

//__FILE__只显示文件名
#if (_WIN32 || _WIN64)
#define FILENAME(x) (strrchr(x, '\\')?strrchr(x, '\\')+1:x)
#else
#define FILENAME(x) (strrchr(x, '/')?strrchr(x, '/')+1:x)
#endif

//宏定义字符拼接
#define TEXT_CONNECTION(a, b) a##b
#define TEXT_CONNECT(a, b) TEXT_CONNECTION(a, b)

class CheckRunTimeGuard
{
public:
    CheckRunTimeGuard(const std::string& msg, const std::string& filename, int line) : msg(msg), filename(filename), line(line), begin_check_run_time(clock()) {}
    ~CheckRunTimeGuard()
    {
        std::cout << "("  << msg << ")" << filename << ":" << line << " " << difftime(clock(), begin_check_run_time) << "ms" << std::endl;
    }

private:
    std::string msg;
    std::string filename;
    int line;
    clock_t begin_check_run_time;
};

//打印执行时间
#ifdef NDEBUG
#define BEGIN_CHECK_RUN_TIME(x) ((void)0)
#define END_CHECK_RUN_TIME(x) ((void)0)
#define END_CHECK_RUN_TIME_MSG(x, msg) ((void)0)
#else
#define BEGIN_CHECK_RUN_TIME(x) clock_t __begin_check_run_time##x = clock(); \
int __begin_check_run_time_line##x = __LINE__

#define END_CHECK_RUN_TIME(x) std::cout << "(" << x << ")" << __FILE__ << ":" << __begin_check_run_time_line##x << "<--->" << __LINE__ << " " << difftime(clock(), __begin_check_run_time##x) << "ms" << std::endl;

#define END_CHECK_RUN_TIME_MSG(x, msg) std::cout << "(" << x << ", " << msg << ")" << __FILE__ << ":" << __begin_check_run_time_line##x << "<--->" << __LINE__ << " " << difftime(clock(), __begin_check_run_time##x) << "ms" << std::endl;

#define CHECK_RUN_TIME_GUARD(msg) CheckRunTimeGuard TEXT_CONNECT(__check_run_time_guard, __LINE__)(msg, __FILE__, __LINE__)
#endif

#endif //COMMON_HPP
