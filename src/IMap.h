//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_IMAP_H
#define MAP_REDUCE_IMAP_H

#include <unordered_map>

template<typename Key, typename Value>
class IMap
{
public:
    void add_value(const Value&);
    std::unordered_map<Key,Value> get_result();
};


#endif //MAP_REDUCE_IMAP_H
