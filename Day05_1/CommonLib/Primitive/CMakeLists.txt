SET(OUT_NAME Primitive)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(APPLICATION_DIR ${CMAKE_SOURCE_DIR}/CommonLib/Primitive)

set(CMAKE_AUTOMOC ON)

file(GLOB SRC ${APPLICATION_DIR}/*.*)
SOURCE_GROUP(Src FILES ${SRC})

if(${BUILD_SHARED_LIBS} STREQUAL "On")
    add_library(
    	${OUT_NAME} SHARED 
    	${SRC}
		)
    ADD_DEFINITIONS(-DPRIMITIVE_LIBRARY)
	#说明1.DPRIMITIVE_LIBRARY中PRIMITIVE为库名称
else()
    add_library(
    	${OUT_NAME} STATIC 
    	${SRC}
    	)
    ADD_DEFINITIONS(-DPRIMITIVE_LIBRARY_STATIC)
	#说明2.DPRIMITIVE_LIBRARY_STATIC中PRIMITIVE为库名称
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
	ListWidget
	MainWindow
	)
else()
target_link_libraries(
    ${OUT_NAME}
    ${QT_LIBRARIES}
	${OPENSCENEGRAPH_LIBRARIES}
	Common
	ListWidget
	MainWindow
	)
endif()