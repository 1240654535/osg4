#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H
#include <windows.h>
#include <string>
#include <osg/MatrixTransform>
using namespace std;
class CModelObject : public osg::MatrixTransform
{
public:
	CModelObject(const string& strPath);

	CModelObject(osg::Node* pNode);

	~CModelObject();

};
#endif MODEL_OBJECT_H