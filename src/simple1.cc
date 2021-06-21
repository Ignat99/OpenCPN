#include <mysqlcppapi/mysqlcppapi.h>
#include <iostream>
#include <iomanip>

int main() {
  // You may need to specify some connection parameters using the
  // Connection::set_*() members if the database is not on
  // the local machine or your database username is not the same as your
  // login name, etc..
  try {
    mysqlcppapi::Connection con;
    con.set_Host("localhost");
    con.set_User("root");
    con.set_Password("Android123");
    con.connect();
    con.select_database("drf_android");
    
    mysqlcppapi::Query query = con.create_Query();
    // This creates a query object that is bound to con.

    query << "select name, date_creation, product, client_id, creator_id  from projects_project";
    // You can write to the query object like you would any other ostrem

    mysqlcppapi::Result_Store res = query.store();
    // Query::store() executes the query and returns the results

        std::cout << "Query: " << query.preview() << std::endl;
    // Query::preview() simply returns a string with the current query
    // string in it.

        std::cout << "Records Found: " << res.size() << std::endl << std::endl;
    
        std::cout.setf(std::ios::left);
        std::cout << std::setw(1) << "Name "
      << std::setw(2)  << "Date_creation " 
      << std::setw(3)  << "product "
      << std::setw(4)  << "client ID "
      << std::setw(5)  << "creator ID " 
      << "Code" << std::endl
      << std::endl;
  
    // The Result_Store class has a read-only Random Access Iterator
    for (mysqlcppapi::Result_Store::iterator i = res.begin(); i != res.end(); i++)
    {
      mysqlcppapi::Row row = *i;
            std::cout << std::setw(1) << row[0] << "  "
        << std::setw(2)  << row[1]  << "  "
        << std::setw(3)  << row["product"] << "  "
        // you can use either the index number or column name when
        // retrieving the colume data as demonstrated above.
        << std::setw(4)  << row[3] << "  "
        << std::setw(5)  << row[4] << "  " << std::endl;
    }
  }
  catch(mysqlcppapi::ex_BadQuery& er)
  {
   // handle any connection or query errors that may come up
      std::cerr << "Error: " << er.what() <<  std::endl;
    return -1;

  }
  catch(mysqlcppapi::ex_BadConversion& er)
  {
    // we still need to catch bad conversions in case something goes 
    // wrong when the data is converted into stock
      std::cerr << "Error: Tried to convert \"" << er.get_Data() << "\" to a \""
   << er.get_TypeName() << "\"." << std::endl;
    return -1;
  }
  return 0;
}
