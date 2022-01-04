SET(OUT_NAME MainWindow)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(APPLICATION_DIR ${CMAKE_SOURCE_DIR}/CommonLib/MainWindow)

file(GLOB SRC ${APPLICATION_DIR}/*.*)
SOURCE_GROUP(Src FILES ${SRC})

if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    	${SRC}
		)
    ADD_DEFINITIONS(-DMAINWINDOW_LIBRARY)
	#说明1.DMAINWINDOW_LIBRARY中MAINWINDOW为库名称
else()
    add_library(
    	${OUT_NAME} STATIC 
    	${SRC}
    	)
    ADD_DEFINITIONS(-DMAINWINDOW_LIBRARY_STATIC)
	#说明2.DMAINWINDOW_LIBRARY_STATIC中MAINWINDOW为库名称
endif()
#说明3.此处添加依赖库	
if (Qt5Widgets_FOUND)
target_link_libraries(
    ${OUT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::OpenGL
    Qt5::Widgets
    Qt5::Xml
	${OPENSCENEGRAPH_LIBRARIES}
	Common
	)
else()
target_link_libraries(
    ${OUT_NAME}
    ${QT_LIBRARIES}
	${OPENSCENEGRAPH_LIBRARIES}
	Common
	)
endif()