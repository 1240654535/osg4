#ifndef PROPERTY_WIDGET_H
#define PROPERTY_WIDGET_H
#include <QWidget>
#include <CommonLib/MainWindow/MainWindow.h>
class CModelObject;
class CPropertyWidget : public QWidget
{
	Q_OBJECT
public:
	CPropertyWidget(CModelObject* pModelObject,QWidget* pParent);

	~CPropertyWidget();

	protected slots:
		void slotTX(double dValue);

		void slotTY(double dValue);

		void slotTZ(double dValue);

		void slotRX(double dValue);

		void slotRY(double dValue);

		void slotRZ(double dValue);

		void slotSX(double dValue);

		void slotSY(double dValue);

		void slotSZ(double dValue);

protected:
	void updateMatrix();

protected:
	CModelObject* m_pModelObject;
	osg::Vec3 m_vecPosition;
	osg::Vec3 m_vecRotation;
	osg::Vec3 m_vecScale;
};
#endif PROPERTY_WIDGET_H