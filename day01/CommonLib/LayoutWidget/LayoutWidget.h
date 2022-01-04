/**************************************************************************************************
* @file name 文件名:LayoutWidget.h
* @note 描述：布局窗口
* @author 作者：z00105
* @data 创建时间：2020 -12 -21
**************************************************************************************************/
#ifndef LAYOUT_WIDGET_H
#define LAYOUT_WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <CommonLib/LayoutWidget/Export.h>

#define ITEM_SIZE_WITH 80
#define ITEM_SIZE_HIGHTH 80
class CMainWindow;


/**
* @class 类名：CLayoutWidgetItem
* @brief 简要说明：布局项类
* @note详细说明：存储布局自定义信息、发送信号
* @author 作者：z00105
*/
class CLayoutWidgetItem : public QLabel
{
	Q_OBJECT
public:
	CLayoutWidgetItem(QString qstrInfo = "");

	~CLayoutWidgetItem();

	/**
	  * @brief 简要说明：设置标签信息
	  * @note 详细说明：
	  * @param qstrInfo [in]：标签信息
	  * @return ：
	*/
	void setUserInfo(QString qstrInfo);
protected:
	/**
	  * @brief 简要说明：虚函数，鼠标按下事件会进入
	  * @note 详细说明：
	  * @param QMouseEvent [in]：鼠标事件
	  * @return ：
	*/
	virtual void mousePressEvent(QMouseEvent *);
signals:
	void signalClicked(QString qstrInfo);

protected:
	QString m_qstrUserInfo;//标签信息
};

/**
* @class 类名：CLayoutWidget
* @brief 简要说明：布局窗口类
* @note详细说明：提供具有可扩展、拉伸的布局界面
* @author 作者：z00105
*/
class LAYOUT_WIDGET_EXPORT CLayoutWidget : public QWidget
{
	Q_OBJECT
public:
	CLayoutWidget(CMainWindow* pMainWindow);

	~CLayoutWidget();

	/**
	  * @brief 简要说明：添加项目
	  * @note 详细说明：传入添加对象的指针
	  * @param 参数1 [in]：QWidget*
	  * @return 返回值以及说明：bool
	*/
	bool addWidgetItem(CLayoutWidgetItem* pWidget);
protected:
	virtual void resizeEvent(QResizeEvent *);

	/**
	  * @brief 简要说明：重新排列项目
	  * @note 详细说明：
	  * @return 返回值以及说明：bool
	*/
	bool reSortWidgetItem();
	protected slots:
		void slotShowfUserInfo(QString qstrInfo);
protected:
	std::vector<CLayoutWidgetItem* > m_vecItems;
	QGridLayout*		  m_pGrid;
};
#endif LAYOUT_WIDGET_H