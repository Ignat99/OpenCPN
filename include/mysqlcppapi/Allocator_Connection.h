#ifndef MYSQLCPPAPI_CONNECTION_ALLOCATOR_H
#define MYSQLCPPAPI_CONNECTION_ALLOCATOR_H


#include "mysqlcppapi/smartpointer/Allocator.h"
#include "mysqlcppapi_internal.h"

namespace mysqlcppapi
{

class Allocator_Connection : public Allocator<MYSQL>
{
public:
  static cpointer allocate();
  static void deallocate(cpointer pInstance);
};

} //namespace

#endif //MYSQLCPPAPI_CONNECTION_ALLOCATOR_H


