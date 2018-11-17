#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try {
        po::options_description desc("General options");
        desc.add_options()
                ("help,H", "Show help")
                ("maps,M", po::value<uint>(), "Set numbers of maps")
                ("reducers,R", po::value<uint>(), "Set numbers of reducers")
                ("file,F", po::value<std::string>(), "Set file name");

        po::positional_options_description pos;
        pos.add("maps", 1);
        pos.add("reducers", 1);
        pos.add("file", 1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
        }


        /*
        std::cout << vm["maps"].as<uint>() << std::endl;
        std::cout << vm["reducers"].as<uint>() << std::endl;
        std::cout << vm["file"].as<std::string>() << std::endl;
         */
    } catch (const std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}