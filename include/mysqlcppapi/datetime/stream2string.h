#ifndef MYSQLCPPAPI_stream2string_h
#define MYSQLCPPAPI_stream2string_h

#include <sstream>

namespace mysqlcppapi
{

template<class Strng, class T>
  Strng
  stream2string(const T &object)
  {
    std::ostringstream str;
    object.out_stream(str);
    str << std::ends;
    return Strng(str.str());
  }

} //namespace mysqlcppapi

#endif  //MYSQLCPPAPI_stream2string_h

