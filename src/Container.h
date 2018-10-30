//
// Created by Андрей Лукин on 30.10.2018.
//

#ifndef MAP_REDUCE_CONTAINER_H
#define MAP_REDUCE_CONTAINER_H

#include <unordered_map>
#include <map>
#include <set>
#include <memory>

class Container
{
    struct Node 
    {
        using string_list_type = std::set<std::string>;
        using node_map_type = std::map<char,std::unique_ptr<Node>>;
        
        string_list_type string_list;
        node_map_type node_map;
    };
};


#endif //MAP_REDUCE_CONTAINER_H
