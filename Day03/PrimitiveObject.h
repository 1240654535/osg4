#ifndef PRIMITIVE_OBJECT_H
#define PRIMITIVE_OBJECT_H

#include <windows.h>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/Texture2D>
#include "Common.h"

class CPrimitiveObject : public osg::Group
{
public:
	CPrimitiveObject();

	~CPrimitiveObject();

	void setPrimitive(osg::PrimitiveSet::Mode mode);

	void setPointSize(int nSize);

	void setLineWidth(int nWidth);

	void setColor(const osg::Vec4& vecColor);

	void setTexture(bool bState);

protected:
	osg::ref_ptr<osg::DrawArrays> m_rpDrawArrays;
	osg::ref_ptr<osg::Vec3Array>  m_rpVertexArray;
	osg::ref_ptr<osg::Geometry>   m_rpGeo;
	osg::ref_ptr<osg::Texture2D>  m_rpTexture;
	double m_dUnit;
};
#endif PRIMITIVE_OBJECT_H