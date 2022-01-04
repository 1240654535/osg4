#ifndef PRIMITIVE_EXPORT_H
#define PRIMITIVE_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( PRIMITIVE_LIBRARY_STATIC )
    #    define PRIMITIVE_EXPORT
    #  elif defined( PRIMITIVE_LIBRARY )
    #    define PRIMITIVE_EXPORT   __declspec(dllexport)
    #  else
    #    define PRIMITIVE_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define PRIMITIVE_EXPORT
#endif  

#endif
