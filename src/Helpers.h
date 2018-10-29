//
// Created by Андрей Лукин on 27.10.2018.
//

#ifndef MAP_REDUCE_HELPERS_H
#define MAP_REDUCE_HELPERS_H

#include <istream>
#include <vector>

std::vector<std::ios::streamoff>
        split_file(std::istream&& in, const unsigned int partitions_count);

#endif //MAP_REDUCE_HELPERS_H
