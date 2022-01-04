#include <QFileDialog>
#include <osg/MatrixTransform>
#include <CommonLib/Common/Common.h>
#include <CommonLib/MainWindow/MainWindow.h>
#include <CommonLib/ListWidget/ModelObject.h>
#include <CommonLib/ListWidget/PropertyWidget.h>
#include <CommonLib/ListWidget/ListWidget.h>
Q_DECLARE_METATYPE(CModelObject*)
CListWidget::CListWidget(CMainWindow* pMainWindow)
	:m_pMainWindow(pMainWindow)
	,m_pListWidget(nullptr)
	,m_pAxesItem(nullptr)
	,m_pCurItem(nullptr)
	,m_pMenu(nullptr)
	,m_pAddAction(nullptr)
	,m_pDelAction(nullptr)
	,m_pClearAction(nullptr)
	,m_pPropertyAction(nullptr)
{
	//创建列表控件
	m_pListWidget = new QListWidget;
	m_pListWidget->setContextMenuPolicy(Qt::CustomContextMenu);//菜单格式
	m_pListWidget->setFixedWidth(120);//固定宽度
	m_pListWidget->setStyleSheet("QListWidget { background-color: rgba(102,204,255,255); font-size:12px; border: 1px solid rgba(249,133,0,255);}");//样式配置
	m_pMainWindow->getHLayout()->insertWidget(0,m_pListWidget);//插入列表到主窗口0位置

	//添加坐标轴到三维场景
	osg::ref_ptr<CModelObject> rpModelObject = new CModelObject("axes.osgt");
	rpModelObject->setMatrix(osg::Matrix::scale(1,1,1));
	m_pMainWindow->getRoot()->addChild(rpModelObject.get());

	//添加坐标轴到列表
	m_pAxesItem = new QListWidgetItem(QString::fromLocal8Bit("坐标轴"));//新建列表项
	m_pAxesItem->setCheckState(Qt::Checked);//设置为已选
	m_pAxesItem->setData(Qt::UserRole,QVariant::fromValue(rpModelObject.get()));//设置用户数据绑定到选项
	m_pListWidget->addItem(m_pAxesItem);//添加到列表

	m_pMainWindow->home();//视点重置

	//信号槽连接，属性窗口应用，模型显隐设置
	connect(m_pListWidget,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(slotShowMenu(const QPoint &)));//绑定鼠标点击事件信号槽
	connect(m_pListWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(slotVisible(QListWidgetItem *)));//绑定选项勾选状态信号槽
	
	m_pMenu = new QMenu(m_pListWidget);//新建菜单
	m_pMenu->setStyleSheet("QMenu { background-color: rgba(102,204,255,255); font-size:12px; border:1px solid rgba(249,133,0,255);}");//设置样式表

	m_pAddAction = new QAction(QString::fromLocal8Bit("添加"),m_pMenu);//添加按钮动作
	connect(m_pAddAction,SIGNAL(triggered()),this,SLOT(slotAdd()));//绑定信号槽

	m_pDelAction = new QAction(QString::fromLocal8Bit("删除"),m_pMenu);//添加删除动作
	connect(m_pDelAction,SIGNAL(triggered()),this,SLOT(slotDel()));

	m_pClearAction = new QAction(QString::fromLocal8Bit("清空"),m_pMenu);//添加清空动作
	connect(m_pClearAction,SIGNAL(triggered()),this,SLOT(slotClear()));
	
	m_pPropertyAction = new QAction(QString::fromLocal8Bit("属性"),m_pMenu);//添加属性动作
	connect(m_pPropertyAction,SIGNAL(triggered()),this,SLOT(slotProperty()));


	m_pMenu->addAction(m_pAddAction);//添加动作
	m_pMenu->addAction(m_pDelAction);
	m_pMenu->addAction(m_pClearAction);
	m_pMenu->addAction(m_pPropertyAction);
}

CListWidget::~CListWidget()
{

}

void CListWidget::slotShowMenu( const QPoint &pos )
{
	m_pCurItem = m_pListWidget->currentItem();
	if (m_pCurItem)//所选位置是列表项
	{
		if (m_pCurItem==m_pAxesItem)//如果是坐标轴，则不显示删除事件
		{
			m_pDelAction->setVisible(false);
		}
		else
		{
			m_pDelAction->setVisible(true);
		}
		m_pAddAction->setVisible(true);
		m_pClearAction->setVisible(true);
		m_pPropertyAction->setVisible(true);
	}
	else
	{
		m_pAddAction->setVisible(true);
		m_pDelAction->setVisible(false);
		m_pClearAction->setVisible(true);
		m_pPropertyAction->setVisible(false);
	}
	m_pMenu->exec(m_pListWidget->mapToGlobal(pos));//显示菜单到鼠标点击的位置
}

void CListWidget::slotAdd()
{
	QStringList strPathList = QFileDialog::getOpenFileNames(m_pMainWindow,"add",".","*.ive *.osg *.osgt");//通过打开资源管理窗口添加模型
	foreach (auto strPath,strPathList)
	{
		addModel(strPath);
	}
}

void CListWidget::addModel( const QString& strPath )
{
	osg::ref_ptr<CModelObject> rpModelObject = new CModelObject(strPath);
	m_pMainWindow->getRoot()->addChild(rpModelObject.get());

	QStringList strList = strPath.split("/");
	if (strList.size()<2)
	{
		strList = strPath.split("\\");
	}

	QListWidgetItem* m_pItem = new QListWidgetItem(strList.back());
	m_pItem->setCheckState(Qt::Checked);
	m_pItem->setData(Qt::UserRole,QVariant::fromValue(rpModelObject.get()));
	m_pListWidget->addItem(m_pItem);
}

void CListWidget::addModel( const QString& strName,osg::Node* pNode )
{
	if (pNode)
	{
		osg::ref_ptr<CModelObject> rpModelObject = new CModelObject(pNode);
		m_pMainWindow->getRoot()->addChild(rpModelObject.get());

		QListWidgetItem* m_pItem = new QListWidgetItem(strName);
		m_pItem->setCheckState(Qt::Checked);
		m_pItem->setData(Qt::UserRole,QVariant::fromValue(rpModelObject.get()));
		m_pListWidget->addItem(m_pItem);
	}
}

bool CListWidget::changeModelState(bool bState)
{
	int nRow = m_pListWidget->model()->rowCount();
	for (int i=0;i<nRow;++i)
	{
		auto pItem = m_pListWidget->item(i);
		if (pItem)
		{
			CModelObject* pModelObject = pItem->data(Qt::UserRole).value<CModelObject*>();
			if(pModelObject)
			{
				if (bState)
				{
					pItem->setCheckState(Qt::CheckState::Checked);
					pModelObject->setNodeMask(0xffffffff);
				}
				else
				{
					pItem->setCheckState(Qt::CheckState::Unchecked);
					pModelObject->setNodeMask(0x00000000);
				}
			}
		}
	}
	return false;
}

void CListWidget::slotDel()
{
	if (m_pCurItem)
	{
		del(m_pListWidget->row(m_pCurItem));
	}
}

void CListWidget::slotClear()
{
	int nRow = m_pListWidget->model()->rowCount();
	for (int i=1;i<nRow;++i)
	{
		del(1);
	}
}

void CListWidget::slotProperty()
{
	CModelObject* pModelObject = m_pCurItem->data(Qt::UserRole).value<CModelObject*>();
	if(pModelObject)
	{
		CPropertyWidget* pPropertyWidget = new CPropertyWidget(pModelObject,m_pMainWindow);
		pPropertyWidget->show();
	}
}

void CListWidget::slotVisible(QListWidgetItem * pItem)
{
	if (pItem)
	{
		CModelObject* pModelObject = pItem->data(Qt::UserRole).value<CModelObject*>();
		if(pModelObject)
		{
			if (pItem->checkState()==Qt::Checked)
			{
				pModelObject->setNodeMask(0xffffffff);
			}
			else if (pItem->checkState()==Qt::Unchecked)
			{
				pModelObject->setNodeMask(0x00000000);
			}
		}
	}
}

void CListWidget::del( int nRow )
{
	auto pItem = m_pListWidget->item(nRow);
	if (pItem)
	{
		CModelObject* pModelObject = pItem->data(Qt::UserRole).value<CModelObject*>();
		if(pModelObject)
		{
			m_pMainWindow->getRoot()->removeChild(pModelObject);
		}
		m_pListWidget->takeItem(nRow);
		pItem = nullptr;
	}
}
