#include <iostream>
#include "common.hpp"

int main()
{
    CHECK_RUN_TIME_GUARD(__FUNCTION__);
    CHECK_RUN_TIME_GUARD(__FUNCTION__);
    BEGIN_CHECK_RUN_TIME(1);

    int a[] = { 1, 2, 3};

    std::cout << "array size by macro: " << ARRAY_SIZE(a) << std::endl;
    std::cout << "array size by template function: " << static_array_size(a) << std::endl;

    print("1", a, 4, "5");

    int b[static_array_size(a)];
    ARRAYCPY(b, a);
    print(b);

    END_CHECK_RUN_TIME(1);
    END_CHECK_RUN_TIME(1);
    END_CHECK_RUN_TIME_MSG(1, "finish");

    return 0;
}