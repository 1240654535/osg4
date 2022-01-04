#include <CommonLib/Common/Common.h>
#include <CommonLib/ListWidget/ModelObject.h>
CModelObject::CModelObject(const QString& strPath)
{
	osg::ref_ptr<osg::Node> rpNode = FeCommon::readNode(strPath.toStdString());
	this->addChild(rpNode.get());
}

CModelObject::CModelObject( osg::Node* pNode )
{
	this->addChild(pNode);
}

CModelObject::~CModelObject()
{

}

