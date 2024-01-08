#include <iostream>
#include "pugixml.hpp"

int main()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../../Xml/test.xml");
    if (!result)
    {
        return -1;
    }

    for (pugi::xml_node node : doc.child("root"))
    {
        std::cout << node.value() << " " << node.child_value() << std::endl;
    }

    return 0;
}