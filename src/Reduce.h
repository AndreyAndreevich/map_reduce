//
// Created by Andrey on 11/11/2018.
//

#ifndef MAP_REDUCE_REDUCE_H
#define MAP_REDUCE_REDUCE_H

#include "IReduce.h"
#include "Node.h"

#include <string>
#include <map>

class Reduce final : public IReduce<std::string, size_t>
{
    using container_type = Node<char>;
public:
    void push(value_type && value_) final {
        if (value_.empty()) {
            return;
        }
        container_type::value_type queue;
        for (auto ch : value_) {
            queue.push_back(ch);
        }
        _container.push(std::move(queue));
    }

    result_type process() final {
        return _container.max_depth();
    }
private:
    container_type _container;
};

#endif //MAP_REDUCE_REDUCE_H
