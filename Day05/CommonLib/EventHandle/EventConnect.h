/**************************************************************************************************
* @file name 文件名:EventConnect.h
* @note 描述：事件通信
* @author 作者：z00105
* @data 创建时间：2020 -12 -10
**************************************************************************************************/
#ifndef EVENT_CONNECT_H
#define EVENT_CONNECT_H
#include <windows.h>
#include "Export.h"
#include "Common/Interface.h"
/*
* @class 类名：CEventConnect
* @brief 简要说明：自定义事件处理
* @note详细说明：
* @author 作者：z00105
*/

class EVENTHANDLE_EXPORT CEventConnect
{
public:
	CEventConnect();
	~CEventConnect();

	/**
	  * @brief 简要说明：事件关联
	  * @note 详细说明：将osg的事件与qt的信号槽相关联
	  * @param sEvent [in]：
	  * @return 返回值以及说明：
	*/
	virtual bool eventConnect(BaseInterFace::SEvent sEvent) =0;
};
#endif