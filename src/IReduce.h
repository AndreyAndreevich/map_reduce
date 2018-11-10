//
// Created by Andrey on 10/11/2018.
//

#ifndef MAP_REDUCE_IREDUCE_H
#define MAP_REDUCE_IREDUCE_H

template<class value, class result>
class IReduce
{
public:
    using value_type = value;
    using result_type = result;

    virtual void push(value_type && value_) = 0;
    virtual result_type process() = 0;
};

#endif //MAP_REDUCE_IREDUCE_H
