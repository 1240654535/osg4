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
* @class 类名：CHandleControl
* @brief 简要说明：自定义事件处理
* @note详细说明：
*/

class EVENTHANDLE_EXPORT MHandleControl :
	public osgGA::GUIEventHandler
{
public:
	MHandleControl();
	~MHandleControl();

	/**
	  * @brief 简要说明：设置时间连接指针
	  * @note 详细说明：
	  * @param pEventConnect [in]：
	  * @return 返回值以及说明：
	*/
	void setEventConnect(MEventConnect* pEventConnect);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

protected:
	MEventConnect* m_pEventConnect;//事件传递指针

};

