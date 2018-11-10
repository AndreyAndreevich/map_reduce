//
// Created by Andrey on 11/11/2018.
//

#ifndef MAP_REDUCE_REDUCE_H
#define MAP_REDUCE_REDUCE_H

#include "IReduce.h"
#include "Node.h"

#include <string>
#include <map>

class Reduce final : public IReduce<std::map<char,Node<char>>, size_t>
{
    using node = Node<char>;
public:
    void add_partition(container_type && partition) final {
        for (auto && element : partition) {
            auto iter = _container.find(element.first);
            if (iter != _container.end()) {
                iter->second.merge(element.second);
            } else {
                _container.insert(std::move(element));
            }
        }
    }

    result_type process() final {
        result_type result = 0;
        for (const auto & element : _container) {
            if (result < element.second.max_depth()) {
                result = element.second.max_depth();
            }
        }
        return result;
    }
private:
    container_type _container;
};

#endif //MAP_REDUCE_REDUCE_H
