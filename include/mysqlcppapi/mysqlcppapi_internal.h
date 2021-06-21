
#ifndef MYSQLCPPAPI_internal_h
#define MYSQLCPPAPI_internal_h

#include <mysql/mysql.h> // Header for MySQL C API.
#include "mysqlcppapi/windows_includes.h" //Conditionally includes windows headers.

#include <string>

namespace mysqlcppapi
{

//typedef MYSQL_FIELD Field;
typedef long long int longgint;

#ifndef uint
typedef unsigned int uint;
#endif

} //namespace

#endif // MYSQLCPPAPI_internal_h

