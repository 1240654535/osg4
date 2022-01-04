#ifndef LAYOUT_WIDGET_EXPORT_H
#define LAYOUT_WIDGET_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( LAYOUT_WIDGET_LIBRARY_STATIC )
    #    define LAYOUT_WIDGET_EXPORT
    #  elif defined( LAYOUT_WIDGET_LIBRARY )
    #    define LAYOUT_WIDGET_EXPORT   __declspec(dllexport)
    #  else
    #    define LAYOUT_WIDGET_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define LAYOUT_WIDGET_EXPORT
#endif  

#endif
