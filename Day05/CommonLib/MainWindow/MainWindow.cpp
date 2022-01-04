#include <osgGA/TrackballManipulator>
#include <osgQt/GraphicsWindowQt>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <QApplication>
#include <CommonLib/MainWindow/MainWindow.h>
CMainWindow::CMainWindow(QWidget* parent, Qt::WindowFlags f) 
	: QWidget(parent, f)
{
	//根据qt版本决定使用单线程或多线程，以及qt应用程序属性
	osgViewer::ViewerBase::ThreadingModel threadingModel;
#if QT_VERSION >= 0x050000
	threadingModel = osgViewer::ViewerBase::SingleThreaded;
#else
	threadingModel = osgViewer::ViewerBase::CullDrawThreadPerContext;
#endif

#if QT_VERSION >= 0x040800
	if (threadingModel != osgViewer::ViewerBase::SingleThreaded)
		QApplication::setAttribute(Qt::AA_X11InitThreads);
#endif
	m_rpViewer = new osgViewer::Viewer;
	m_rpViewer->setThreadingModel(threadingModel);//设置线程
	m_rpViewer->setCameraManipulator( new osgGA::TrackballManipulator );//设置相机操作器
	m_rpViewer->setKeyEventSetsDone(0);// disable the default setting of viewer.done() by pressing Escape.//设置不接受esc退出事件
	m_rpViewer->addEventHandler( new osgViewer::StatsHandler );//添加s键事件
	m_rpViewer->addEventHandler( new osgGA::StateSetManipulator(m_rpViewer->getCamera()->getOrCreateStateSet()));//添加w键事件
	m_rpRoot = new osg::Group;
	m_rpViewer->setSceneData(m_rpRoot.get());
	//初始化qt主窗口布局
	m_pVLayout = new QVBoxLayout;
	m_pVLayout->setMargin(1);
	m_pVLayout->setSpacing(0);
	m_pHLayout = new QHBoxLayout;
	m_pHLayout->setMargin(0);
	m_pHLayout->setSpacing(0);
	//创建场景widget指针
	QWidget* pSceneWidget = createGraphicsWindow(0,0,800,600,"main window",true);
	pSceneWidget->setMinimumSize(500,500);
	m_pHLayout->addWidget(pSceneWidget);
	m_pVLayout->addLayout(m_pHLayout);
	setLayout(m_pVLayout);

	//设置每10ms更新场景
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer.start(10);
}

void CMainWindow::home()
{
	if (m_rpViewer.valid() && m_rpViewer->getCameraManipulator())
	{
		m_rpViewer->getCameraManipulator()->home(0);
	}
}

QWidget* CMainWindow::createGraphicsWindow( int nX, int nY, int nW, int nH, const std::string& strName, bool bWindowDecoration)
{
	//显示设置
	osg::DisplaySettings* pDS = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> pTraits = new osg::GraphicsContext::Traits(pDS);
	//场景内容显示特征
	pTraits->windowName = strName;//窗口名称
	pTraits->windowDecoration = false;//窗口装饰
	pTraits->overrideRedirect = true;//重定向
	pTraits->x = nX;//x位置
	pTraits->y = nY;//y位置
	pTraits->width = nW;//宽
	pTraits->height = nH;//高
	pTraits->doubleBuffer = true;//双缓存
	pTraits->alpha = pDS->getMinimumNumAlphaBits();
	pTraits->stencil = pDS->getMinimumNumStencilBits();//模具
	pTraits->sampleBuffers = pDS->getMultiSamples();//采样缓存
	pTraits->samples = pDS->getNumMultiSamples();
	osgQt::GraphicsWindowQt* pGW = new osgQt::GraphicsWindowQt(pTraits.get());//新建窗口
	if (!pGW)
	{
		return nullptr;
	}
	if (!m_rpViewer)
	{
		return nullptr;
	}
	osg::Camera* pCamera = m_rpViewer->getCamera();
	if (!pCamera)
	{
		return nullptr;
	}
	pCamera->setGraphicsContext( pGW );
	pCamera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
	pCamera->setViewport( new osg::Viewport(0, 0, pTraits->width, pTraits->height) );
	//设置远近裁截面
	pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(pTraits->width)/static_cast<double>(pTraits->height), 1.0f, 10000.0f );
	return pGW->getGLWidget();
}

void CMainWindow::paintEvent( QPaintEvent* event )
{ 
	m_rpViewer->frame();
}
