#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <future>
#include <algorithm>

#include "FileReaders.h"
#include "Map.h"
#include "Reduce.h"

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
            return 0;
        }

        auto mnum = vm["maps"].as<uint>();
        auto rnum = vm["reducers"].as<uint>();
        const auto filename = vm["file"].as<std::string>();

        std::ifstream file(filename, std::ios_base::binary);
        if (!file.is_open()) {
            throw std::logic_error("File is not exist");
        }

        auto partition_positions = split_file(std::move(file),mnum);
        std::vector<std::future<Map::partitions_type>> map_results;
        map_results.reserve(partition_positions.size());

        for (const auto & positions_pair : partition_positions) {
            map_results.push_back(std::async(std::launch::async, [&filename,rnum] (auto start_pos, auto end_pos) {
                Map map;
                read_partition(map,std::ifstream(filename, std::ios_base::binary),start_pos, end_pos);
                return map.split(rnum);
            }, positions_pair.first, positions_pair.second));
        }

        std::vector<Map::partitions_type> data_to_reduce(rnum);

        for (auto && result : map_results) {
            size_t index = 0;
            for (auto && part : result.get()) {
                data_to_reduce[index].push_back(std::move(part));
                index++;
            }
        }

        std::vector<std::future<Reduce::result_type>> reduce_results;
        reduce_results.reserve(rnum);

        for (auto && part : data_to_reduce) {
            reduce_results.push_back(std::async(std::launch::async, [] (auto data) {
                Reduce reduce;
                for (auto && mp : data) {
                    for (auto && pair : mp) {
                        reduce.push(std::move(pair.second));
                    }
                }
                return reduce.process();
            }, std::move(part)));
        }

        assert(reduce_results.size() == rnum);

        auto max = 0;
        for (auto & result : reduce_results) {
            auto c_result = result.get();
            if (c_result > max) {
                max = c_result;
            }
        }

        std::cout << max << std::endl;

    } catch (const std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}