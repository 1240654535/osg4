#ifndef PRIMITIVE_WIDGET_H
#define PRIMITIVE_WIDGET_H
#include <QObject>
#include <QMap>
#include <QVector>
#include <osg/PrimitiveSet>
#include <osg/observer_ptr>
#include <CommonLib/Primitive/Export.h>
class CMainWindow;
class CListWidget;
class CPrimitiveObject;
class PRIMITIVE_EXPORT CPrimitiveWidget : public QObject
{
	Q_OBJECT
public:
	CPrimitiveWidget(CMainWindow* pMainWindow,CListWidget* pListWidget);

	~CPrimitiveWidget();

protected:
	//初始化映射表
	void initMap();

	//初始化控件
	void initWidget();

	//初始化图元
	void initPrimitive();

	protected slots:
		//设置图元类型
		void slotType(const QString & strType);

		//设置点大小
		void slotPoint(int nSize);

		//设置线宽
		void slotLine(int nWidth);

		//设置颜色
		void slotColor(const QString & strType);

		//设置纹理
		void slotTexture(int nState);

protected:
	CMainWindow* m_pMainWindow;//主窗口
	CListWidget* m_pListWidget;//列表
	osg::observer_ptr<CPrimitiveObject> m_opPrimitiveObject;//图元指针
	QVector<QString> m_vecPrimitive;//图元容器
	QMap<QString,osg::PrimitiveSet::Mode> m_mapPrimitive;//图元名与类型映射
	QVector<QString> m_vecColor;//颜色
	QMap<QString,osg::Vec4> m_mapColor;//颜色映射
};
#endif PRIMITIVE_WIDGET_H