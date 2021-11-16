#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct Option
{
    int val;
    bool cond;
    std::string str;
    Option() 
      : val(0), cond(false)
    {
    }
};

int main(int argc, char *argv[])
{
    Option opt;
    po::options_description desc("options");
    desc.add_options()
        ("help,h", "Help")
        ("val,v", po::value<int>(&opt.val)->default_value(0), "Value")
        ("cond,c", "Cond")
        ("str,s", po::value<std::string>(&opt.str), "String")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }

    opt.cond = vm.count("cond");
    std::cout << "val = " << opt.val << std::endl;
    std::cout << "cond = " << opt.cond << std::endl;
    std::cout << "str = " << opt.str << std::endl;

    return 0;
}