//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_MAP_H
#define MAP_REDUCE_MAP_H

#include "IMap.h"
#include "Node.h"

#include <string>
#include <map>

class Map final : public IMap<std::string,std::map<char,Node<char>>>
{
    using node = Node<char>;
public:
    void push(const value_type & value_) final {
        if (value_.empty()) {
            return;
        }
        std::deque<char> deque;
        for (auto element : value_) {
            deque.push_back(element);
        }

        auto index = deque.front();
        auto iter = _container.find(index);
        if (iter != _container.end()) {
            iter->second.push(std::move(deque));
        } else {
            _container.insert({index,node(std::move(deque))});
        }
    }

    partitions_type split(const size_type & size_) final {
        constexpr node::key_type min = std::numeric_limits<node::key_type>::min();
        constexpr node::key_type max = std::numeric_limits<node::key_type>::max();
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

        auto part = static_cast<node::key_type>(range / size_);

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
