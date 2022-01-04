#pragma once
#include <windows.h>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <iostream>
class MHandleControl :public osgGA::GUIEventHandler
{
public:
	MHandleControl();
	~MHandleControl();
protected:
	//重写handle函数
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
public:
	//获取线段与几何体交点
	static void getInterSections(osg::ref_ptr<osg::Group> group, osg::Vec3 vBegin, osg::Vec3 vEnd, osg::ref_ptr<osg::Group> &root);
};

