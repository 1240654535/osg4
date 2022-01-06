/**************************************************************************************************
* @file name 文件名:Callback.h
* @note 描述：回调更新
* @author 作者：z00105
* @data 创建时间：2020 -12 -10
**************************************************************************************************/
#ifndef MODEL_CALLBACK_H
#define	MODEL_CALLBACK_H

#include <osg/Node>
#include <osg/NodeCallback>
#include <CommonLib/Callback/Export.h>
#include <osg/MatrixTransform>

/**
* @class 类名：CModelCallback
* @brief 简要说明：模型回调示例，每次回调增加dAngle角度
* @note详细说明：
* @author 作者：z00105
*/
class CALLBACK_EXPORT CModelCallback : public osg::NodeCallback
{
public:
	CModelCallback();

	~CModelCallback();

	/** Callback method called by the NodeVisitor when visiting a node.*/
	virtual void operator()(osg::Node* pNode, osg::NodeVisitor* pNv);

protected:
	double dAngle;
};

/**
* @class 类名：CModelCallbackNode
* @brief 简要说明：CModelCallback的应用
* @note详细说明：
* @author 作者：z00105
*/
class CALLBACK_EXPORT CModelCallbackNode : public osg::MatrixTransform
{
public:
	CModelCallbackNode();
	~CModelCallbackNode();
};

#endif //MODEL_CALLBACK_H