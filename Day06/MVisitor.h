#pragma once
/**************************************************************************************************
* @file name �ļ���:Visitor.h
* @note ������������
* @author ���ߣ�z00105
* @data ����ʱ�䣺2020 -12 -10
**************************************************************************************************/

#include <osg/NodeVisitor>
#include <windows.h>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>

class MVisitor:public osg::NodeVisitor
{
public:
	MVisitor(TraversalMode eMode = TRAVERSE_ALL_CHILDREN);
	~MVisitor();

	virtual void apply(osg::Node& node);
	virtual void apply(osg::Group& group);
	virtual void apply(osg::MatrixTransform& mt);
	virtual void apply(osg::Geode& node);
	virtual void apply(osg::Geometry& geometry);

	void printMap();
protected:
	void addCount2Map(std::string strNodeType);

protected:
	std::map<std::string, int> m_mapType2Count;
};

