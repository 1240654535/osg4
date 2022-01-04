#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H
#include <QString>
#include <osg/MatrixTransform>
class CModelObject : public osg::MatrixTransform
{
public:
	CModelObject(const QString& strPath);

	CModelObject(osg::Node* pNode);

	~CModelObject();

};
#endif MODEL_OBJECT_H