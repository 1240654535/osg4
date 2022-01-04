// osg4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/StateSetManipulator>
#include<osgViewer/Viewer>
#include<osg/Node>
#include<osg/Geode>
#include<osg/Group>
#include<osgDB/ReadFile>
#include<osgDB/WriteFile> // 写文件暂时不用
#include<osgUtil/Optimizer>

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int main()
{
	//osgViewer::Viewer viewer;
	//viewer.setSceneData(osgDB::readNodeFile("cessna.osg"));

	////添加状态事件
	//viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));

	////添加窗口缩放事件
	//viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	////添加一下常用的状态设置
	//viewer.addEventHandler(new osgViewer::StatsHandler);

	//viewer.realize();
	//viewer.run();
	//return 0;


	//osgViewer::Viewer viewer;
	//viewer.setSceneData(osgDB::readNodeFile("glider.osg"));
	//viewer.realize();
	//return viewer.run();


	//osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer();
	//osg::ref_ptr<osg::Group> root = new osg::Group();
	//osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("C:\\Users\\Administrator\\OneDrive\\桌面\\OsgData\\cow.osg");
	//root->addChild(node.get());
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(root.get());
	//viewer->setSceneData(root.get());
	//viewer->setUpViewInWindow(600, 100, 800, 600);
	//viewer->realize();
	//viewer->run(); 

  //创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//创建场景组节点
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//创建一个节点,读取牛的模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	//添加到场景
	root->addChild(node.get());

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	//设置场景数据
	viewer->setSceneData(root.get());

	//初始化并创建窗口
	viewer->realize();

	//开始渲染
	viewer->run();

	return 0;

		
}

