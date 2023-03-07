#pragma once
#include "_list_node.hpp"
#include "flist.hpp"
#include <iterator>

template<bool Const, class T>
class _list_iterator
{
    template<class FlistT> friend class flist;
    friend class _list_iterator<!Const, T>;

    typedef _list_iterator<Const, T> self;
    typedef _list_node<T>            node;

    // only for friends
    explicit _list_iterator(node* node);

public:
    // used for std::iterator_traits
    typedef std::forward_iterator_tag               iterator_category;
    typedef T                                       value_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef std::conditional_t<Const, const T&, T&> reference;
    typedef std::conditional_t<Const, const T*, T*> pointer;


    reference operator*() const noexcept;
    self& operator++();
    self  operator++(int);

    
    template<bool ConstRhs>
    bool operator==(const _list_iterator<ConstRhs, T>& rhs) const noexcept;

    template<bool ConstRhs>
    bool operator!=(const _list_iterator<ConstRhs, T>& rhs) const noexcept;


    // convertion operator from nonconst to const
    operator _list_iterator<true, T>() const noexcept;

private:
    node* _node;
};

//
// IMPLEMENTATION
//

template<bool Const, class T>
_list_iterator<Const, T>::_list_iterator(node* node)
    : _node{node}
{}

template<bool Const, class T>
typename _list_iterator<Const, T>::reference
_list_iterator<Const, T>::operator*() const noexcept
{
    return _node->data;
}

template<bool Const, class T>
_list_iterator<Const, T>&
_list_iterator<Const, T>::operator++()
{
    _node = _node ? _node->next : nullptr;
    return *this;
}

template<bool Const, class T>
_list_iterator<Const, T>
_list_iterator<Const, T>::operator++(int)
{
    self _self{*this};
    ++*this;
    return _self;
}

template<bool Const, class T>
template<bool ConstRhs>
bool _list_iterator<Const, T>::operator==(const _list_iterator<ConstRhs, T>& rhs) const noexcept
{
    return _node == rhs._node;
}

template<bool Const, class T>
template<bool ConstRhs>
bool _list_iterator<Const, T>::operator!=(const _list_iterator<ConstRhs, T>& rhs) const noexcept
{
    return _node != rhs._node;
}

template<bool Const, class T>
_list_iterator<Const, T>::operator _list_iterator<true, T>() const noexcept
{
    return _list_iterator<true, T>{_node};
}
