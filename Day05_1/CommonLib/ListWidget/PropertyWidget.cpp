#include <QLabel>
#include <QDoubleSpinBox>
#include <CommonLib/Common/Common.h>
#include <CommonLib/ListWidget/ModelObject.h>
#include <CommonLib/ListWidget/PropertyWidget.h>
CPropertyWidget::CPropertyWidget(CModelObject* pModelObject,QWidget* pParent)
	:QWidget(pParent)
	,m_pModelObject(pModelObject)
{
	setWindowFlags(Qt::Dialog);
	setAttribute(Qt::WA_DeleteOnClose);
	QVBoxLayout* pVlayout = new QVBoxLayout;
	this->setLayout(pVlayout);
	osg::Matrix mat = m_pModelObject->getMatrix();
	{
		m_vecPosition = mat.getTrans();
		QHBoxLayout* pHLayout = new QHBoxLayout;
		pVlayout->addLayout(pHLayout);
		QLabel* pLabel = new QLabel(QString::fromLocal8Bit("位移"));
		pLabel->setFixedWidth(30);
		pHLayout->addWidget(pLabel);
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-10000,10000);
			pDSBox->setValue(m_vecPosition.x());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotTX(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-10000,10000);
			pDSBox->setValue(m_vecPosition.y());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotTY(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-10000,10000);
			pDSBox->setValue(m_vecPosition.z());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotTZ(double)));
			pHLayout->addWidget(pDSBox);
		}
	}
	{
		FeCommon::Quat2DegreesRotate(mat.getRotate(),m_vecRotation);
		QHBoxLayout* pHLayout = new QHBoxLayout;
		pVlayout->addLayout(pHLayout);
		QLabel* pLabel = new QLabel(QString::fromLocal8Bit("旋转"));
		pLabel->setFixedWidth(30);
		pHLayout->addWidget(pLabel);
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-360,360);
			pDSBox->setValue(m_vecRotation.x());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotRX(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-360,360);
			pDSBox->setValue(m_vecRotation.y());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotRY(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(-360,360);
			pDSBox->setValue(m_vecRotation.z());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotRZ(double)));
			pHLayout->addWidget(pDSBox);
		}
	}
	{
		m_vecScale = mat.getScale();
		QHBoxLayout* pHLayout = new QHBoxLayout;
		pVlayout->addLayout(pHLayout);
		QLabel* pLabel = new QLabel(QString::fromLocal8Bit("缩放"));
		pLabel->setFixedWidth(30);
		pHLayout->addWidget(pLabel);
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(0,10000);
			pDSBox->setValue(m_vecScale.x());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotSX(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(0,10000);
			pDSBox->setValue(m_vecScale.y());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotSY(double)));
			pHLayout->addWidget(pDSBox);
		}
		{
			QDoubleSpinBox* pDSBox = new QDoubleSpinBox;
			pDSBox->setRange(0,10000);
			pDSBox->setValue(m_vecScale.z());
			connect(pDSBox,SIGNAL(valueChanged(double)),this,SLOT(slotSZ(double)));
			pHLayout->addWidget(pDSBox);
		}
	}
}

CPropertyWidget::~CPropertyWidget()
{

}

void CPropertyWidget::slotTX(double dValue)
{
	m_vecPosition.x() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotTY(double dValue)
{
	m_vecPosition.y() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotTZ(double dValue)
{
	m_vecPosition.z() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotRX( double dValue )
{
	m_vecRotation.x() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotRY( double dValue )
{
	m_vecRotation.y() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotRZ( double dValue )
{
	m_vecRotation.z() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotSX( double dValue )
{
	m_vecScale.x() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotSY( double dValue )
{
	m_vecScale.y() = dValue;
	updateMatrix();
}

void CPropertyWidget::slotSZ( double dValue )
{
	m_vecScale.z() = dValue;
	updateMatrix();
}

void CPropertyWidget::updateMatrix()
{
	m_pModelObject->setMatrix(osg::Matrix::scale(m_vecScale)*FeCommon::DegreesRotate2Matrix(m_vecRotation)*osg::Matrix::translate(m_vecPosition));
}

