#ifndef MYSQLCPPAPI_resuse_h
#define MYSQLCPPAPI_resuse_h

#include "mysqlcppapi/fields/Fields.h"
#include "mysqlcppapi/row/Row.h"
#include "mysqlcppapi/smartpointer/SharedPtr.h"
#include "mysqlcppapi/query_results/Allocator_Result.h"

namespace mysqlcppapi
{

class Connection;

class Result_Use
{
public:
  Result_Use();
  explicit Result_Use(MYSQL_RES* pResult, bool bFullFieldInfo = false);
  Result_Use(MYSQL_RES* pResult, const Connection& connection, bool bFullFieldInfo = false);
  //bFullFieldInfo: Some MYSQL_RES members are random unless the result comes from mysql_list_fields().

  ///The copy will share the underlying result.
  Result_Use(const Result_Use& src);
  virtual ~Result_Use ();

  ///The copy will share the underlying result.
  Result_Use& operator=(const Result_Use& src);

  bool operator==(const Result_Use& src) const;
  bool operator!=(const Result_Use& src) const;

  typedef Fields::size_type size_type1;
  
  Row fetch_row();

  bool eof() const;

  typedef std::vector<long unsigned int> type_vecLengths;
  type_vecLengths get_lengths() const;
  
 
  size_type1 num_fields() const;

  /// @retval Table name  
  std::string get_table_name() const;
  
  Fields get_fields() const;
  
protected:

  //It would be nice to just copy the Connection, instead of using a SharedPtr<>(new Connection),
  //but that would cause a circular #include.
  typedef SharedPtr<Connection> type_sharedptr_connection;
  type_sharedptr_connection m_connection;

  typedef SharedPtr<MYSQL_RES, Allocator_Result> type_sharedptr_cresult;
  mutable type_sharedptr_cresult m_pMySQL_Res;

  Fields m_Fields;
  std::string m_table_name;
};



//! with_class = Result_Use


inline void swap (Result_Use &x, Result_Use &y) {
  Result_Use tmp = x;
  x = y;
  y = tmp;
}


} //namespace

#endif //MYSQLCPPAPI_resuse_h

