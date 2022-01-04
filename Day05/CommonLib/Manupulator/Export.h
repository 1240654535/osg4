#ifndef MANUPULATOR_EXPORT_H
#define MANUPULATOR_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( MANUPULATOR_LIBRARY_STATIC )
    #    define MANUPULATOR_EXPORT
    #  elif defined( MANUPULATOR_LIBRARY )
    #    define MANUPULATOR_EXPORT   __declspec(dllexport)
    #  else
    #    define MANUPULATOR_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define MANUPULATOR_EXPORT
#endif  

#endif
