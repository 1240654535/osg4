#include <windows.h>
#include "Common/Common.h"
#include "ModelObject.h"
CModelObject::CModelObject(const string& strPath)
{
	osg::ref_ptr<osg::Node> rpNode = FeCommon::readNode(strPath);
	this->addChild(rpNode.get());
}

CModelObject::CModelObject( osg::Node* pNode )
{
	this->addChild(pNode); 
}

CModelObject::~CModelObject()
{

}

