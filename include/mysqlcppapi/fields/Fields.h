#ifndef MYSQLCPPAPI_Fields_h
#define MYSQLCPPAPI_Fields_h

#include "mysqlcppapi/fields/FieldInfo.h"
#include <vector>

namespace mysqlcppapi
{

class Connection;
class ResUse;

/// A vector of FieldInfos, with some extra utility methods.
class Fields : public std::vector<FieldInfo>
{
public:
  Fields();
  explicit Fields(MYSQL_RES* pResult, bool bFullFieldInfo = false);
  //bFullFieldInfo: Some MYSQL_RES members are random unless the result comes from mysql_list_fields().
    
  Fields(const Fields& src);
  virtual ~Fields();

  Fields& operator=(const Fields& src);
  
  /// Returns the field with an offset of i;
  const FieldInfo& operator [] (size_type i) const;
  const FieldInfo& operator [] (const std::string& strFieldName) const;

  size_type get_index(const std::string& strFieldName) const;

  bool get_PrimaryKey(size_type& i) const; //bool indicates success.
  
protected:
  typedef std::vector<FieldInfo> type_base;
};



} //namespace

#endif //MYSQLCPPAPI_Fields_h

