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
    Node(const value_type& value) {
        if (value.size()) {
            _value_list.push_back(value);
        }
    }

    depth_type add_value(value_type&& value) {
        if (value.empty()) {
            return 0;
        }
        depth_type depth = 1;
        auto first_element = value.front();
        auto map_iter = _node_map.find(first_element);

        auto add_to_map = [&depth,first_element,this] (auto value, auto map_iter) {
            value.pop_front();
            depth += map_iter->second.add_value(std::move(value));
        };

        if (map_iter != _node_map.end()) {
            add_to_map(value, map_iter);
        } else {
            auto list_iter = std::find_if(
                    _value_list.begin(),
                    _value_list.end(),
                    [first_element] (auto element) {
                        return element.front() == first_element;
                    });
            if (list_iter != _value_list.end()) {
                if (value != *list_iter) {
                    auto found_value = *list_iter;
                    _value_list.erase(list_iter);
                    found_value.pop_front();
                    map_iter = _node_map.insert({first_element, Node(found_value)}).first;
                    add_to_map(value, map_iter);
                }
            } else {
                _value_list.push_back(value);
            }
        }

        return depth;
    }

    depth_type add_value(const value_type& value) {
        auto copy = value;
        return add_value(std::move(copy));
    }

    value_list_type get_all_values() const {
        value_list_type result = _value_list;
        for (const auto& node : _node_map) {
            auto value_list = node.second.get_all_values();
            for (auto value : value_list) {
                value.push_front(node.first);
                result.push_back(value);
            }
        }
        return result;
    }

    size_type size() const {
        size_type size = _value_list.size();
        for (const auto& node : _node_map) {
            size += node.second.size();
        }
        return size;
    }

private:
    value_list_type _value_list;
    node_map_type _node_map;
};

#endif //MAP_REDUCE_NODE_H
