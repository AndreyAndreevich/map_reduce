//
// Created by Андрей Лукин on 27.10.2018.
//

#ifndef MAP_REDUCE_HELPERS_H
#define MAP_REDUCE_HELPERS_H

#include <istream>
#include <vector>
#include <exception>

std::vector<std::ios::streamoff> split_file(std::istream&& in, const uint partitions_count) {
    std::vector<std::ios::streamoff> positions;

    in.seekg(0, std::ios::end);
    std::ios::streamoff file_size = in.tellg();
    if (file_size <= 0) {
        throw std::logic_error("File is empty");
    }

    if (partitions_count == 0) {
        throw std::logic_error("Partition count is zero");
    }

    if (partitions_count > file_size) {
        throw std::logic_error("Partition count over file size");
    }

    auto partition_size = file_size / partitions_count;
    assert(partition_size > 0);

    positions.reserve(partitions_count);
    for (uint i = 0; i < partitions_count - 1; i++) {
        auto position = (i + 1) * partition_size;
        in.seekg(position - 1);
        std::string buf;
        std::getline(in,buf);
        std::ios::streamoff pos = in.tellg();
        positions.push_back(pos);
    }
    positions.push_back(file_size);

    return positions;
}

#endif //MAP_REDUCE_HELPERS_H
