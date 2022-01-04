SET(OUT_NAME ListWidget)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(APPLICATION_DIR ${CMAKE_SOURCE_DIR}/CommonLib/ListWidget)

set(CMAKE_AUTOMOC ON)

file(GLOB SRC ${APPLICATION_DIR}/*.*)
SOURCE_GROUP(Src FILES ${SRC})

if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    	${SRC}
		)
    ADD_DEFINITIONS(-DLISTWIDGET_LIBRARY)
	#说明1.DLISTWIDGET_LIBRARY中LISTWIDGET为库名称
else()
    add_library(
    	${OUT_NAME} STATIC 
    	${SRC}
    	)
    ADD_DEFINITIONS(-DLISTWIDGET_LIBRARY_STATIC)
	#说明2.DLISTWIDGET_LIBRARY_STATIC中LISTWIDGET为库名称
endif()
#说明1.此处添加依赖库
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
	MainWindow
	)
else()
target_link_libraries(
    ${OUT_NAME}
    ${QT_LIBRARIES}
	${OPENSCENEGRAPH_LIBRARIES}
	Common
	MainWindow
	)
endif()