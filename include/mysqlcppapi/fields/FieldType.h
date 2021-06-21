#ifndef MYSQLCPPAPI_FieldType_h
#define MYSQLCPPAPI_FieldType_h

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include <map>

namespace mysqlcppapi
{

class Connection;

//Information about the type of data stored in a field.
class FieldType
{
public:
  FieldType();
  FieldType(enum_field_types fieldType, bool bSigned, bool bCanBeNull);
  FieldType(const FieldType& src);
  virtual ~FieldType();

  FieldType& operator=(const FieldType& src);

  bool operator==(const FieldType& src) const;
  //bool operator<(const FieldType& src) const;

  virtual enum_field_types get_Type() const;
  virtual bool get_CanBeNull() const;

  virtual void set_Type(enum_field_types enumType);
  virtual void set_CanBeNull(bool bVal);

  //Not all type use these:
  virtual unsigned int get_MaxLength() const;
  virtual unsigned int get_DecimalsCount() const;
  virtual bool get_Signed() const;

  virtual void set_MaxLength(unsigned int uiVal);
  virtual void set_DecimalsCount(unsigned int uiVal);
  virtual void set_Signed(bool bVal);

    
  virtual bool get_NeedsQuotes() const;
  virtual bool get_NeedsEscaping() const;

  typedef std::map<enum_field_types, std::string> type_mapFieldTypes;
  static type_mapFieldTypes get_mapFieldTypes();

  std::string sql(const std::string& strValue) const;

  //Category as per MySQL manual:
  enum enumTypeCategory
  {
    TYPE_CATEGORY_Unknown,
    TYPE_CATEGORY_Numeric,
    TYPE_CATEGORY_DateAndTime,
    TYPE_CATEGORY_String
  };
  static enumTypeCategory get_TypeCategory(enum_field_types fieldType);
  enumTypeCategory get_TypeCategory() const;

  //Information about the optional details used by a field type:
  enum enumTypeOptionals
  {
    TYPE_OPTIONALS_None,
    TYPE_OPTIONALS_M_D, //(M, D)
    TYPE_OPTIONALS_M_S, //(M) UNSIGNED
    TYPE_OPTIONALS_M, //(M)
    TYPE_OPTIONALS_List //ENUM and SET
  };
  static enumTypeOptionals get_TypeOptionals(enum_field_types fieldType);
  enumTypeOptionals get_TypeOptionals() const;

protected:
  enum_field_types m_field_type;
  bool m_bSigned;
  bool m_bCanBeNull;
  unsigned int m_uiMaxLength;
  unsigned int m_uiDecimalsCount;
  bool m_bNeedsQuotes;
};

} //namespace

#endif //MYSQLCPPAPI_FieldType_h
