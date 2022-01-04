#ifndef CALLBACK_EXPORT_H
#define CALLBACK_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( CALLBACK_LIBRARY_STATIC )
    #    define CALLBACK_EXPORT
    #  elif defined( CALLBACK_LIBRARY )
    #    define CALLBACK_EXPORT   __declspec(dllexport)
    #  else
    #    define CALLBACK_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define CALLBACK_EXPORT
#endif  

#endif
