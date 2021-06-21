#ifndef MYSQLCPPAPI_result_h
#define MYSQLCPPAPI_result_h

#include "mysqlcppapi/query_results/Result_Use.h"
#include "mysqlcppapi/exceptions/ex_BadQuery.h"

namespace mysqlcppapi
{

/** This class handles the result set. 
 * It is also a Random Access Container that is not LessThanComparable
 * and not Assignable. Being a Random Access Container it can
 * return a Random Access Iterator or a reverse Random Access Iterator
 * yet.
 */
class Result_Store :
    virtual public Result_Use, 
    virtual public const_subscript_container<Result_Store, Row, const Row>
{
public:
  Result_Store();

  ///The copy will share the underlying result.
  Result_Store(const Result_Store& src);
    
  explicit Result_Store(MYSQL_RES *result, bool bFullFieldInfo = false);
  //bFullFieldInfo: Some MYSQL_RES members are random unless the result comes mysql_list_fields().

  virtual ~Result_Store();

  ///The copy will share the underlying result.
  Result_Store& operator=(const Result_Store& src);
  
  Row fetch_row() const;
 
  /// Raw C API function
  void data_seek(size_type offset) const;
  
  /// @retval The number of rows.
  size_type size() const;

  /// Returns the row with an offset of i.
  const Row operator [] (size_type i) const;

protected:
  typedef Result_Use type_base;
  typedef const_subscript_container<Result_Store, Row, const Row> type_container;
};



inline void swap(Result_Store& x, Result_Store& y)
{
  Result_Store tmp = x;
  x = y;
  y = tmp;
}

} //namespace

#endif //MYSQLCPPAPI_result_h

