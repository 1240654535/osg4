/**************************************************************************************************
* @file name 文件名:EventHandle.h
* @note 描述：事件控制
* @author 作者：z00105
* @data 创建时间：2020 -12 -10
**************************************************************************************************/
#include <windows.h>
#include <EventHandle/Export.h>
//#include "osgGA/GUIEventHandler"
//#include "osgGA/GUIEventAdapter"
//#include "osgGA/GUIActionAdapter"
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include "EventConnect.h"

/*
* @class 类名：CHandleControl
* @brief 简要说明：自定义事件处理
* @note详细说明：
* @author 作者：z00105
*/

class EVENTHANDLE_EXPORT CHandleControl : public osgGA::GUIEventHandler
{
public:
	CHandleControl();
	~CHandleControl();

	/**
	  * @brief 简要说明：设置时间连接指针
	  * @note 详细说明：
	  * @param pEventConnect [in]：
	  * @return 返回值以及说明：
	*/
	void setEventConnect(CEventConnect* pEventConnect);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

protected:
	CEventConnect* m_pEventConnect;//事件传递指针
};