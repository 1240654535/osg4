#include "MHandleControl.h"
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/LineWidth>
using namespace std;
MHandleControl::MHandleControl()
{
}

MHandleControl::~MHandleControl()
{
}

bool MHandleControl::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
	/*dynamic_cast������̳в�μ��ָ�������ת������Ҫ��������ִ�С���ȫ������ת�ͣ�safe downcasting������
	Ҳ���ǻ�������ָ�������ת��Ϊͬһ�̳в�ε�����ָ������á�
	���ڡ�����ת�͡�����������ָ�����������ת��Ϊ��������ͣ���������ǰ�ȫ�ģ�
	���ܿ���ʹ��dynamic_cast����ת����������û��Ҫ�ģ� ��ͨ��ת���Ѿ����ԴﵽĿ�ģ��Ͼ�ʹ��dynamic_cast����Ҫ�����ġ�*/
	osg::ref_ptr<osgViewer::Viewer> rpViewer = dynamic_cast<osgViewer::Viewer*>(&aa);//�¼�������ת����viewer
	if (!rpViewer.valid())
	{
		return false;
	}
	switch (ea.getEventType())//�¼�����
	{
		case osgGA::GUIEventAdapter::KEYDOWN://��������
		{
			switch (ea.getKey())//ѡ�񰴼�
			{
			case osgGA::GUIEventAdapter::KEY_I://�����°�ťI
			{
				static bool sg_bState = false;//��̬��������������״̬

				sg_bState = !sg_bState;//״̬ȡ��

			}
			break;
			case osgGA::GUIEventAdapter::KEY_K:
			{

			}
			break;
			default:
				break;
			}
			std::cout << "KEYDOWN test!" << std::endl;
		}
		break;
		case osgGA::GUIEventAdapter::PUSH://��갴��
		{
			switch (ea.getButton())//ѡ�񰴼�
			{
				case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON://���
				{

				}
				std::cout << "PUSH test!123123" << std::endl;
				break;
				
				default:
					break;
			}	
		}
		case osgGA::GUIEventAdapter::DRAG:
			std::cout << "DRAG test!123123" << std::endl;
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			std::cout << "RELEASE test!123123" << std::endl;
			break;
		default:
			break;
	}
	return false;
}
//�����߿�
void setLineWidth1(float nWidth, osg::ref_ptr<osg::Geometry>& geom)
{
	//osg::ref_ptr<osg::LineWidth> rpLineWidth = dynamic_cast<osg::LineWidth*>(geom->getOrCreateStateSet()->getAttribute(osg::StateAttribute::LINEWIDTH));
	//if (rpLineWidth.valid())
	//{
	//	rpLineWidth->setWidth(nWidth);
	//}
	osg::ref_ptr<osg::StateSet> stateset = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> lineWid = new osg::LineWidth(nWidth);
	stateset->setAttribute(lineWid);
}
//������
osg::ref_ptr<osg::Geode> DrawLines1(osg::ref_ptr<osg::Vec3Array> v ) {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(v.get());
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));
	setLineWidth1(5, geom);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom);
	return geode;
}
//��������
osg::ref_ptr<osg::Geode> DrawPlanet1(float radius, osg::Vec3 v) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//��ϸ��
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	//���þ�ϸ��
	hints->setDetailRatio(1.1f);
	//��������
	osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(v, radius);
	osg::ref_ptr<osg::ShapeDrawable> draw = new osg::ShapeDrawable(sphere, hints);
	//draw->setColor(osg::Vec4(1, 0, 0, 1));
	//SetColor(draw, osg::Vec4(0.1, 0.5, 0.1, 1));
	geode->addDrawable(draw);
	//setTexture(geode);
	return geode;
}
//��ȡ�߶��뼸���彻��
void MHandleControl::getInterSections(osg::ref_ptr<osg::Group> group, osg::Vec3 vBegin, osg::Vec3 vEnd, osg::ref_ptr<osg::Group>& root) {
	//osgUtil::LineSegmentIntersector::Intersections intersections = new osgUtil::LineSegmentIntersector::Intersections(vBegin, vBegin);
	osg::ref_ptr<osgUtil::LineSegmentIntersector> lineSegmentIntersector = new osgUtil::LineSegmentIntersector(vBegin, vEnd);
	osg::ref_ptr<osgUtil::IntersectionVisitor> IntersectionVisitor = new osgUtil::IntersectionVisitor(lineSegmentIntersector);
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back(vBegin);
	v->push_back(vEnd);
	root->addChild(DrawLines1(v));
	group->accept(*IntersectionVisitor.get());
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (lineSegmentIntersector->containsIntersections())
	{
		intersections = lineSegmentIntersector->getIntersections();
		osgUtil::LineSegmentIntersector::Intersections::iterator iter;
		for (iter = intersections.begin(); iter != intersections.end(); iter++)
		{
			std::cout << "x:" << iter->getWorldIntersectPoint().x() << "    y:" << iter->getWorldIntersectPoint().y() << "    z:" << iter->getWorldIntersectPoint().z() << std::endl;
			DrawPlanet1(20, osg::Vec3(iter->getLocalIntersectPoint().x(),iter->getLocalIntersectPoint().y(),iter->getLocalIntersectPoint().z()));
		}
	}

}