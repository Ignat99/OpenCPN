#ifndef MYSQLCPPAPI_row_template_h
#define MYSQLCPPAPI_row_template_h

#include "mysqlcppapi/fields/FieldInfo.h"
#include <vector>
#include <string>

namespace mysqlcppapi
{

typedef std::vector<FieldInfo> FieldNames;

template <class ThisType, class Res>
class RowTemplate
{
public:
  RowTemplate()
  {
  }

  virtual ~RowTemplate()
  {
  }
  
  virtual const Res& parent() const = 0;
 

};


// RowTemplate


} //namespace

#endif //MYSQLCPPAPI_row_template_h


