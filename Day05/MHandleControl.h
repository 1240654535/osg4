#pragma once
#include <windows.h>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <iostream>

#include "MModelObject.h"
#include <osgFX/Scribe>
#include <EventHandle/Export.h>
#include "osgGA/GUIEventHandler"
#include "osgGA/GUIEventAdapter"
#include "osgGA/GUIActionAdapter"
#include "MEventConnect.h"
/*
* @class ������CHandleControl
* @brief ��Ҫ˵�����Զ����¼�����
* @note��ϸ˵����
*/

class EVENTHANDLE_EXPORT MHandleControl :
	public osgGA::GUIEventHandler
{
public:
	MHandleControl();
	~MHandleControl();

	/**
	  * @brief ��Ҫ˵��������ʱ������ָ��
	  * @note ��ϸ˵����
	  * @param pEventConnect [in]��
	  * @return ����ֵ�Լ�˵����
	*/
	void setEventConnect(MEventConnect* pEventConnect);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
	MEventConnect* m_pEventConnect;//�¼�����ָ��

};

