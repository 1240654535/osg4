#include "MModelObject.h"
#include "Common/Common.h"
MModelObject::MModelObject(const string & strPath)
{
	osg::ref_ptr<osg::Node> rpNode = FeCommon::readNode(strPath);
	this->addChild(rpNode.get());
}

MModelObject::MModelObject(osg::Node * pNode)
{
	this->addChild(pNode);
}

MModelObject::~MModelObject()
{
}
