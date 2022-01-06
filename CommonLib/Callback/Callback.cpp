#include "Callback.h"
#include <osgDB/ReadFile>
#include "osg/CullFace"

CModelCallback::CModelCallback()
	:osg::NodeCallback()
	,dAngle(0.0)
{

}

CModelCallback::~CModelCallback()
{

}

void CModelCallback::operator()(osg::Node* pNode, osg::NodeVisitor* pNv)
{
	//转为矩阵变换节点
	osg::ref_ptr<osg::MatrixTransform> rpMt = dynamic_cast<osg::MatrixTransform*>(pNode);
	if (rpMt.valid())
	{
		osg::Matrix mtRotate;
		mtRotate.makeRotate(dAngle,osg::Z_AXIS);//绕z轴旋转dAngle角度
		rpMt->setMatrix(mtRotate);//设置矩阵
		dAngle+=0.01;
	}
	traverse(pNode,pNv);//继续遍历
}

CModelCallbackNode::CModelCallbackNode()
{
	osg::ref_ptr<osg::Node> rpNode = osgDB::readNodeFile("cow.osg");
	//正面剔除
// 	osg::ref_ptr<osg::CullFace> cullface=new osg::CullFace(osg::CullFace::FRONT);
// 	rpNode->getOrCreateStateSet()->setAttribute(cullface.get());
// 	rpNode->getOrCreateStateSet()->setMode(GL_CULL_FACE,osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
 	osg::ref_ptr<CModelCallback> rpCallback = new CModelCallback;
	addChild(rpNode.get());
	setUpdateCallback(rpCallback.get() );//添加更新回调
}

CModelCallbackNode::~CModelCallbackNode()
{

}
