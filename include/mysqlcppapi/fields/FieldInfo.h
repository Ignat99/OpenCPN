#ifndef MYSQLCPPAPI_FieldInfo_h
#define MYSQLCPPAPI_FieldInfo_h

#include "mysqlcppapi/fields/FieldType.h"
#include <string>

namespace mysqlcppapi
{

//The field definition.
//Includes its FieldType information.
//The FieldType of 2 fields might be equal (or a conversion might be possible).
//but the complete FieldInfo could be not-equal.
class FieldInfo
{
public:
  FieldInfo();
  explicit FieldInfo(const MYSQL_FIELD& mysqlField, bool bFullFieldInfo = false);
  //bFullFieldInfo: Some MYSQL_RES members are random unless the result comes from mysql_list_fields().
    
  FieldInfo(const FieldInfo& src);
  virtual ~FieldInfo();

  FieldInfo& operator=(const FieldInfo& src);

  bool operator==(const FieldInfo& src) const;

  std::string get_Name() const;
  std::string get_DefaultValue() const;
  bool get_IsPrimaryKey() const;
  bool get_IsUnique() const;
  bool get_HasAutoIncrement() const;
  FieldType get_FieldType() const;

  void set_Name(const std::string& strVal);
  void set_DefaultValue(const std::string& strVal);
  void set_IsPrimaryKey(bool bVal);
  void set_IsUnique(bool bVal);
  void set_HasAutoIncrement(bool bVal);
  void set_FieldType(const FieldType& fieldType);

  std::string get_TableName() const;
  void set_TableName(const std::string& strVal);
    
  std::string get_field_definition() const; //description needed for a CREATE TABLE command.

  std::string sql(const std::string& strValue) const;

 
protected:
  std::string m_strName;
  FieldType m_FieldType;
  std::string m_strDefaultValue;
  bool m_bPrimaryKey;
  bool m_bUnique;
  bool m_bAutoIncrement;

  std::string m_strTableName; //TODO: Remove this.
};

} //namespace

#endif //MYSQLCPPAPI_FieldInfo_h
