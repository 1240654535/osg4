#include <QFileDialog>
#include <QMessageBox>
#include <CommonLib/MainWindow/MainWindow.h>
#include <CommonLib/ListWidget/ModelObject.h>
#include <LayoutWidget.h>
#include <stdlib.h>
//Q_DECLARE_METATYPE(CModelObject*)

CLayoutWidget::CLayoutWidget(CMainWindow* pMainWindow)
	:m_pGrid(NULL)
{
	pMainWindow->getHLayout()->addWidget(this);
	setMinimumWidth(100);
	setMinimumHeight(100);
	m_pGrid = new QGridLayout(this);
	CLayoutWidgetItem* pLabel1 = new CLayoutWidgetItem("pLabel1");
	CLayoutWidgetItem* pLabel2 = new CLayoutWidgetItem("pLabel2");
	CLayoutWidgetItem* pLabel3 = new CLayoutWidgetItem("pLabel3");
	CLayoutWidgetItem* pLabel4 = new CLayoutWidgetItem("pLabel4");
	pLabel1->setFixedSize(80,80);
	pLabel2->setFixedSize(80,80);
	pLabel3->setFixedSize(80,80);
	pLabel4->setFixedSize(80,80);
	pLabel1->setText("Test");
	pLabel2->setText("Test");
	pLabel3->setText("Test");
	pLabel4->setText("Test");
	std::string strOsgFile = getenv("OSG_FILE_PATH");
	strOsgFile = strOsgFile+"/placemark64.png";
	QPixmap PixMap(strOsgFile.c_str());
	pLabel4->setPixmap(PixMap);
	addWidgetItem(pLabel1);
	addWidgetItem(pLabel2);
	addWidgetItem(pLabel3);
	addWidgetItem(pLabel4);
}

CLayoutWidget::~CLayoutWidget()
{

}

bool CLayoutWidget::addWidgetItem(CLayoutWidgetItem* pWidget)
{
	if (pWidget)
	{
		m_vecItems.push_back(pWidget);
		m_pGrid->addWidget(pWidget);
		bool b = connect(pWidget,SIGNAL(signalClicked(QString)),this,SLOT(slotShowfUserInfo(QString)));
		return reSortWidgetItem();
	}
	return false;
}

void CLayoutWidget::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
 	reSortWidgetItem();
}

bool CLayoutWidget::reSortWidgetItem()
{
	QSize SizeWgt = this->size();
	int nColNumMax= SizeWgt.width() /ITEM_SIZE_WITH;
	int nItemSize = m_vecItems.size();
	int nRowCounts = nItemSize/nColNumMax;
	int nRowCountsPlus = nItemSize%nColNumMax;
	if (nRowCountsPlus)
	{
		nRowCounts++;
	}

	QObjectList listChildern = m_pGrid->children();
	for(int n=0;n<nItemSize;n++)
	{
		QWidget* pLabel = m_vecItems.at(n);
		if (pLabel && listChildern.contains(pLabel))
		{
			m_pGrid->removeWidget(pLabel);
		}
	}

	for (int nRow=0;nRow<nRowCounts;nRow++)
	{
		for (int nCol=0;nCol<nColNumMax;nCol++)
		{
			int nNumber = nRow*nColNumMax+nCol;
			if (nNumber<nItemSize)
			{
				QWidget* pLabel = m_vecItems.at(nNumber);
				if (pLabel)
				{
					m_pGrid->addWidget(pLabel,nRow,nCol);
				}
			}
			else
			{
				break;
			}
		}
	}
	return true;
}

void CLayoutWidget::slotShowfUserInfo(QString qstrInfo)
{
	QMessageBox msg;
	msg.setWindowTitle(QString::fromLocal8Bit("提示:")+qstrInfo);
	msg.setText(qstrInfo);
	msg.setStyleSheet("color:rgb(220, 0, 0);font: 14pt");
	msg.setIcon(QMessageBox::Information);
	msg.addButton(QString::fromLocal8Bit("确定"),QMessageBox::ActionRole);
	msg.addButton(QString::fromLocal8Bit("取消"),QMessageBox::ActionRole);
	msg.exec();
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
CLayoutWidgetItem::CLayoutWidgetItem(QString qstrInfo/* = ""*/)
	:m_qstrUserInfo(qstrInfo)
{

}

CLayoutWidgetItem::~CLayoutWidgetItem()
{

}

void CLayoutWidgetItem::setUserInfo(QString qstrInfo)
{
	m_qstrUserInfo = qstrInfo;
}

void CLayoutWidgetItem::mousePressEvent(QMouseEvent * event)
{
	QLabel::mousePressEvent(event);
	emit signalClicked(m_qstrUserInfo);
}
