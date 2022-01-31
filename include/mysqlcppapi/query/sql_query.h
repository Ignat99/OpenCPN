#ifndef MYSQLCPPAPI_sql_query_h
#define MYSQLCPPAPI_sql_query_h

#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace mysqlcppapi
{


//: The "pure" query class 

// This is the "pure" query class. It is used to form queries to send
// to the *Connection* object. The *Query* class can be used if you
// wish to also be able to execute the queries without having to send
// them to the *Connection* object.
//
// This class is subclassed from *sstream*. This means that you can
// write to it like a stream to avoid having to piece parts together
// by creating you own *sstream* or by using *sprintf*. Although you
// can read from query because it is a stream this is _not_
// recommended. I can not guarantee the predictability of the class if
// you do and will offer no help if you run into problems when you do
// this. However, feel free to use any of the stream methods to write
// to it. Just make sure that the write buffer points to the end of
// your query before you try to use any of the *SQLQuery* specific
// methods except for *error()* and *success()*.

class SQLQuery : public std::stringstream
{ 
public:
  SQLQuery();
  SQLQuery(const SQLQuery &q); 
  SQLQuery& operator = (const SQLQuery &q); 

  std::string   error () const {return errmsg;}
  bool     success() const {return Success;}


  //!dummy: std::string str (query_reset r = DONT_RESET);
  //: Returns the full query string.
  // Returns the full query string, replacing it with the default
  // template parameters if necessary. *query_reset* can either be
  // DONT_RESET or RESET_QUERY. If it is set the RESET_QUERY then
  // reset() is called after it has finished returning the query. If
  // there is not enough  parameters then it will return a
  // empty string and *success()* would be false.

  //!dummy: string str (const SQLString &parm0, ...,const SQLString &parm11);
  //: Like str(query_reset) but sets the parameters.
  // Like str(query_reset) but sets query parameters 0 to (up to)
  // 11. To parm0, parm1 etc. This is achieved by overloaded methods
  // and templates and not the ...
  //
  // It will combine this with def. If any of the required parameters
  // are null it will produce an error and return an empty string.

  //!dummy: string str(const SQLQueryParameters & p, query_reset r = DONT_RESET);
  //: Like *str(query_reset)* but sets the parameter.
  // Like *query(query_reset res)* but sets the parameters based on
  // combining p and def.
  //
  // If any of the required parameters are null it will produce an
  // error and return an empty string.

private:
  
protected:
  
  bool Success;
  std::string errmsg;
};  

} //namespace

#endif //MYSQLCPPAPI_sql_query_h
