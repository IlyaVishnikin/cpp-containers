#pragma once
#include "_list_node.hpp"
#include "_list_iterator.hpp"
#include <cstddef>
#include <initializer_list>

// Forward list implementation
template<class T>
class flist
{
    typedef flist<T>      self;
    typedef _list_node<T> node;

public:
    typedef std::size_t              size_type;
    typedef _list_iterator<true, T>  const_iterator;
    typedef _list_iterator<false, T> iterator;


    flist();
    flist(const self& rhs);
    flist(self&& rhs);
    explicit flist(std::initializer_list<T> init_lits);
    ~flist();


    inline T& front() const;
    inline const size_type& size() const;


    [[nodiscard]]
    inline bool empty() const;


    iterator insert_after(iterator pos, const T& value);
    inline void push_front(const T& value);
    void pop_front();
    void clear();


    template<class ...Args>
    iterator emplace_after(iterator it, Args&&... args);
    
    template<class ...Args>
    iterator emplace_front(Args&&... args);


    iterator before_begin() const;
    iterator begin() const;
    iterator end() const;
    const_iterator cbefore_begin() const;
    const_iterator cbegin() const;
    const_iterator cend() const;


    self& operator=(const self& rhs);
    self& operator=(self&& rhs);

protected:
    node* _before_begin;
    node* _begin;
    node* _end;
    size_type _size;
};

// 
// IMPLEMENTATION
//

// CONSTR, DESTR
template<class T>
flist<T>::flist()
    : _before_begin{new node},
      _begin{nullptr},
      _end{nullptr},
      _size{0}
{}

template<class T>
flist<T>::flist(const self& rhs)
    : _before_begin{new node},
      _size{0}
{
    if (this == &rhs) return;

    iterator it{before_begin()};
    for (auto rhs_it = rhs.cbegin(); rhs_it != rhs.cend(); ++rhs_it)
        it = insert_after(it, *rhs_it);

    _end = it._node;
}

template<class T>
flist<T>::flist(self&& rhs)
{
    *this = std::move(rhs);
}

template<class T>
flist<T>::flist(std::initializer_list<T> init_list)
    : _before_begin{new node},
      _size{0}
{
    node* current_node{_before_begin};
    for (auto it = init_list.begin(); it != init_list.end(); ++it)
    {
        current_node->next = new node{*it, nullptr};
        current_node = current_node->next;
        ++_size;
    }

    _begin = _before_begin->next;
    _end = current_node;
}

template<class T>
flist<T>::~flist()
{
    for (node* next, *cur{_before_begin}; cur; cur = next)
    {
        next = cur->next;
        delete cur;
    }
}
// END CONSTS DESTR

// ACCESSORS
template<class T>
T& flist<T>::front() const
{
    if (!_begin)
        throw std::length_error("List is not contans any elements.");

    return _begin->data;
}

template<class T>
const typename flist<T>::size_type&
flist<T>::size() const
{
    return _size;
}
// END ACCESSORS

// EMPTY
template<class T>
bool flist<T>::empty() const
{
    return _size == 0;
}
// END EMPTY

// MODIFIERS
template<class T>
typename flist<T>::iterator
flist<T>::insert_after(iterator pos, const T& value)
{
    if (!pos._node)
        throw std::domain_error("Node that associated with iterator is not exists.");

    node* new_node{new node{value, pos._node->next}};
    pos._node->next = new_node;
    if (pos._node == _before_begin)
        _begin = _begin ? pos._node->next : new_node;

    ++_size;
    return iterator{new_node};
}

template<class T>
void flist<T>::push_front(const T& value)
{
    insert_after(before_begin(), value);
}

template<class T>
void flist<T>::pop_front()
{
    if (!_begin)
        throw std::domain_error("List empty");

    node* begin_next{_begin->next};
    delete _begin;
    _begin = begin_next;
    _before_begin->next = _begin;
    --_size;
}

template<class T>
void flist<T>::clear()
{
    while (_size)
        pop_front();
}
// END MODIFIERS

// EMPLACES
template<class T>
template<class ...Args>
typename flist<T>::iterator
flist<T>::emplace_after(iterator it, Args&&... args)
{
    return iterator{insert_after(it, std::forward<Args>(args)...)};
}

template<class T>
template<class ...Args>
typename flist<T>::iterator
flist<T>::emplace_front(Args&&... args)
{
    iterator begin_iter{emplace_after(before_begin(), std::forward<Args>(args)...)};
    _begin = begin_iter._node;
    return begin_iter;
}
// END EMPLACES

// ITERATORS
template<class T>
typename flist<T>::iterator
flist<T>::before_begin() const
{
    return iterator{_before_begin};
}

template<class T>
typename flist<T>::iterator
flist<T>::begin() const
{
    return iterator{_begin};
}

template<class T>
typename flist<T>::iterator
flist<T>::end() const
{
    return iterator{_end ? _end->next : nullptr};
}

template<class T>
typename flist<T>::const_iterator
flist<T>::cbefore_begin() const
{
    return const_iterator{_before_begin};
}

template<class T>
typename flist<T>::const_iterator
flist<T>::cbegin() const
{
    return const_iterator{_begin};
}

template<class T>
typename flist<T>::const_iterator
flist<T>::cend() const
{
    return const_iterator{_end ? _end->next : nullptr};
}
// END ITERATORS

// ASSIGNMENT OPERATORS
template<class T>
typename flist<T>::self&
flist<T>::operator=(const self& rhs)
{
    if (this == &rhs) return *this;

    *this = std::move(self(rhs));
    return *this;
}

template<class T>
typename flist<T>::self&
flist<T>::operator=(self&& rhs)
{
    *this = std::move(rhs);
    return *this;
}
// END ASSIGNMENT OPERATORS