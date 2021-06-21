#ifndef MYSQLCPPAPI_null_h
#define MYSQLCPPAPI_null_h

#include "mysqlcppapi/exceptions/ex_BadNullConversion.h"
#include <iostream>

namespace mysqlcppapi
{

//! with_class = Null

//TODO: What's this Null stuff all about? murrayc.

class null_type
{
public:
  template <class Type> operator Type ()
  {
    throw ex_BadNullConversion();
  }
};

 
static const null_type null = null_type();

//: Type to use for the behavior parameter for *Null<>*
class NullisNull
{
public:
  static null_type null_is() {return null_type();}
  static std::ostream&  null_ostr(std::ostream& o) {o << "(NULL)"; return o;}
};

//: Type to use for the behavior parameter for *Null<>*
class NullisZero
{
public:
  static int   null_is() {return 0;}
  static std::ostream& null_ostr(std::ostream &o) {o << 0; return o;}
};

//: Type to use for the behavior parameter for *Null<>*
class NullisBlank
{
public:
  static const char* null_is() {return "";}
  static std::ostream& null_ostr(std::ostream &o) {o << ""; return o;}
};

//: Container class for holding null types.
template <class Type, class Behavior = NullisNull>
class Null {
public:
  Type data;
  bool is_null;
  typedef Type value_type;
public:
  Null () {} 
  Null (Type x) : data(x), is_null(false) {} 
   
  Null (const null_type& n) : is_null(true) {}
 
  //: Gives Null the null value
  // Note: the global const *null* (not NULL) is of value null_type thus 
  // you can say something like *Null<Type> x = null*.
  operator Type& () { 
    if (is_null) return data = Behavior::null_is();
    else return data; } 
  
  Null& operator = (const Type& x) {data = x; is_null = false; return *this;}
   
  Null& operator = (const null_type&) {is_null = true; return *this;}
  
};

//: OEP - Specialization for <void>
template <> class Null<void> {
public:
  bool is_null;
  typedef void value_type;
public:
  Null () : is_null(false) {} 
   
  Null (const null_type&) : is_null(true) {} 
  //: Gives Null the null value
  // Note: the global const *null* (not NULL) is of value null_type thus 
  // you can say something like *Null<Type> x = null*.
  
  Null& operator = (const null_type&) {is_null = true; return *this;}
  
};


template <class Type, class Behavior>
inline std::ostream& operator << (std::ostream &o, const Null<Type,Behavior> &n)
{
  if (n.is_null) return Behavior::null_ostr(o);
  else return o << n.data;
}

} //namespace

#endif  // MYSQLCPPAPI_null_h
