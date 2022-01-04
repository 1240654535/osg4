#ifndef MAINWINDOW_EXPORT_H
#define MAINWINDOW_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( MAINWINDOW_LIBRARY_STATIC )
    #    define MAINWINDOW_EXPORT
    #  elif defined( MAINWINDOW_LIBRARY )
    #    define MAINWINDOW_EXPORT   __declspec(dllexport)
    #  else
    #    define MAINWINDOW_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define MAINWINDOW_EXPORT
#endif  

#endif
