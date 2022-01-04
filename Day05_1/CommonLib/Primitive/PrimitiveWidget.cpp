#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <CommonLib/MainWindow/MainWindow.h>
#include <CommonLib/ListWidget/ListWidget.h>
#include <CommonLib/Primitive/PrimitiveObject.h>
#include <CommonLib/Primitive/PrimitiveWidget.h>
CPrimitiveWidget::CPrimitiveWidget(CMainWindow* pMainWindow,CListWidget* pListWidget)
	:m_pMainWindow(pMainWindow)
	,m_pListWidget(pListWidget)
	,m_opPrimitiveObject(nullptr)
{
	//初始化列表
	initMap();
	//初始化控件
	initWidget();
	//初始化图元
	initPrimitive();
}

CPrimitiveWidget::~CPrimitiveWidget()
{

}

void CPrimitiveWidget::initMap()
{
	m_vecPrimitive.clear();
	m_vecPrimitive.push_back(QString::fromLocal8Bit("多边形"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("点"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("线"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("多段线"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("封闭线"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("三角形"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("多段三角形"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("三角形扇面"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("四边形"));
	m_vecPrimitive.push_back(QString::fromLocal8Bit("多段四边形"));
	int i=0;
	m_mapPrimitive.clear();
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::POLYGON);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::POINTS);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::LINES);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::LINE_STRIP);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::LINE_LOOP);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::TRIANGLES);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::TRIANGLE_STRIP);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::TRIANGLE_FAN);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::QUADS);
	m_mapPrimitive.insert(m_vecPrimitive.at(i++),osg::PrimitiveSet::QUAD_STRIP);

	m_vecColor.clear();
	m_vecColor.push_back(QString::fromLocal8Bit("白色"));
	m_vecColor.push_back(QString::fromLocal8Bit("红色"));
	m_vecColor.push_back(QString::fromLocal8Bit("绿色"));
	m_vecColor.push_back(QString::fromLocal8Bit("蓝色"));
	m_vecColor.push_back(QString::fromLocal8Bit("黄色"));
	m_vecColor.push_back(QString::fromLocal8Bit("紫色"));
	m_vecColor.push_back(QString::fromLocal8Bit("青色"));
	m_vecColor.push_back(QString::fromLocal8Bit("黑色"));
	i=0;
	m_mapColor.clear();
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(1.0,1.0,1.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(1.0,0.0,0.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(0.0,1.0,0.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(0.0,0.0,1.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(1.0,1.0,0.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(1.0,0.0,1.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(0.0,1.0,1.0,1.0));
	m_mapColor.insert(m_vecColor.at(i++),osg::Vec4(0.0,0.0,0.0,1.0));
}

void CPrimitiveWidget::initWidget()
{
	QWidget* pWidget = new QWidget;
	pWidget->setFixedWidth(100);
	m_pMainWindow->getHLayout()->addWidget(pWidget);
	QVBoxLayout* pVLayout = new QVBoxLayout;
	pWidget->setLayout(pVLayout);


	QLabel* pTypeLabel = new QLabel(QString::fromLocal8Bit("图元类型"));
	pVLayout->addWidget(pTypeLabel);

	QComboBox* pTypeCombBox = new QComboBox();
	connect(pTypeCombBox,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotType(const QString &)));
	foreach (auto primitive,m_vecPrimitive)
	{
		pTypeCombBox->addItem(primitive);
	}
	pVLayout->addWidget(pTypeCombBox);

	QLabel* pPointLabel = new QLabel(QString::fromLocal8Bit("点大小"));
	pVLayout->addWidget(pPointLabel);
	QSpinBox* pPointBox = new QSpinBox;
	pPointBox->setRange(1,100);
	connect(pPointBox,SIGNAL(valueChanged(int)),this,SLOT(slotPoint(int)));
	
	pVLayout->addWidget(pPointBox);

	QLabel* pLineLabel = new QLabel(QString::fromLocal8Bit("线宽"));
	pVLayout->addWidget(pLineLabel);
	QSpinBox* pLineBox = new QSpinBox;
	pLineBox->setRange(1,10);
	connect(pLineBox,SIGNAL(valueChanged(int)),this,SLOT(slotLine(int)));
	pVLayout->addWidget(pLineBox);

	QLabel* pColorLabel = new QLabel(QString::fromLocal8Bit("颜色"));
	pVLayout->addWidget(pColorLabel);
	QComboBox* pColorCombBox = new QComboBox();
	connect(pColorCombBox,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotColor(const QString &)));
	foreach (auto color,m_vecColor)
	{
		pColorCombBox->addItem(color);
	}
	pVLayout->addWidget(pColorCombBox);

	QCheckBox* pTextureBox = new QCheckBox(QString::fromLocal8Bit("开启纹理"));
	pTextureBox->setCheckable(true);
	pTextureBox->setChecked(true);
	connect(pTextureBox,SIGNAL(stateChanged(int)),this,SLOT(slotTexture(int)));
	pVLayout->addWidget(pTextureBox);

	pVLayout->addStretch();

}

void CPrimitiveWidget::initPrimitive()
{
	if (!m_opPrimitiveObject)
	{
		//新建图元对象
		m_opPrimitiveObject = new CPrimitiveObject;
		m_pListWidget->addModel(QString::fromLocal8Bit("图元"),m_opPrimitiveObject.get());
	}
}

void CPrimitiveWidget::slotType( const QString & strType )
{
	initPrimitive();
	m_opPrimitiveObject->setPrimitive(m_mapPrimitive.value(strType));
}

void CPrimitiveWidget::slotPoint( int nSize )
{
	initPrimitive();
	m_opPrimitiveObject->setPointSize(nSize);
}

void CPrimitiveWidget::slotLine( int nWidth )
{
	initPrimitive();
	m_opPrimitiveObject->setLineWidth(nWidth);
}

void CPrimitiveWidget::slotColor( const QString & strType )
{
	initPrimitive();
	m_opPrimitiveObject->setColor(m_mapColor.value(strType));
}

void CPrimitiveWidget::slotTexture( int nState )
{
	initPrimitive();
	m_opPrimitiveObject->setTexture(nState);
}
