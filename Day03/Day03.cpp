// Day03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>
#include <osgViewer/Viewer>
#include "Common.h"
#include <osg/Point>
#include <osg/LineWidth>
#include <string.h>
#include <osg/ShapeDrawable>
#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>
#include <osg/TexGen>
#include <osg/TexEnv>
#include "MHandleControl.h"
#include <osg/Switch>
using namespace std;


//设置颜色,参数默认值蓝色,绑定所有顶点
void SetColor(const osg::ref_ptr<osg::Geometry> & geometry, osg::Vec4 v4 = osg::Vec4(0.0, 1.0, 1.0, 1.0), osg::Geometry::AttributeBinding binding = osg::Geometry::AttributeBinding::BIND_OVERALL) {
	osg::ref_ptr<osg::Vec4Array> v4a = new osg::Vec4Array;
	v4a->push_back(v4);
	//shapeDrawable->setColor(v4);
	geometry->setColorArray(v4a.get());
	geometry->setColorBinding(binding);
}
void setTexture(osg::ref_ptr<osg::Geode> &geode) {
	string filename = "C:\\Users\\Administrator\\OneDrive\\桌面\\OsgData\\a9c8068efd544c438a4dcf1be85b72d4.jpg";
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D(osgDB::readImageFile(filename));
	texture->setDataVariance(osg::Object::DYNAMIC);
	//设置贴图
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
	//geode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);//重新设置节点规模后，重置法向量
	/*osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
	texgen->setMode(osg::TexGen::SPHERE_MAP);
	osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv;
	texenv->setMode(osg::TexEnv::Mode::ADD);
	geode->getOrCreateStateSet()->setTextureAttribute(1, texenv.get());
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texgen.get(), osg::StateAttribute::ON);
	*/
}
//设置点大小
void setPointSize(float nSize, osg::ref_ptr<osg::Geometry> & Geo)
{
	//osg::ref_ptr<osg::Point> rpPoint = dynamic_cast<osg::Point*>(Geo->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POINT));
	//if (rpPoint.valid())
	//{
	//	rpPoint->setSize(nSize);
	//}
	osg::StateSet* stateSet = Geo->getOrCreateStateSet();
	osg::Point* pointSize = new osg::Point;
	pointSize->setSize(nSize);
	stateSet->setAttribute(pointSize);
}
//绘制点
void DrawPoint(osg::ref_ptr<osg::Vec3Array> v) {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Geometry> geo = new osg::Geometry;
	geo->setVertexArray(v.get());
	geo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));
	osg::ref_ptr<osg::Geode> node = new osg::Geode;
	setPointSize(5, geo);
	node->addDrawable(geo);
	viewer->setSceneData(node.get());
	//解决双屏问题，只在单独的屏幕显示
	viewer->setUpViewOnSingleScreen();
	viewer->run();
}
//设置线宽
void setLineWidth(float nWidth, osg::ref_ptr<osg::Geometry>& geom)
{
	//osg::ref_ptr<osg::LineWidth> rpLineWidth = dynamic_cast<osg::LineWidth*>(geom->getOrCreateStateSet()->getAttribute(osg::StateAttribute::LINEWIDTH));
	//if (rpLineWidth.valid())
	//{
	//	rpLineWidth->setWidth(nWidth);
	//}
	osg::ref_ptr<osg::StateSet> stateset = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth> lineWid = new osg::LineWidth(nWidth);
	stateset->setAttribute(lineWid);
}
//绘制线
void DrawLines(osg::ref_ptr<osg::Vec3Array> v) {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(v.get());
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,v->size()));
	setLineWidth(5,geom);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom);
	viewer->setSceneData(geode.get());
	viewer->setUpViewOnSingleScreen();
	viewer->run();
}
//绘制点划线
void DrawPointsAndLines(osg::ref_ptr<osg::Vec3Array> v) {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(v.get());
	for (int i = 0; i < v->size(); i++)
	{
		if ((i+1)%3 == 0)
		{
			geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, i, 1));
			geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, i-2, 2));
		}
	}
	setPointSize(5, geom);
	setLineWidth(5, geom);
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom);
	SetColor(geom, osg::Vec4(1, 0, 0, 1));
	viewer->setSceneData(geode.get());
	viewer->setUpViewOnSingleScreen();
	viewer->run();
}
//绘制球体
void DrawBall() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//半径
	float radius = 0.8f;
	//精细度
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	//设置精细度
	hints->setDetailRatio(1.1f);
	//创建球体
	osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius);
	osg::ref_ptr<osg::ShapeDrawable> draw = new osg::ShapeDrawable(sphere, hints);
	
	draw->setColor(osg::Vec4(0, 1, 1,0.29));
	
	geode->addDrawable(draw);
	setTexture(geode);
	draw->setColor(osg::Vec4(0, 1, 1, 0.29));
	SetColor(draw, osg::Vec4(1, 0, 0, 1));
	root->addChild(geode.get());
	viewer->setSceneData(root);
	viewer->setUpViewOnSingleScreen();
	viewer->run();
}
//绘制星球
osg::ref_ptr<osg::Geode> DrawPlanet(float radius, osg::Vec3 v) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//精细度
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	//设置精细度
	hints->setDetailRatio(1.1f);
	//创建球体
	osg::ref_ptr<osg::Sphere> sphere = new osg::Sphere(v, radius);
	osg::ref_ptr<osg::ShapeDrawable> draw = new osg::ShapeDrawable(sphere, hints);
	//draw->setColor(osg::Vec4(1, 0, 0, 1));
	SetColor(draw, osg::Vec4(0.1, 0.5, 0.1, 1));
	geode->addDrawable(draw);
	setTexture(geode);
	return geode;
}
//绘制圆形
osg::ref_ptr<osg::Geode> DrawCircle(float radius, osg::Vec3 v) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
	geode->addDrawable(geometry);
	//存放所有圆上的点，把这些点连接成直线画成圆
	osg::ref_ptr<osg::Vec3Array> circlePoints = new osg::Vec3Array;
	//得到半径为radius的314个点，这些点形成线坐标表盘
	for (double i = 0.0; i < 6.28; i += 0.02) {
		circlePoints->push_back(osg::Vec3(radius * sin(i), -0.0, radius * cos(i)));
	}
	//设置顶点
	geometry->setVertexArray(circlePoints.get());
	//画线
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, circlePoints->size()));
	SetColor(geometry);
	setLineWidth(3, geometry);
	return geode;
}
//绘制太阳系(无显隐功能)
void DrawSolarSystem() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Group> planetGroup = new osg::Group;
	osg::ref_ptr<osg::Group> circleGroup = new osg::Group;
	planetGroup->addChild(DrawPlanet(5,osg::Vec3(0,0,0)));
	planetGroup->addChild(DrawPlanet(2.5,osg::Vec3(-10,0,0)));
	planetGroup->addChild(DrawPlanet(1.8,osg::Vec3(-20,0,0)));
	planetGroup->addChild(DrawPlanet(1.2,osg::Vec3(-30,0,0)));
	planetGroup->addChild(DrawPlanet(2,osg::Vec3(-40,0,0)));
	planetGroup->addChild(DrawPlanet(1,osg::Vec3(-50,0,0)));
	planetGroup->addChild(DrawPlanet(2.1,osg::Vec3(-60,0,0)));
	planetGroup->addChild(DrawPlanet(3.1,osg::Vec3(-70,0,0)));
	planetGroup->addChild(DrawPlanet(2.2,osg::Vec3(-80,0,0)));
	circleGroup->addChild(DrawCircle(10, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(20, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(30, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(40, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(50, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(60, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(70, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(80, osg::Vec3(0, 0, 0)));
	MHandleControl::getInterSections(planetGroup, osg::Vec3(-90, 1, 2), osg::Vec3(1,3,4),root);
	root->addChild(planetGroup.get());
	root->addChild(circleGroup.get());
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	viewer->setSceneData(root.get());
	viewer->addEventHandler(new MHandleControl);
	viewer->setUpViewOnSingleScreen();
	viewer->run();
	
}
//绘制太阳系(有显隐功能)
void DrawSolarSystem_Switch() {
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Group> planetGroup = new osg::Group;
	osg::ref_ptr<osg::Switch> circleGroup = new osg::Switch;
	//此处星球与轨道线具备对应关系，轨道线在circleGroup的索引对应星球在planetGroup的索引加一
	planetGroup->addChild(DrawPlanet(5, osg::Vec3(0, 0, 0)));
	planetGroup->addChild(DrawPlanet(2.5, osg::Vec3(-10, 0, 0)));
	planetGroup->addChild(DrawPlanet(1.8, osg::Vec3(-20, 0, 0)));
	planetGroup->addChild(DrawPlanet(1.2, osg::Vec3(-30, 0, 0)));
	planetGroup->addChild(DrawPlanet(2, osg::Vec3(-40, 0, 0)));
	planetGroup->addChild(DrawPlanet(1, osg::Vec3(-50, 0, 0)));
	planetGroup->addChild(DrawPlanet(2.1, osg::Vec3(-60, 0, 0)));
	planetGroup->addChild(DrawPlanet(3.1, osg::Vec3(-70, 0, 0)));
	planetGroup->addChild(DrawPlanet(2.2, osg::Vec3(-80, 0, 0)));
	circleGroup->addChild(DrawCircle(10, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(20, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(30, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(40, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(50, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(60, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(70, osg::Vec3(0, 0, 0)));
	circleGroup->addChild(DrawCircle(80, osg::Vec3(0, 0, 0)));
	//设置线段用于与几何体相交
	MHandleControl::getInterSections(planetGroup, osg::Vec3(-90, 1, 2), osg::Vec3(1, 3, 4), root);
	root->addChild(planetGroup.get());
	root->addChild(circleGroup.get());
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	viewer->setSceneData(root.get());
	viewer->addEventHandler(new MHandleControl);
	viewer->setUpViewOnSingleScreen();
	viewer->run();

}
int main()
{
	cout << "1、绘制点" << endl;
	cout << "2、绘制点线" << endl;
	cout << "3、绘制点划线" << endl;
	cout << "4、绘制球体" << endl;
	cout << "5、绘制太阳系" << endl;
	cout << "6、有显隐状态的太阳系" << endl;
	int choise;
	cin >> choise;
	switch (choise)
	{
	case 1://绘制点
	{
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
		v->push_back(osg::Vec3(1, 1, 1));
		v->push_back(osg::Vec3(2, 1, 1));
		v->push_back(osg::Vec3(1, 4, 1));
		v->push_back(osg::Vec3(4, 5, 7));
		v->push_back(osg::Vec3(1, 3, 6));
		v->push_back(osg::Vec3(1, 6, 9));
		v->push_back(osg::Vec3(9, 2, 3));
		v->push_back(osg::Vec3(1, 7, 0));
		DrawPoint(v);
		break;
	}
	case 2://绘制线
	{
		osg::ref_ptr<osg::Vec3Array> v1 = new osg::Vec3Array;
		v1->push_back(osg::Vec3(0, 0, 0));
		v1->push_back(osg::Vec3(1, 0, 0));
		v1->push_back(osg::Vec3(2, 0, 0));
		v1->push_back(osg::Vec3(3, 0, 0));
		DrawLines(v1);
		break;
		
	}
	case 3://绘制点划线
	{
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
		v->push_back(osg::Vec3(0, 0, 0));
		v->push_back(osg::Vec3(1, 0, 0));
		v->push_back(osg::Vec3(2, 0, 0));
		v->push_back(osg::Vec3(3, 0, 0));
		v->push_back(osg::Vec3(4, 0, 0));
		v->push_back(osg::Vec3(5, 0, 0));
		v->push_back(osg::Vec3(6, 0, 0));
		v->push_back(osg::Vec3(7, 0, 0));
		v->push_back(osg::Vec3(8, 0, 0));
		v->push_back(osg::Vec3(9, 0, 0));
		v->push_back(osg::Vec3(10, 0, 0));
		v->push_back(osg::Vec3(11, 0, 0));
		v->push_back(osg::Vec3(12, 0, 0));
		v->push_back(osg::Vec3(13, 0, 0));
		v->push_back(osg::Vec3(14, 0, 0));
		v->push_back(osg::Vec3(15, 0, 0));
		DrawPointsAndLines(v);
		break;
	}
	case 4://绘制球体
		DrawBall();
		break;
	case 5:
		DrawSolarSystem();
		break;
	case 6:
		DrawSolarSystem_Switch();
		break;
	default:
		break;
	}

}

