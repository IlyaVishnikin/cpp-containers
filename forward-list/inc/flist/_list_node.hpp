#pragma once

template<class T>
struct _list_node
{
    T data{T{}};
    _list_node<T>* next{nullptr};
};
