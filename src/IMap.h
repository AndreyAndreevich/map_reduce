//
// Created by Андрей Лукин on 29.10.2018.
//

#ifndef MAP_REDUCE_IMAP_H
#define MAP_REDUCE_IMAP_H

#include <vector>

template<class value, class container>
class IMap
{
public:
    using value_type = value;
    using container_type = container;
    using size_type = size_t;
    using partitions_type = std::vector<container_type>;

    virtual void push(value_type && value_) = 0;
    virtual partitions_type split(const size_type & size_) = 0;
    virtual ~IMap() = default;
};


#endif //MAP_REDUCE_IMAP_H
