#ifndef HUDRTT_EXPORT_H
#define HUDRTT_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( HUDRTT_LIBRARY_STATIC )
    #    define HUDRTT_EXPORT
    #  elif defined( HUDRTT_LIBRARY )
    #    define HUDRTT_EXPORT   __declspec(dllexport)
    #  else
    #    define HUDRTT_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define HUDRTT_EXPORT
#endif  

#endif
