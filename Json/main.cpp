#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
    std::ifstream fs("../../Json/test.json");
    json conf;
    fs >> conf;

    std::cout << "Int: "  << conf["Int"].get<int>() << std::endl;
    std::cout << "Float: "  << conf["Float"].get<float>() << std::endl;
    std::cout << "String: "  << conf["String"].get<std::string>() << std::endl;
    std::cout << "Boolean: "  << conf["Boolean"].get<bool>() << std::endl;
    for (int i = 0; i < conf["Array"].size(); i++){
        std::cout << "Array[" << i << "]: "  << conf["Array"][i].get<int>() << std::endl;
    }
    for (int i = 0; i < conf["Object"].size(); i++){
        std::string key = "key" + std::to_string(i+1);
        std::cout << "Obj[" << i << "]: "  << conf["Object"][key].get<int>() << std::endl;
    }

    return 0;
}