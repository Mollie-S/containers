#ifndef STACK_HPP
#define STACK_HPP

#include <vector> //removed when replaced with ft_vector

namespace ft 
{
    template <class T, class Container = std::vector<T> > // !!!!!!!!!!!!!!   replace std::vector with ft_vector
    class  stack 
    {
        typedef T           value_type;
        typedef Container   container_type; //container_type is the type of the underlying container type (defined as an alias of the second class template parameter, Container;
        typedef size_t      size_type;
    private:
        container_type _container;
    public:
        explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {} // Constructs a stack that is empty or that is a copy of a base container object.
        ~stack() {}

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
};
#endif