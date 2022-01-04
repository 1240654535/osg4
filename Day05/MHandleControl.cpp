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
			if (m_pEventConnect)//�¼�����
			{
				static bool sg_bState = false;//��̬��������������״̬
				BaseInterFace::SEvent sEvent;
				sEvent.bState = sg_bState;
				m_pEventConnect->eventConnect(sEvent);//������Ϣ��qt����
				sg_bState = !sg_bState;//״̬ȡ��
			}
		}
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
			osgUtil::LineSegmentIntersector::Intersections intersections;//��ײ���
			if (rpViewer->computeIntersections(ea.getX(), ea.getY(), intersections))//viewer�����нڵ�����Ļ������ײ���
			{
				osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();//��ȡ��ײ�����
				osg::NodePath& nodePath = intersection.nodePath;//��ȡ�ڵ㼯��
				//��ȡѡ�е�����
				MModelObject* pNode = NULL;
				auto itrNode = nodePath.begin();//�����ڵ�
				for (; itrNode != nodePath.end(); itrNode++)
				{
					pNode = dynamic_cast<MModelObject*>(*itrNode);//��̬ת��
					if (pNode)//��ע���öο���ΪCModelObject�ĳ�Ա������Ϊ������ʾ�������ڴ˴�
					{
						osg::ref_ptr< osgFX::Scribe> rpScribe = NULL;//�����ڵ�
						auto pChildNode = pNode->getChild(0);//
						rpScribe = dynamic_cast<osgFX::Scribe*>(pChildNode);//�Ƿ��Ѿ��Ǹ����ڵ�
						if (!rpScribe)
						{
							//������ʾ
							rpScribe = new osgFX::Scribe;
							rpScribe->addChild(pChildNode);
							pNode->replaceChild(pChildNode, rpScribe.get());
						}
						else
						{
							//ȡ������
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
