//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_MAP_H
#define MAP_REDUCE_MAP_H

#include "IMap.h"
#include "Node.h"
#include <string>


class Map : public IMap<char,std::string,std::unordered_map<char,Node<char>>>
{
public:
    void add_value(const value_type& value) override {

    }

    container_type get_result() override {
        return container;
    }
private:
    container_type container;
};


#endif //MAP_REDUCE_MAP_H
