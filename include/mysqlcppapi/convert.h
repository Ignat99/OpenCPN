#ifndef MYSQLCPPAPI_convert_h
#define MYSQLCPPAPI_convert_h

#include <cstdlib>

namespace mysqlcppapi
{

template <class Type> class mysql_convert;

#define mysql__convert(TYPE, FUNC) \
  template <> \
  class mysql_convert<TYPE> {\
  private:\
    TYPE num;\
  public:\
    mysql_convert(const char* str, const char *& end) { \
      num = FUNC(str, const_cast<char **>(&end));}\
    operator TYPE () {return num;}\
  };\

mysql__convert(float, strtod)
mysql__convert(double, strtod)

#undef mysql__convert
#define mysql__convert(TYPE, FUNC) \
  template <> \
  class mysql_convert<TYPE> {\
  private:\
    TYPE num;\
  public:\
    mysql_convert(const char* str, const char *& end) { \
      num = FUNC(str, const_cast<char **>(&end),10);}\
    operator TYPE () {return num;}\
  };\

mysql__convert(char, strtol)
mysql__convert(signed char, strtol)
mysql__convert(int, strtol)
mysql__convert(short int, strtol)
mysql__convert(long int, strtol)

mysql__convert(unsigned char, strtoul)
mysql__convert(unsigned int, strtoul)
mysql__convert(unsigned short int, strtoul)
mysql__convert(unsigned long int, strtoul)

#ifndef NO_LONG_LONGS
#ifdef _FIX_FOR_BSD_
mysql__convert(long long int, strtoq)
mysql__convert(unsigned long long int, strtouq)
#else
mysql__convert(long long int, strtoll)
mysql__convert(unsigned long long int, strtoull)
#endif
#endif

} //namespace

#endif //MYSQLCPPAPI_convert_h



