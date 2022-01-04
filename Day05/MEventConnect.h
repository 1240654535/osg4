#pragma once
#ifndef EVENT_CONNECT_H
#define EVENT_CONNECT_H
#include <windows.h>
#include <EventHandle/Export.h>
#include <Common/Interface.h>
class EVENTHANDLE_EXPORT MEventConnect
{
public:
	MEventConnect();
	~MEventConnect();

	/**
	  * @brief 简要说明：事件关联
	  * @note 详细说明：将osg的事件与qt的信号槽相关联
	  * @param sEvent [in]：
	  * @return 返回值以及说明：
	*/
	virtual bool eventConnect(BaseInterFace::SEvent sEvent) = 0;
};
#endif
