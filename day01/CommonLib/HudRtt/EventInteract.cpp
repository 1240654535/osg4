#include <EventInteract.h>
#include <osg/ShapeDrawable>

osg::Camera* CHUDProvider::createHUD()
{
	// create a camera to set up the projection and model view matrices, and the subgraph to draw in the HUD
	osg::Camera* pCamera = new osg::Camera;
	// set the projection matrix
	pCamera->setProjectionMatrix(osg::Matrix::ortho2D(0,1580,0,1024));
	// set the view matrix
	pCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	pCamera->setViewMatrix(osg::Matrix::identity());
	// only clear the depth buffer
	pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	// draw subgraph after main camera view.
	pCamera->setRenderOrder(osg::Camera::POST_RENDER);
	// we don't want the camera to grab event focus from the viewers main camera(s).
	pCamera->setAllowEventFocus(false);

	// add to this camera a subgraph to render
	{
		osg::Geode* pGeode = new osg::Geode();
		osg::StateSet* pStateset = pGeode->getOrCreateStateSet();
		pStateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		std::string strTimesFont("fonts/arial.ttf");
		float fFontSize = 25.0;
		osg::Vec3 position(250.0f,800.0f,0.0f);
		osg::Vec3 delta(0.0f,-120.0f,0.0f);

		//文字
		// add to this camera a subgraph to render
		{
			{
				osgText::Text* pText = new  osgText::Text;//新建文字节点
				pGeode->addDrawable( pText );//添加文字节点到几何节点中
				pText->setFont(strTimesFont);//设置字体
				pText->setPosition(position);//设置文字节点位置
				pText->setText("Head Up Displays are simple :-)");//设置文字内容
				position += delta;//下一个文字的位置
			}

			{
				osgText::Text* pText = new  osgText::Text;
				pGeode->addDrawable( pText );

				pText->setFont(strTimesFont);
				pText->setPosition(position);
				pText->setText("All you need to do is create your text in a subgraph.");
				position += delta;
			}

			{
				osgText::Text* pText = new  osgText::Text;
				pGeode->addDrawable( pText );

				pText->setFont(strTimesFont);
				pText->setPosition(position);
				pText->setText("Then place an osg::Camera above the subgraph\n"
					"to create an orthographic projection.\n");
				position += delta;
			}

			{
				osgText::Text* text = new  osgText::Text;
				pGeode->addDrawable( text );

				text->setFont(strTimesFont);
				text->setPosition(position);
				text->setText("Set the Camera's ReferenceFrame to ABSOLUTE_RF to ensure\n"
					"it remains independent from any external model view matrices.");
				position += delta;
			}

			{
				osgText::Text* text = new  osgText::Text;
				pGeode->addDrawable( text );

				text->setFont(strTimesFont);
				text->setPosition(position);
				text->setText("And set the Camera's clear mask to just clear the depth buffer.");
				position += delta;
			}

			{
				osgText::Text* text = new  osgText::Text;
				pGeode->addDrawable( text );

				text->setFont(strTimesFont);
				text->setPosition(position);
				text->setText("And finally set the Camera's RenderOrder to POST_RENDER\n"
					"to make sure it's drawn last.");
				position += delta;
			}
		}
		//贴图
		{
			//添加纹理
			osg::ref_ptr<osg::Geode> gnode2 = new osg::Geode;//纹理节点
			osg::ref_ptr<osg::Geometry> gm = new osg::Geometry();//纹理图元

			gnode2->addDrawable(gm);//添加绘制

			//压入顶点
			osg::BoundingBox bb;//包围盒
			for(unsigned int i=0;i<pGeode->getNumDrawables();++i)
			{
				bb.expandBy(pGeode->getDrawable(i)->getBoundingBox());//根据文字图元节点设置包围盒
			}

			osg::Geometry* geom = new osg::Geometry;

			osg::Vec3Array* vertices = new osg::Vec3Array;
			float depth = bb.zMin()-0.1;//图片深度在文字之下

			//贴在左下角
			osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array();
			vertex->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
			vertex->push_back(osg::Vec3(bb.xMax(), bb.yMin(), depth));
			vertex->push_back(osg::Vec3(bb.xMax(), bb.yMax(), depth));
			vertex->push_back(osg::Vec3(bb.xMin(), bb.yMax(), depth));

			gm->setVertexArray(vertex);

			//法线
			osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
			normal->push_back(osg::Vec3(0.0, 0.0, 1.0));
			gm->setNormalArray(normal);

			//设置绑定方式
			gm->setNormalBinding(osg::Geometry::BIND_OVERALL);

			//设置纹理坐标
			osg::ref_ptr<osg::Vec2Array> coord = new osg::Vec2Array();
			coord->push_back(osg::Vec2(0.0, 0.0));
			coord->push_back(osg::Vec2(1.0, 0.0));
			coord->push_back(osg::Vec2(1.0, 1.0));
			coord->push_back(osg::Vec2(0.0, 1.0));
			gm->setTexCoordArray(0, coord);

			//设置关联
			gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

			//贴纹理
			//osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Cubemap_axis/posx.png");
			osg::ref_ptr<osg::Texture2D> t2d = new osg::Texture2D();
			//t2d->setImage(0, image);

			//贴纹理
			osg::ref_ptr<osg::ImageSequence> imageSequence = new osg::ImageSequence;
			imageSequence->setLength(4.0);
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/posx.png"));
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/negx.png"));
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/posy.png"));
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/negy.png"));
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/posz.png"));
			imageSequence->addImage(osgDB::readImageFile("Cubemap_axis/negz.png"));
			imageSequence->play();
			t2d->setImage(0, imageSequence);

			gm->getOrCreateStateSet()->setTextureAttributeAndModes(0, t2d, osg::StateAttribute::ON);//设置纹理属性模式
			gm->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
			pGeode->addChild(gnode2);

		}

		pCamera->addChild(pGeode);
	}

	return pCamera;
}

osg::Node* CHUDProvider::CreateTexture()
{
	osg::ref_ptr<osg::Node> rpNode = osgDB::readNodeFile("cow.osg");//读取模型
	osg::ref_ptr<osg::MatrixTransform> rpMt = new osg::MatrixTransform;//创建矩阵节点
	rpMt->addChild(rpNode);
	rpMt->setMatrix(osg::Matrix::scale(10,10,10) );//放大
	rpMt->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);//重定向发现

	osg::ref_ptr<osg::Camera>rpHudCamera=new osg::Camera;//创建相机
	rpHudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);//清除深度缓存
	rpHudCamera->setAllowEventFocus(false);//不接收主窗事件
	rpHudCamera->setRenderOrder(osg::Camera::POST_RENDER);//最后渲染
	rpHudCamera->setViewport(0, 0, 512, 512);//设置窗口位置大小
	rpHudCamera->addChild(rpMt);//添加模型节点
	osg::ref_ptr<osg::Group>root=new osg::Group;
	root->addChild(rpMt);
	root->addChild(rpHudCamera);
	return root.release();
 }


osg::Camera* CHUDProvider::createRTT()
{
	osg::GraphicsContext::WindowingSystemInterface *wsi= osg::GraphicsContext::getWindowingSystemInterface();//获取窗口系统接口
	if(!wsi){
		cout<<"wsi is NULL"<<endl;
		return NULL;
	}
	unsigned int width,height;//宽高
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);//获取屏幕宽高

	osg::ref_ptr<osg::GraphicsContext::Traits>traits=new osg::GraphicsContext::Traits;//图形上下文设置
	traits->x=0;
	traits->y=0;
	traits->width=width;
	traits->height=height;
	traits->windowDecoration=false;
	traits->doubleBuffer=true;
	traits->sharedContext=0;

	osg::ref_ptr<osg::GraphicsContext>gc=osg::GraphicsContext::createGraphicsContext(traits);//图形上下文

  osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;//创建相机
  rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);//最先渲染
  rttCamera->setGraphicsContext(gc);
  rttCamera->setViewport(0, 0, 500, 500);

  osg::ref_ptr<osg::Group>root=new osg::Group;
  osg::ref_ptr<osg::Geode>geode=new osg::Geode;
  root->addChild(geode);
 
  osg::ref_ptr<osg::Geometry>gm=new osg::Geometry;//设置集合图元
  geode->addDrawable(gm);
 
  osg::ref_ptr<osg::Vec3Array>vertex=new osg::Vec3Array;//设置图元顶点
  vertex->push_back(osg::Vec3(-400,200,-300));
  vertex->push_back(osg::Vec3(400,200,-300));
  vertex->push_back(osg::Vec3(400,200,300));
  vertex->push_back(osg::Vec3(-400,200,300));
  gm->setVertexArray(vertex);
 
  osg::ref_ptr<osg::Vec3Array>norm=new osg::Vec3Array;//法线
  norm->push_back(osg::Vec3(0,-1,0));
  gm->setNormalArray(norm);
  gm->setNormalBinding(osg::Geometry::BIND_OVERALL);
 
  osg::ref_ptr<osg::Vec2Array>coord=new osg::Vec2Array;//纹理顶点
  coord->push_back(osg::Vec2(0,0));
  coord->push_back(osg::Vec2(1,0));
  coord->push_back(osg::Vec2(1,1));
  coord->push_back(osg::Vec2(0,1));
  gm->setTexCoordArray(0, coord);//设置纹理
  gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));//图元连接方式设置
  gm->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);//关闭光照
  osg::ref_ptr<osg::Texture2D>t2d=new osg::Texture2D;//纹理
  t2d->setInternalFormat(GL_RGBA);//设置颜色属性

  gm->getOrCreateStateSet()->setTextureAttributeAndModes(0, t2d,osg::StateAttribute::ON);//开启纹理
  rttCamera->attach(osg::Camera::COLOR_BUFFER,t2d);//关联纹理
  return rttCamera;
}


//做一个圆，并贴上纹理
osg::Node* CHUDProvider::CreateNode(osg::Texture2D* t2d)
{
	osg::Geode* gnode = new osg::Geode;
	osg::StateSet* stateset = gnode->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, t2d, osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::TessellationHints*hints = new osg::TessellationHints;
	hints->setDetailRatio(1.0f);

	gnode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(400.0, 300.0, 0.0), 150, 0.1), hints));
	return gnode;

}

//创建一个HUD，固定圆盘
osg::Camera* CHUDProvider::CreateHUD(osg::Texture2D* t2d)
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setAllowEventFocus(false);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewport(200, 0, 800, 600);
	camera->setProjectionMatrixAsOrtho2D(0, 800, 0, 600);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	camera->addChild(CreateNode(t2d));
	return camera.release();
}

//烘培纹理
osg::Group*  CHUDProvider::CreateRTTScale(osgViewer::Viewer * viewer)
{
	osg::ref_ptr<osg::Group> gp = new osg::Group;
	osg::ref_ptr<osg::Node> ceep = osgDB::readNodeFile("cow.osg");

	//创建主相机
	if(!viewer)
	{
		std::cout<< "error viewer" <<std::endl;
		return NULL;
	}
	osg::ref_ptr<osg::GraphicsContext> gc = viewer->getCamera()->getGraphicsContext();
	if(!gc.valid())
	{
		return NULL;
	}
	
	unsigned int width = gc->getTraits()->width ;
	unsigned int height = gc->getTraits()->height;

	//创建主相机
	osg::ref_ptr<osg::Camera> master = new osg::Camera;
	master->setGraphicsContext(gc);
	master->setViewport(0, 0, width, height);
	viewer->addSlave(master);

	//创建RTT相机
	osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera;
	rttCamera->setRenderOrder(osg::Camera::PRE_RENDER);
	rttCamera->setGraphicsContext(gc);
	rttCamera->setViewport(0, 0, width, height);
	rttCamera->addChild(ceep);
	viewer->addSlave(rttCamera, osg::Matrix::scale(8, 8, 8), osg::Matrix::identity(), false);
	
	osg::Texture2D* t2d = new osg::Texture2D;
	t2d->setInternalFormat(GL_RGBA);
	rttCamera->attach(osg::Camera::COLOR_BUFFER, t2d);
	rttCamera->addUpdateCallback(new CUpdateViewPort(rttCamera,viewer ));
	gp->addChild(CreateHUD(t2d));
	return gp.release();
}