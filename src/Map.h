//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_MAP_H
#define MAP_REDUCE_MAP_H

#include "IMap.h"
#include "Node.h"

#include <string>
#include <map>

class Map final : public IMap<std::string,std::multimap<char,std::string>>
{
public:
    void push(value_type && value_) final {
        if (value_.empty()) {
            return;
        }
        _container.emplace(value_.at(0),std::move(value_));
    }

    partitions_type split(const size_type & size_) final {
        constexpr container_type::key_type min = std::numeric_limits<container_type::key_type>::min();
        constexpr container_type::key_type max = std::numeric_limits<container_type::key_type>::max();
        constexpr auto range = max - min;
        if (size_ <= 0 || size_ > range) {
            throw std::logic_error("Numbers of partitions are incorrect");
        }

        partitions_type partitions;
        partitions.reserve(size_);

        auto set_partition = [&partitions] (auto && begin, auto && end) {
            container_type partition;
            std::move(begin,end,std::inserter(partition,partition.begin()));
            partitions.push_back(std::move(partition));
        };

        auto part = static_cast<container_type::key_type>(range / size_);

        for (auto i = 0; i < size_ - 1; i++) {
            set_partition(
                _container.lower_bound(static_cast<char>(min + part * i)),
                _container.upper_bound(static_cast<char>(min + part * (i + 1)))
            );
        }

        set_partition(
            _container.lower_bound(static_cast<char>(min + part * (size_ - 1))),
            _container.end()
        );

        return partitions;
    }
private:
    container_type _container;
};


#endif //MAP_REDUCE_MAP_H
