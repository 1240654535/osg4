/**************************************************************************************************
* @file name 文件名:MainWindow.h
* @note 描述：主界面
* @author 作者：z00105
* @data 创建时间：2021 -2 -23
**************************************************************************************************/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QBoxLayout>
#include <QTimer>
#include <QWidget>
#include <osgViewer/Viewer>
#include <CommonLib/MainWindow/Export.h>
/**
* @class 类名：CMainWindow
* @brief 简要说明：主窗口显示
* @note详细说明：
* @author 作者：z00105
*/
class MAINWINDOW_EXPORT CMainWindow : public QWidget
{
public:
	/**
	  * @brief 简要说明：主窗口的初始化
	  * @note 详细说明：
	  * @param parent [in]：父窗口
	  * @param f [in]：窗口属性
	*/
	CMainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);

	/**
	  * @brief 简要说明：获取视景器
	  * @note 详细说明：
	  * @return m_rpViewer：场景视景器
	*/
	osgViewer::Viewer* getViewer(){return m_rpViewer.get();}

	/**
	  * @brief 简要说明：获取根节点
	  * @note 详细说明：
	  * @return m_rpRoot：场景根节点
	*/
	osg::Group* getRoot(){return m_rpRoot.get();}

	/**
	  * @brief 简要说明：获取主窗口垂直布局
	  * @note 详细说明：
	  * @return m_pVLayout：主窗口垂直布局
	*/
	QVBoxLayout* getVLayout(){return m_pVLayout;}
	
	/**
	  * @brief 简要说明：获取主窗口水平布局
	  * @note 详细说明：
	  * @return m_pVLayout：主窗口水平布局
	*/
	QHBoxLayout* getHLayout(){return m_pHLayout;}

	/**
	  * @brief 简要说明：视口复位
	  * @note 详细说明：三维窗口的视口回到初始设置的位置
	  * @return ：
	*/
	void home();

protected:
	/**
	  * @brief 简要说明：三维窗口与qt窗口的结合
	  * @note 详细说明：
	  * @param nX [in]：x位置
	  * @param nY [in]：y位置
	  * @param nW [in]：宽度
	  * @param nH [in]：高度
	  * @param strName [in]：窗口名
	  * @param bWindowDecoration [in]：是否装饰
	  * @return QWidget：三维与qt结合的窗口
	*/
	QWidget* createGraphicsWindow( int nX, int nY, int nW, int nH, const std::string& strName="", bool bWindowDecoration=false );

	/**
	  * @brief 简要说明：绘制事件
	  * @note 详细说明：qt的窗口绘制事件，用于三维场景的刷新
	  * @param event [in]：绘制事件
	  * @return 返回值以及说明：
	*/
	virtual void paintEvent( QPaintEvent* event );

protected:
	osg::ref_ptr<osgViewer::Viewer>      m_rpViewer;	//视景器
	osg::ref_ptr<osg::Group>             m_rpRoot;		//根节点
	QVBoxLayout*                         m_pVLayout;	//垂直布局
	QHBoxLayout*                         m_pHLayout;	//水平布局
	QTimer                               m_timer;		//定时器
};
#endif MAIN_WINDOW_H