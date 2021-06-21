#ifndef MYSQLCPPAPI_ALLOCATOR_H
#define MYSQLCPPAPI_ALLOCATOR_H

#include "mysqlcppapi/exceptions/ex_base.h"

namespace mysqlcppapi
{


//Derive new Allocators to use e.g. ct_cmd_alloc and ct_cmd_drop instead of new and delete.
template<typename T_cobj>
class Allocator
{
public:
  typedef T_cobj cvalue_type;
  typedef T_cobj* cpointer;

  //An actual derived Allocator should implement these methods:
  //static cpointer allocate();
  //
  //static void deallocate(cpointer pInstance);


};

//Allocator that implements allocate() and deallocate() with simple C++ new and delete.
template<typename T_cobj>
class Allocator_NewDelete : public Allocator<T_cobj>
{
public:  
  typedef typename Allocator<T_cobj>::cpointer cpointer;

  static cpointer allocate()
  {
    return new T_cobj();
  }
 
  static void deallocate(cpointer pInstance)
  {
    delete pInstance;
  }
};

} //namespace

#endif //MYSQLCPPAPI_ALLOCATOR_H

