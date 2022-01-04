#include "MHandleControl.h"

MHandleControl::MHandleControl()
{
}

MHandleControl::~MHandleControl()
{
}

void MHandleControl::setEventConnect(MEventConnect * pEventConnect)
{
	m_pEventConnect = pEventConnect;
}

bool MHandleControl::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
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
			if (m_pEventConnect)//事件连接
			{
				static bool sg_bState = false;//静态变量，控制显隐状态
				BaseInterFace::SEvent sEvent;
				sEvent.bState = sg_bState;
				m_pEventConnect->eventConnect(sEvent);//发送信息到qt界面
				sg_bState = !sg_bState;//状态取反
			}
		}
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
			osgUtil::LineSegmentIntersector::Intersections intersections;//碰撞结合
			if (rpViewer->computeIntersections(ea.getX(), ea.getY(), intersections))//viewer的所有节点与屏幕坐标碰撞检测
			{
				osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();//获取碰撞检测结果
				osg::NodePath& nodePath = intersection.nodePath;//获取节点集合
				//获取选中的物体
				MModelObject* pNode = NULL;
				auto itrNode = nodePath.begin();//遍历节点
				for (; itrNode != nodePath.end(); itrNode++)
				{
					pNode = dynamic_cast<MModelObject*>(*itrNode);//动态转换
					if (pNode)//备注，该段可作为CModelObject的成员函数，为方便演示而放置在此处
					{
						osg::ref_ptr< osgFX::Scribe> rpScribe = NULL;//高亮节点
						auto pChildNode = pNode->getChild(0);//
						rpScribe = dynamic_cast<osgFX::Scribe*>(pChildNode);//是否已经是高亮节点
						if (!rpScribe)
						{
							//高亮显示
							rpScribe = new osgFX::Scribe;
							rpScribe->addChild(pChildNode);
							pNode->replaceChild(pChildNode, rpScribe.get());
						}
						else
						{
							//取消高亮
							pChildNode = rpScribe->getChild(0);
							//pNode->replaceChild(rpScribe.get(), pChildNode);
							osg::Node::ParentList parentList = rpScribe->getParents();
							for (osg::Node::ParentList::iterator itr = parentList.begin(); itr != parentList.end(); itr++)
							{
								(*itr)->replaceChild(rpScribe.get(), pChildNode);

							}
						}
						break;
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
	std::cout << "PUSH test!" << std::endl;
	break;
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
