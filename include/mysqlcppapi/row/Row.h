#ifndef MYSQLCPPAPI_row_h
#define MYSQLCPPAPI_row_h

#include "mysqlcppapi/row/row_template.h"
#include "mysqlcppapi/ColData.h"
#include "mysqlcppapi/const_subscript_container.h"
//#include "mysqlcppapi/query_results/resuse.hh"
#include "mysqlcppapi/smartpointer/SharedPtr.h"

#include <vector>


namespace mysqlcppapi
{

class Result_Use;

/// This class handles the actual rows in an intelligent manner.
class Row :
  public const_subscript_container<Row,ColData, const ColData>,
  public RowTemplate<Row, Result_Use>
{
public:
  Row();

  typedef long unsigned int type_length;
  Row(MYSQL_ROW d, const Result_Use& result, type_length* jj);
  virtual ~Row();

  //This returns const Result_Use& instead of just Result_Use to avoid a circular #include.
  virtual const Result_Use& parent() const;
  
  ///@retval The number of columns.
  size_type size() const;
  
  /// Returns the value of the field with the index of i.
  const ColData operator [] (size_type i) const;

  /** Returns the value of the field with the field name of i.
   * This method is not as effecent as using the index number,
   * so use it sparingly.
   */ 
  const ColData operator [] (const std::string& i) const;
 

  typedef std::vector<std::string> type_vecStrings;
  virtual type_vecStrings get_vector() const;

private:
//  MYSQL_ROW    data;
  type_vecStrings data;
  std::vector<bool> is_nulls;

  typedef SharedPtr<const Result_Use> type_sharedptr_result;
  type_sharedptr_result m_sharedptr_result;
}; 

} //namespace

#endif  //MYSQLCPPAPI_row_h

