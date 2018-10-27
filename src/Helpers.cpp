//
// Created by Андрей Лукин on 27.10.2018.
//

#include "Helpers.h"

#include <vector>
#include <fstream>
#include <exception>

std::vector<std::ios::streamoff> split_file(const char* filename, const uint partitions_count) {
    std::vector<std::ios::streamoff> positions;
    std::ifstream file(filename,std::ios_base::binary | std::ios_base::ate);
    if (!file.is_open()) {
        throw std::logic_error("Incorrect file name");
    }

    std::ios::streamoff file_size = file.tellg();
    if (file_size == 0) {
       throw std::logic_error("File is empty");
    }

    if (partitions_count == 0) {
        throw std::logic_error("Partition count is zero");
    }

    if (partitions_count > file_size) {
        throw std::logic_error("Partition count over file size");
    }

    auto partition_size = file_size / partitions_count;
    if (partition_size == 0) {
        throw std::logic_error("Partition size is zero");
    }

    positions.reserve(partitions_count);
    for (uint i = 0; i < partitions_count - 1; i++) {
        auto position = (i + 1) * partition_size;
        file.seekg(position);
        std::string buf;
        std::getline(file,buf);
        std::ios::streamoff pos = file.tellg();
        positions.push_back(pos);
    }
    positions.push_back(file_size);

    return positions;
}
