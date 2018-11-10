//
// Created by Andrey on 10/11/2018.
//

#ifndef MAP_REDUCE_IREDUCE_H
#define MAP_REDUCE_IREDUCE_H

template<class container, class result>
class IReduce
{
public:
    using container_type = container;
    using result_type = result;

    virtual void add_partition(container_type && partition) = 0;
    virtual result_type process() = 0;
};

#endif //MAP_REDUCE_IREDUCE_H
