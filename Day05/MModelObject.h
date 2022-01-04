#pragma once
#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H
#include <windows.h>
#include <osg/MatrixTransform>
#include <string>
using namespace std;
class MModelObject :
	public osg::MatrixTransform
{
public:
	MModelObject(const string& strPath);

	MModelObject(osg::Node* pNode);

	~MModelObject();

};

#endif MODEL_OBJECT_H