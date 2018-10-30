//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_IMAP_H
#define MAP_REDUCE_IMAP_H

#include <unordered_map>

template<class key, class value, class container = std::unordered_map<key,value>>
class IMap
{
public:
    using key_type = key;
    using value_type = value;
    using container_type = container;

    virtual void add_value(const value_type&) = 0;
    virtual container_type get_result() = 0;
    virtual ~IMap() = default;
};


#endif //MAP_REDUCE_IMAP_H
