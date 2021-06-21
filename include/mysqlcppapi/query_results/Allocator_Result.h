#ifndef MYSQLCPPAPI_QUERYRESULTS_ALLOCATOR_RESULT_H
#define MYSQLCPPAPI_QUERYRESULTS_ALLOCATOR_RESULT_H


#include "mysqlcppapi/smartpointer/Allocator.h"
#include "mysqlcppapi/mysqlcppapi_internal.h"

namespace mysqlcppapi
{

//The is used to deallocate Results when appropriate,
//but allocation is done by specific queries, which use the SharedPtr(MYSQL_RES*) constructor.
class Allocator_Result : public Allocator<MYSQL_RES>
{
public:
  static cpointer allocate();
  static void deallocate(cpointer pInstance);
};

} //namespace

#endif //MYSQLCPPAPI_QUERYRESULTS_ALLOCATOR_RESULT_H


