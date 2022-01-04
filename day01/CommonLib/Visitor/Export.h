#ifndef VISITOR_EXPORT_H
#define VISITOR_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( VISITOR_LIBRARY_STATIC )
    #    define VISITOR_EXPORT
    #  elif defined( VISITOR_LIBRARY )
    #    define VISITOR_EXPORT   __declspec(dllexport)
    #  else
    #    define VISITOR_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define VISITOR_EXPORT
#endif  

#endif
