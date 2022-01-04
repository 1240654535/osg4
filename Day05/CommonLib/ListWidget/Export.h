#ifndef LIST_WIDGTE_EXPORT_H
#define LIST_WIDGTE_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( LISTWIDGET_LIBRARY_STATIC )
    #    define LISTWIDGET_EXPORT
    #  elif defined( LISTWIDGET_LIBRARY )
    #    define LISTWIDGET_EXPORT   __declspec(dllexport)
    #  else
    #    define LISTWIDGET_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define LISTWIDGET_EXPORT
#endif  

#endif
