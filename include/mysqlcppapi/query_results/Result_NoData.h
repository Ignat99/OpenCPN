#ifndef MYSQLCPPAPI_Result_NoData_h
#define MYSQLCPPAPI_Result_NoData_h

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include "mysqlcppapi/Allocator_Connection.h"
#include "mysqlcppapi/smartpointer/SharedPtr.h"

#include "mysqlcppapi/exceptions/ex_BadQuery.h"

namespace mysqlcppapi
{

class Connection;

/** This holds the information on the success of queries that
 * don't return any results.
 */
class Result_NoData
{
public:
  Result_NoData();
  Result_NoData(const Result_NoData& src);
  Result_NoData(const Connection& connection);
  virtual ~Result_NoData();

  Result_NoData& operator=(const Result_NoData& src);

  bool get_succeeded() const;
  int get_insert_id() const;
  int get_rows_affected() const;
  std::string get_info() const;

  //It would be nice to just copy the Connection (which does it's own reference counting),
  //instead of using a SharedPtr<Connection>,
  //but that would cause a circular #include.
  typedef SharedPtr<Connection> type_sharedptr_connection;
      
protected:
  bool m_bSucceeded;   
  int m_InsertID;
  int m_RowsAffected;
  std::string m_strInfo;

  //It would be nice to just copy the Connection, instead of using a SharedPtr<>(new Connection),
  //but that would cause a circular #include.
  type_sharedptr_connection m_sharedptr_connection; //Store it, to keep it alive.
};  



} //namespace

#endif //MYSQLCPPAPI_Result_NoData_h

