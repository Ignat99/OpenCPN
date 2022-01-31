#ifndef MYSQLCPPAPI_QUERY_H
#define MYSQLCPPAPI_QUERY_H

#include "mysqlcppapi/query/sql_query.h"
#include "mysqlcppapi/Connection.h"

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include "mysqlcppapi/query_results/Result_Store.h"
#include "mysqlcppapi/query_results/Result_NoData.h"

namespace mysqlcppapi
{
//: A Query class suitable for executing queries.  
// This is the class is subclassed from SQLQuery. This class unlike
// SQLQuery is loosely attached to a Mysql object so that it can
// execute queries.
class Query : public SQLQuery
{
public:
  /// Create a new query object attached to a connection.
  explicit Query(const Connection& connection);
 
  Query(const Query& src);
  virtual ~Query();
   
  Query& operator=(const Query &q);

  /// The error message if the query was not successful.
  std::string error();

  bool success();
 
  /// Displays the string currently in the buffer.  
  std::string preview();

  /** Executes the query and returns a structure
   * that contains the information of the success of the query. Use
   * this for queries that don't return a result set such as INSERT,
   * UPDATE, etc.
   */
  Result_NoData execute();

  /** Executes the query in the string buffer.
   * Executes the query and returns the
   * results. This method uses the mysql_use_result(MYSQL_RES)
   * function and thus should be used sparingly. Also the Result set is
   * a lot more limited and DOES NOT have an iterator.
   */
  Result_Use use();

  /** Executes the query and returns the result.
   */
  Result_Store store();

 
  template <class Sequence>
  void storein_sequence (Sequence &seq, const std::string& s);

  template <class Set>
  void storein_set (Set &sett, const std::string& s);

  template <class T>
  void storein (T &con, const std::string& s);

protected:

  Result_NoData execute(const std::string& str);
  Result_Store store(const std::string& str);
  Result_Use use(const std::string& str);

  typedef Result_NoData::type_sharedptr_connection type_sharedptr_connection;
  type_sharedptr_connection m_sharedptr_connection;

  int affected_rows() const;
  int insert_id ();

};

template <class Sequence>
void Query::storein_sequence (Sequence &seq, const std::string& s)
{
  m_sharedptr_connection->storein_sequence (seq, s);
}

template <class Set>
void Query::storein_set (Set &sett, const std::string& s)
{
  m_sharedptr_connection->storein_set (sett, s);
}

template <class T>
void Query::storein (T &con, const std::string& s)
{
  m_sharedptr_connection->storein (con, s);
}

} //namespace

#endif //MYSQLCPPAPI_QUERY_H


