#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft 
{
    template <class T, class Container = ft::vector<T> >
    class  stack 
    {
        typedef T           value_type;
        typedef Container   container_type; //container_type is the type of the underlying container type (defined as an alias of the second class template parameter, Container;
        typedef size_t      size_type;
    private:
        container_type _container;
    public:
    // Constructs a stack that is empty or that is a copy of a base container object.
        explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {} 
        stack( const stack& other ) : _container(other._container){}
        ~stack() {}

        stack& operator=( const stack& other )
        {
            if (*this != other)
            {
                _container = other._container;
            }
            return *this;
        }

        bool empty() const
        {
            return _container.empty();
        }

        size_type size() const
        {
            return _container.size();
        }

        value_type& top()
        {
            return _container.back();
        }

        const value_type& top() const
        {
            return _container.back();
        }

        void push(const value_type& val)
        {
            _container.push_back(val);
        }

        void pop()
        {
            _container.pop_back();
        }
    };

        template <class T, class Container>
        bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container == rhs._container;
        }

        template <class T, class Container>
        bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container != rhs._container;
        }

        template <class T, class Container>
        bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container < rhs._container;
        }

        template <class T, class Container>
        bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container <= rhs._container;
        }
        template <class T, class Container>
        bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container > rhs._container;
        }

        template <class T, class Container>
        bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
        {
            return lhs._container >= rhs._container;
        }
};
#endif
