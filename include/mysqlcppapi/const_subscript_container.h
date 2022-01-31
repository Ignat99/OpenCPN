#ifndef MYSQLCPPAPI_const_subscript_container_h
#define MYSQLCPPAPI_const_subscript_container_h

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include <iterator>

namespace mysqlcppapi
{

template <class OnType, class ReturnType>
class subscript_iterator;

//: A container adapter to make a container into a Random Access Container.

// The requirements are that the container has the member functions
// *operator[] (size_type)* _and_  *size()* defined. 

//Abstract base class:
template <class OnType, class ValueType, class ReturnType = const ValueType&>
class const_subscript_container
{
public:
  typedef unsigned int size_type;
  typedef int difference_type;
  
  typedef const_subscript_container<OnType, ValueType, ReturnType> this_type; 

  typedef subscript_iterator<const this_type, ReturnType> iterator;   
  typedef iterator const_iterator; 
  typedef const std::reverse_iterator<iterator> reverse_iterator; 
  typedef const std::reverse_iterator<const_iterator> const_reverse_iterator; 
  
  typedef ValueType value_type; 
  typedef value_type& reference;  
  typedef value_type& const_reference; 
  typedef value_type* pointer; 
  typedef value_type* const_pointer; 
  
  virtual size_type  size() const = 0; 
  virtual ReturnType operator[] (size_type i) const = 0; 

  size_type max_size() const {return size();}    
  bool empty() const {return size()==0;} 
  
  iterator begin() const {return iterator(this, 0);}      
  iterator end() const {return iterator(this, size());} 
  
  reverse_iterator rbegin() const {return reverse_iterator(end());}   
  reverse_iterator rend() const {return reverse_iterator(begin());} 
};


template <class OnType, class ReturnType>
class subscript_iterator
{
public:

  typedef std::random_access_iterator_tag  iterator_category;
  typedef ReturnType                       value_type;
  typedef ReturnType*                      pointer;
  typedef ReturnType&                      reference;
  typedef typename OnType::difference_type difference_type;
  typedef typename OnType::size_type       size_type;

  subscript_iterator() : i(0), d(0) { }

  subscript_iterator(OnType *what, size_type pos) : i(pos), d(what) { }

  bool operator == (const subscript_iterator &j) const
  {
    return (d == j.d && i==j.i);
  }
  
  bool operator != (const subscript_iterator &j) const
  {
    return (d == j.d && i!=j.i);
  }
    
  bool operator < (const subscript_iterator &j) const
  {
    return (d == j.d && i < j.i);
  }
    
  bool operator > (const subscript_iterator &j) const
  {
    return (d == j.d && i > j.i);
  }
    
  bool operator <= (const subscript_iterator &j) const
  {
    return (d == j.d && i<=j.i);
  }
    
  bool operator >= (const subscript_iterator &j) const
  {
    return (d == j.d && i>=j.i);
  }  

#if 0
  ReturnType* operator -> () const
  {
    return &(operator*());  // returns address of temporary!
  }
#endif
  
  ReturnType operator *  () const
  {
    return (*d)[i];
  }
  
  ReturnType operator [] (size_type n) const
  {
    return (*d)[n];
  }

  subscript_iterator& operator ++ ()
  {
    subscript_iterator iterChanged = operator+(1);
    this->operator=(iterChanged);

    return *this;
  }
  
  subscript_iterator operator ++ (difference_type) 
  {
    subscript_iterator iterBefore = *this;
    
    operator++();
    
    return iterBefore;
  }
  
  subscript_iterator& operator -- ()
  {
    subscript_iterator iterChanged = operator-(1);
    this->operator=(iterChanged);

    return *this;
  }
  
  subscript_iterator operator -- (difference_type) 
  {
    subscript_iterator iterBefore = *this;
    
    operator--();
    
    return iterBefore;
  }
  
  subscript_iterator& operator += (difference_type n)
  {
    return operator+(n);
  }
  
  subscript_iterator operator + (difference_type n) const
   {
    subscript_iterator tmp = *this;
    tmp.i += n;
    return tmp;
  }
  
  subscript_iterator& operator -= (difference_type n)
  {
    return operator-(n);
  }
  
  subscript_iterator operator - (difference_type n) const
  {
    return operator+(-n);
  }

  difference_type operator - (const subscript_iterator &j) const
  {
    if (d == j.d) return (size_type)i - j.i;
    return 0;
  }

private:
  size_type i;
  OnType* d;

};

template <class OnType, class ReturnType>
inline subscript_iterator<OnType, ReturnType> operator + 
(typename OnType::size_type x, const subscript_iterator<OnType, ReturnType>& y) 
{
  return y + x;
}

} //namespace

#endif   //MYSQLCPPAPI_const_subscript_container_h

