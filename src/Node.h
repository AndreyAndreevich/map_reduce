//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_NODE_H
#define MAP_REDUCE_NODE_H

#include <map>
#include <list>
#include <deque>
#include <algorithm>

template<class T>
class Node
{
public:
    using key_type = T;
    using value_type = std::deque<T>;
    using value_list_type = std::list<value_type>;
    using node_map_type = std::map<T,Node<T>>;
    using depth_type = size_t;
    using size_type = size_t;

    Node() = default;

    template<class VALUE_TYPE = value_type>
    Node(VALUE_TYPE && value) {
        if (value.size()) {
            _value_list.push_back(std::forward<VALUE_TYPE>(value));
            _max_depth = 1;
        }
    }

    Node(std::initializer_list<value_type> && values) {
        for (auto && value : values) {
            push(std::move(value));
        }
    }

    depth_type push(const value_type & value) {
        auto copy = value;
        return this->push(std::move(copy));
    }

    depth_type push(value_type && value) {
        if (value.empty()) {
            return 0;
        }
        depth_type depth = 1;
        auto first_element = value.front();
        auto map_iter = _node_map.find(first_element);

        auto add_to_map = [&depth,first_element,this] (auto && value, auto & map_iter) {
            value.pop_front();
            depth += map_iter->second.push(std::move(value));
        };

        if (map_iter != _node_map.end()) {
            add_to_map(value, map_iter);
        } else {
            auto list_iter = std::find_if(
                    _value_list.begin(),
                    _value_list.end(),
                    [first_element] (const auto & element) {
                        return element.front() == first_element;
                    });
            if (list_iter != _value_list.end()) {
                if (value != *list_iter) {
                    auto found_value = *list_iter;
                    _value_list.erase(list_iter);
                    found_value.pop_front();
                    map_iter = _node_map.insert({first_element, Node(std::move(found_value))}).first;
                    add_to_map(value, map_iter);
                }
            } else {
                _value_list.push_back(std::move(value));
            }
        }

        this->check_and_change_depth(depth);
        return depth;
    }

    depth_type max_depth() const {
        return _max_depth;
    }

private:
    void check_and_change_depth(const depth_type & depth) {
        if (depth > _max_depth) {
            _max_depth = depth;
        }
    }

private:
    value_list_type _value_list;
    node_map_type _node_map;
    depth_type _max_depth = 0;
};

#endif //MAP_REDUCE_NODE_H
