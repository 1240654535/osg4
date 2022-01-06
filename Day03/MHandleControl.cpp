#include "MHandleControl.h"
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/LineWidth>
using namespace std;
MHandleControl::MHandleControl() {

}
MHandleControl::MHandleControl(osg::ref_ptr<osg::Switch> &switchs)
{
	this->m_switchs = switchs;
}

MHandleControl::~MHandleControl()
{
}
//�����߿�
void setLineWidth1(float nWidth, osg::ref_ptr<osg::Geometry>& geom)
{
	osg::ref_ptr<osg::StateSet> stateset = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth(nWidth);
	stateset->setAttribute(lineWidth);
}
bool MHandleControl::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
	/*dynamic_cast������̳в�μ��ָ�������ת������Ҫ��������ִ�С���ȫ������ת�ͣ�safe downcasting������
	Ҳ���ǻ�������ָ�������ת��Ϊͬһ�̳в�ε�����ָ������á�
	���ڡ�����ת�͡�����������ָ�����������ת��Ϊ��������ͣ���������ǰ�ȫ�ģ�
	���ܿ���ʹ��dynamic_cast����ת����������û��Ҫ�ģ� ��ͨ��ת���Ѿ����ԴﵽĿ�ģ��Ͼ�ʹ��dynamic_cast����Ҫ�����ġ�*/
	osg::ref_ptr<osgViewer::View> view = dynamic_cast<osgViewer::View*>(&aa);//�¼�������ת����view
	if (!view.valid())
	{
		return false;
	}
	switch (ea.getEventType())//�¼�����
	{
		case osgGA::GUIEventAdapter::KEYDOWN://��������
		{
			switch (ea.getKey())//ѡ�񰴼�
			{
			case osgGA::GUIEventAdapter::KEY_5://�����°�ťI
			{

				//static bool sg_bState = false;//��̬��������������״̬
				int count = view->getSceneData()->asGroup()->getNumChildren();
				count--;
				view->getSceneData()->asGroup()->getChild(count)->asSwitch()->setValue(0, ismask);
				ismask = !ismask;
				/*
				rpViewer->getSceneData()->asGroup()->getChild(count)->asSwitch()->setValue(0,0);*/
				//sg_bState = !sg_bState;//״̬ȡ��
				cout << "I" << endl;
			}
			break;
			case osgGA::GUIEventAdapter::KEY_8:
			{
				int count = view->getSceneData()->asGroup()->getNumChildren();
				count--;
			
				osg::ref_ptr<osg::StateSet> stateset = view->getSceneData()->asGroup()->getChild(count)->asGeometry()->getOrCreateStateSet();
				if (m_lineWidth > 1)
				{
					m_lineWidth--;
				}
				osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth(m_lineWidth);
				stateset->setAttribute(lineWidth);
				//osg::ref_ptr<osg::Geometry>  geometry = dynamic_cast<osg::Geometry*>(view->getSceneData()->asGroup()->getChild(count));
			
	
			}
			break;
			case osgGA::GUIEventAdapter::KEY_9:
			{
				int count = view->getSceneData()->asGroup()->getNumChildren();
				count--;
				osg::ref_ptr<osg::Geometry> geometry = view->getSceneData()->asGroup()->getChild(count)->asGeometry();

				m_lineWidth++;

				setLineWidth1(m_lineWidth, geometry);
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
					pink(view, ea.getX(), ea.getY());
				}
				std::cout << "PUSH test!1" << std::endl;
				break;
				
				default:
					break;
			}	
		}
		case osgGA::GUIEventAdapter::DRAG:
			std::cout << "DRAG test!" << std::endl;
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			std::cout << "RELEASE test!" << std::endl;
			break;
		default:
			break;
	}
	return false;
}
//bool MHandleControl::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa, osg::ref_ptr<osg::Switch>& switchs)
//{
//	return false;
//}

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
	draw->setColor(osg::Vec4(1, 0, 0, 1));
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
			root->addChild(DrawPlanet1(0.2, osg::Vec3(iter->getLocalIntersectPoint().x(), iter->getLocalIntersectPoint().y(), iter->getLocalIntersectPoint().z())));
		}
	}

}
//����ѡȡ�¼�������
void MHandleControl::pink(osg::ref_ptr<osgViewer::View> view, float x, float y)
{
	osg::ref_ptr<osg::Node> node  = new osg::Node();
	osg::ref_ptr<osg::Group> parent = new osg::Group();
	// ������Ļ�ͳ����ཻ�Ľ��������intersectioins��
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(x,y,intersections))
	{
		//��λ����һ���ཻ�Ľڵ�
		osgUtil::LineSegmentIntersector::Intersections::iterator it = intersections.begin();
		//��������ڵ�
		if (!it->nodePath.empty())
		{
			/*NodePath ����osg::NodeΪԪ�ص�vector������osg::NodePathList����NodePathΪԪ�ص�����������˵�����£�
			NodePath��ʾһ��·�������е�ÿ��Ԫ�ر�ʾ·���е�ÿ���ڵ㣬����ӡ���������--->�ʹ���������ġ���������--->�ʹ�����һ��·����
			·���е�ÿ���ڵ���൱������·���еĹ���վ�����磺���������ֵ��ʹ�Ҫ�������찲�����������찲�Ŷ��������ʹ�����������վ��
			����ġ��찲�����������찲�Ŷ��������ʹ�������NodePath�е�Node��
			osg::NodePathList��ʾ���������ֵ��ʹ�������·���ļ��ϣ���Ϊ���������ֵ��ʹ������кܶ���·�ɵ���
			���磺�ӡ���������--->���ҽ�---->������-->������->�ʹ�����*/
			osg::NodePath nodePath = it->nodePath;
			node = (nodePath.size() >= 1) ? nodePath[(nodePath.size() - 1)] : 0;
			node->setNodeMask(!ismask);
			//node->asSwitch()->setValue(0, ismask);
			ismask = !ismask;
		}
		else
		{
			
		}
	}
}

