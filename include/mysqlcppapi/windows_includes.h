#ifndef MYSQLCPPAPI_windows_includes_h
#define MYSQLCPPAPI_windows_includes_h

//Include the Windows headers if this is being compiled on Windows:
#ifdef __WIN32__
	#include <Windows32/Base.h>
	#include <Windows32/Defines.h>
	#include <Windows32/Structures.h>
	#include <winsock.h>
	
  #define errno WSAGetLastError()
#endif


#endif //MYSQLCPPAPI_windows_includes_h
