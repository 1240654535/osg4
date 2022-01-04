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
	/*dynamic_cast用于类继承层次间的指针或引用转换。主要还是用于执行“安全的向下转型（safe downcasting）”，
	也即是基类对象的指针或引用转换为同一继承层次的其他指针或引用。
	至于“先上转型”（即派生类指针或引用类型转换为其基类类型），本身就是安全的，
	尽管可以使用dynamic_cast进行转换，但这是没必要的， 普通的转换已经可以达到目的，毕竟使用dynamic_cast是需要开销的。*/
	osg::ref_ptr<osgViewer::Viewer> rpViewer = dynamic_cast<osgViewer::Viewer*>(&aa);//事件适配器转换成viewer
	if (!rpViewer.valid())
	{
		return false;
	}
	switch (ea.getEventType())//事件类型
	{
		case osgGA::GUIEventAdapter::KEYDOWN://按键按下
		{
			switch (ea.getKey())//选择按键
			{
			case osgGA::GUIEventAdapter::KEY_I://当按下按钮I
			{
				static bool sg_bState = false;//静态变量，控制显隐状态

				sg_bState = !sg_bState;//状态取反

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
		case osgGA::GUIEventAdapter::PUSH://鼠标按下
		{
			switch (ea.getButton())//选择按键
			{
				case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON://左键
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
//设置线宽
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
//绘制线
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
//绘制星球
osg::ref_ptr<osg::Geode> DrawPlanet1(float radius, osg::Vec3 v) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//精细度
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	//设置精细度
	hints->setDetailRatio(1.1f);
	//创建球体
	osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(v, radius);
	osg::ref_ptr<osg::ShapeDrawable> draw = new osg::ShapeDrawable(sphere, hints);
	//draw->setColor(osg::Vec4(1, 0, 0, 1));
	//SetColor(draw, osg::Vec4(0.1, 0.5, 0.1, 1));
	geode->addDrawable(draw);
	//setTexture(geode);
	return geode;
}
//获取线段与几何体交点
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