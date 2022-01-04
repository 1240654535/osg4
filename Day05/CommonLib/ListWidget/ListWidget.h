#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H
#include <osg/Node>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>
#include <CommonLib/ListWidget/Export.h>
class CMainWindow;
class LISTWIDGET_EXPORT CListWidget : public QObject
{
	Q_OBJECT

public:
	/**
	* @class 结构体名：SModelInfo
	* @brief 简要说明：添加模型所需信息
	* @note详细说明：bUseLLH决定是否使用vec3LLH
	* @author 作者：z00105
	*/
	struct SModelInfo
	{
		SModelInfo()
		{
			bUseLLH = false;
			vec3Scale = osg::Vec3d(1.0,1.0,1.0);
		}
		bool bUseLLH;			//是否使用经纬高
		osg::Vec3d vec3LLH;		//经纬高
		osg::Vec3d vec3Scale;	//模型缩放比例
		osg::Vec3d vec3Rotate;	//模型姿态
	};

	CListWidget(CMainWindow* pMainWindow);

	~CListWidget();

	/**
	  * @brief 简要说明：添加模型
	  * @note 详细说明：通过路径添加模型
	  * @param strPath [in]：绝对路径或相对data目录的路径
	  * @return ：
	*/
	void addModel(const QString& strPat);

	/**
	  * @brief 简要说明：添加模型
	  * @note 详细说明：模型名称和节点指针添加
	  * @param strName [in]：模型名称
	  * @param pNode [in]：模型节点
	  * @return ：
	*/
	void addModel(const QString& strName,osg::Node* pNode);
	
	/**
	  * @brief 简要说明：改变模型状态
	  * @note 详细说明：显隐控制
	  * @param bState [in]：模型状态
	  * @return ：
	*/
	bool changeModelState(bool bState);
	protected slots:
		/**
		  * @brief 简要说明：显示右键菜单
		  * @note 详细说明：根据位置和选择的对象进行菜单显示
		  * @param pos [in]：位置
		  * @return ：
		*/
		void slotShowMenu(const QPoint &pos);
		
		/**
		  * @brief 简要说明：添加选项
		  * @note 详细说明：添加模型节点
		  * @return ：
		*/
		void slotAdd();
		
		/**
		  * @brief 简要说明：删除选项
		  * @note 详细说明：删除当前选中的列表项和三维场景中的对应节点
		  * @return ：
		*/
		void slotDel();
		
		/**
		  * @brief 简要说明：显示清除菜单
		  * @note 详细说明：
		  * @return ：
		*/
		void slotClear();
		
		/**
		  * @brief 简要说明：显示属性菜单
		  * @note 详细说明：
		  * @return ：
		*/
		void slotProperty();
		
		/**
		  * @brief 简要说明：设置选项对应控制节点的显隐
		  * @note 详细说明：通过选项控制三维场景节点显隐
		  * @param pItem [in]：列表项
		  * @return ：
		*/
		void slotVisible(QListWidgetItem * pItem);
protected:
	void del(int nRow);

protected:
	CMainWindow* m_pMainWindow;//主窗口
	QListWidget* m_pListWidget;//列表控件
	QListWidgetItem* m_pAxesItem;//坐标轴项
	QListWidgetItem* m_pCurItem;//当前项
	QMenu* m_pMenu;//菜单
	QAction* m_pAddAction;//添加动作
	QAction* m_pDelAction;//删除动作
	QAction* m_pClearAction;//清除动作
	QAction* m_pPropertyAction;//属性动作
};
#endif LIST_WIDGET_H