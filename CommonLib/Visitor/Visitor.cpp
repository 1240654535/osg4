#include <CommonLib/Visitor/Visitor.h> 
#include <iostream>
CModelVisitor::CModelVisitor(TraversalMode eMode /* = TRAVERSE_ALL_CHILDREN*/)
	:osg::NodeVisitor(eMode)
{

}

CModelVisitor::~CModelVisitor()
{

}

void CModelVisitor::apply(osg::Node& pNode)
{
	addCount2Map("Node");
	traverse(pNode);
}

void CModelVisitor::apply(osg::Group& pGroup)
{
	addCount2Map("Group");
	traverse(pGroup);
}

void CModelVisitor::apply(osg::MatrixTransform& pMt)
{
	addCount2Map("MatrixTransform");
	traverse(pMt);
}

void CModelVisitor::apply(osg::Geode& node)
{
	addCount2Map("Geode");
	traverse(node);
}


void CModelVisitor::apply(osg::Geometry& pGeometry)
{
	addCount2Map("Geometry");
	traverse(pGeometry);
}


void CModelVisitor::addCount2Map(std::string strNodeType)
{
	if (!m_mapType2Count.count(strNodeType))
	{
		m_mapType2Count[strNodeType] = 1;
	}
	else
	{
		m_mapType2Count[strNodeType] +=1;
	}
}

void CModelVisitor::printMap()
{
	auto itr = m_mapType2Count.begin();
	for (;itr!=m_mapType2Count.end();itr++)
	{
		std::cout<<itr->first<<" Counts:"<<itr->second<<std::endl;
	}
}

