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
	  * @brief ��Ҫ˵�����¼�����
	  * @note ��ϸ˵������osg���¼���qt���źŲ������
	  * @param sEvent [in]��
	  * @return ����ֵ�Լ�˵����
	*/
	virtual bool eventConnect(BaseInterFace::SEvent sEvent) = 0;
};
#endif
