// day01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
//#include <CommonLib/Common/Common.h>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <iostream>
#include<osg/Node>
#include<osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <cstring>
using namespace std;
//显示模型
void day01(string str)
{
	int nType = 0;
	while (nType < 4)
	{
		std::cout << "选择显示场景:" << std::endl;
		std::cout << "1.最简场景" << std::endl;
		std::cout << "2.显示模型" << std::endl;
		std::cout << "3.键盘事件" << std::endl;
		std::cout << "4.退出" << std::endl;
		std::cin >> nType;
		osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
		if (nType == 2 || nType == 3)
		{
			osg::ref_ptr<osg::Node> rpCow = osgDB::readNodeFile(str);
			rpViewer->setSceneData(rpCow.get());
		}
		if (nType == 3)
		{
			//设置事件处理
			rpViewer->addEventHandler(new osgViewer::StatsHandler);
			rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
			rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
		}
		if (nType < 4)
		{
			rpViewer->run();
		}
	}
}
//建立图形
osg::ref_ptr<osg::Node> createSceneGraph()
{
	// 创建一个用于保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	// 创建四个顶点的数组
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	//指定顶点数组
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));
	// 创建四种颜色的数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	//指定颜色
	geom->setColorArray(c.get());
	//颜色绑定方式为 osg::Geometry::BIND_PER_VERTEX，即每 种 颜 色 对 应 一 个 顶 点 。
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
	// 为唯一的法线创建一个数组
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	//指定法线
	geom->setNormalArray(n.get());
	//法 线 的 绑 定 方 式 为osg::Geometry::BIND_OVERALL，即整个 Geometry 几何体对应唯一的一个法线数据。
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));
	// 由保存的数据绘制四个顶点的多边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	// 向 Geode 类添加几何体（ Drawable）并返回 Geode
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//Geode 提供了 addDrawable()方法来关联应用程序中的几何信息。
	//Geode::addDrawable()将一个 Drawable 指针作为传入的参数。Drawable 类是一个派生了 Geometry 等很多子类的虚基类。
	geode->addDrawable(geom.get());
	return geode.get();
}
//将写入文件
void Wtite()
{
	osg::ref_ptr<osg::Node> root = createSceneGraph();
	if (!root.valid())
		osg::notify(osg::FATAL) << "Failed in createSceneGraph()."<< endl;
	bool result = osgDB::writeNodeFile(*(root.get()), "Simple.osg");
	if (!result)
		osg::notify(osg::FATAL) << "Failed in osgDB::writeNode()."<< endl;
}
int main()
{
	//createSceneGraph();
	//用读文件的形式看模型
	//day01("D:\\my-program\\c++\\VS2017\\osg4\\day01\\Simple.osg");
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::ref_ptr<osg::Node> node = createSceneGraph();
	viewer->setSceneData(node.get());
	viewer->setSceneData(node.get());
	viewer->run();
	
	return 0;
}
//最基本流程
void MostBasibleStep()
{
	//1.Viewer
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	//2.Node
	osg::ref_ptr<osg::Node> node = createSceneGraph();
	//3.Node设置进Viewer
	viewer->setSceneData(node.get());
	//4.运行
	viewer->run();
}
