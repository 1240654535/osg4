#include <windows.h>
#include "MVisitor.h"
#include <iostream>
MVisitor::MVisitor(TraversalMode eMode /* = TRAVERSE_ALL_CHILDREN*/)
	:osg::NodeVisitor(eMode)
{

}

MVisitor::~MVisitor()
{

}

void MVisitor::apply(osg::Node& pNode)
{
	addCount2Map("Node");
	traverse(pNode);
}

void MVisitor::apply(osg::Group& pGroup)
{
	addCount2Map("Group");
	traverse(pGroup);
}

void MVisitor::apply(osg::MatrixTransform& pMt)
{
	addCount2Map("MatrixTransform");
	traverse(pMt);
}

void MVisitor::apply(osg::Geode& node)
{
	addCount2Map("Geode");
	traverse(node);
}
void MVisitor::apply(osg::Geometry& pGeometry)
{
	addCount2Map("Geometry");
	traverse(pGeometry);
}


void MVisitor::addCount2Map(std::string strNodeType)
{
	if (!m_mapType2Count.count(strNodeType))
	{
		m_mapType2Count[strNodeType] = 1;
	}
	else
	{
		m_mapType2Count[strNodeType] += 1;
	}
}

void MVisitor::printMap()
{
	auto itr = m_mapType2Count.begin();
	for (; itr != m_mapType2Count.end(); itr++)
	{
		std::cout << itr->first << " Counts:" << itr->second << std::endl;
	}
}

