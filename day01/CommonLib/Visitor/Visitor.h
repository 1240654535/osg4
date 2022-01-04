/**************************************************************************************************
* @file name 文件名:Visitor.h
* @note 描述：遍历器
* @author 作者：z00105
* @data 创建时间：2020 -12 -10
**************************************************************************************************/

#include <CommonLib/Visitor/Export.h> 
#include <osg/NodeVisitor>
#include <CommonLib/Callback/Callback.h>
#include "osg/Geode"
#include "osg/Geometry"

/*
* @class 类名：
* @brief 简要说明：
* @note详细说明：
* @author 作者：z00105
*/

class VISITOR_EXPORT CModelVisitor : public osg::NodeVisitor
{
public:
	CModelVisitor(TraversalMode eMode = TRAVERSE_ALL_CHILDREN);
	~CModelVisitor();

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