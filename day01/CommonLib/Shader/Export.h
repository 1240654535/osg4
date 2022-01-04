#ifndef SHADER_EXPORT_H
#define SHADER_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( SHADER_LIBRARY_STATIC )
    #    define SHADER_EXPORT
    #  elif defined( SHADER_LIBRARY )
    #    define SHADER_EXPORT   __declspec(dllexport)
    #  else
    #    define SHADER_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define SHADER_EXPORT
#endif  

#endif
