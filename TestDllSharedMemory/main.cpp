#include <iostream>
#include <string>
#include "SharedDll.h"

int main()
{
    std::string cmd;
    std::cin >> cmd;
    while (cmd != "quit")
    {
        if (cmd == "get")
        {
            std::cout << GetValueString() << std::endl;
        } else if (cmd == "set")
        {
            char data[1024] = "";
            std::cin >> data;
            SetValueString(data);
        }

        std::cin >> cmd;
    }

    return 0;
}