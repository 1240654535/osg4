#ifndef EVENTHANDLE_EXPORT_H
#define EVENTHANDLE_EXPORT_H
#include <windows.h>
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( EVENTHANDLE_LIBRARY_STATIC )
    #    define EVENTHANDLE_EXPORT
    #  elif defined( EVENTHANDLE_LIBRARY )
    #    define EVENTHANDLE_EXPORT   __declspec(dllexport)
    #  else
    #    define EVENTHANDLE_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define EVENTHANDLE_EXPORT
#endif  

#endif
