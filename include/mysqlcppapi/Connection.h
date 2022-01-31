#ifndef MYSQLCPPAPI_CONNECTION_H
#define MYSQLCPPAPI_CONNECTION_H

#include "mysqlcppapi_internal.h"

#include "mysqlcppapi/exceptions/ex_BadQuery.h"
#include "mysqlcppapi/exceptions/ex_Locked.h"
#include "mysqlcppapi/Allocator_Connection.h"
#include "mysqlcppapi/smartpointer/SharedPtr.h"
#include "mysqlcppapi/query_results/Result_Use.h"

#include <vector>
#include <deque>
#include <list>
#include <set>

namespace mysqlcppapi
{
class Query;
class Fields;
class Result_NoData;
class Result_Store;

/// A connection to the database.
class Connection
{
public:
  Connection();

  virtual ~Connection();

  // Allow implicit copy constructor and assignment operator.
  // Copies will share the underlying connection.
 
  virtual void close();  
  virtual std::string info();  

  /// @retval true if the connection is still open.
  virtual bool is_connected() const;

  /// @retval true if the last query was successful.
  virtual bool success() const;

  virtual void set_Host(const std::string& strVal);
  virtual void set_User(const std::string& strVal);
  virtual void set_Password(const std::string& strVal);
  virtual void set_Port(unsigned int uiVal);
  virtual void set_UnixSocket(const std::string& strVal);
  virtual void set_ClientFlags(unsigned int uiVal);
  virtual void set_Timeout(unsigned int uiVal);
  
  virtual void connect();

  typedef std::vector<std::string> type_vecStrings;
  virtual type_vecStrings get_DatabaseNames(const std::string& strPattern = "");
  
  virtual void select_database(const std::string& strDatabaseName);

  virtual type_vecStrings get_TableNames(const std::string& strPattern = "");

  virtual Fields get_fields(const std::string& strTableName, const std::string& strPattern = "");
  
  virtual void lock() throw(ex_Locked);
  virtual void unlock();

  /// @retval A query object which uses this connection.
  Query create_Query();
  
  Result_NoData execute(const std::string& str);
  Result_Store store(const std::string& str);
  Result_Use use(const std::string& strs);

  unsigned long get_last_auto_increment();

  /// @retval The last error message().
  std::string error();
  int errnum();
  int refresh(unsigned int refresh_options);
  int ping();
  int kill(unsigned long pid);
  std::string get_client_info();
  
  std::string host_info();
  
  int proto_info();
  
  std::string server_info();
 
  std::string stat();

 
  bool create_database(const std::string& strName); 
  bool drop_database(const std::string& strName);
  
  bool reload(); 
  bool shutdown(); 
  
  st_mysql_options get_options () const;
  int read_options(enum mysql_option option, const std::string& arg);

  template <class Sequence> void storein_sequence(Sequence& , const std::string& str);
  template <class Set>      void storein_set(Set& sett, const std::string& str);

  //!dummy: void storein(TYPE &con, const std::string& s);
  //: Stores the results in TYPE.  
  // Stores the result in TYPE. TYPE must be some sort of STL container.  

  template <class T>        void storein(std::vector<T> &con, const std::string& s)
    {storein_sequence(con,s);}
  template <class T>        void storein(std::deque<T> &con, const std::string& s)
     {storein_sequence(con,s);}
  template <class T>        void storein(std::list<T> &con, const std::string& s)
    {storein_sequence(con,s);}
  template <class T>        void storein(std::set<T> &con, const std::string& s)
    {storein_set(con,s);}
  template <class T>        void storein(std::multiset<T> &con, const std::string& s)
    {storein_set(con,s);}


  /// @return the number of rows affected by the previous query on this connection.
  int affected_rows();

  int insert_id();

protected:
  void query(const std::string& strQuery);
  void check_connection_is_open() throw(ex_base);

  //All member data is shared between copied instances:
  struct ConnectionData
  {
      std::string  host, user, password, database;
      unsigned int port;
      std::string  unix_socket;
      unsigned int client_flags;
      unsigned int timeout;
      bool         locked;
      bool         success;
      bool         is_connected;
  };
  SharedPtr<ConnectionData> m_connection_data;

private:

  typedef SharedPtr<MYSQL, Allocator_Connection> type_sharedptr_connection;
  type_sharedptr_connection m_sharedptr_connection;
};


template <class Sequence>
void Connection::storein_sequence(Sequence& seq, const std::string& str) {
  Result_Use result = use(str);
  while(true)
  {
    try
    {
      const Row& row = result.fetch_row();
      seq.push_back(typename Sequence::value_type(row));
    }
    catch (...)
    {
      break;
    }
  }
}

template <class Set>
void Connection::storein_set(Set& sett, const std::string& str) {
  Result_Use result = use(str);
  while(true)
  {
    try
    {
      const Row& row = result.fetch_row();
      sett.insert(typename Set::value_type(row));
    }
    catch (...)
    {
      break;
    }
  }
}


} //namespace

#endif //MYSQLCPPAPI_CONNECTION_H

