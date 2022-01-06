// Day06.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include "MVisitor.h"
#include <iostream>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include "Callback.h"
osg::Node* readNode(const std::string& strPath)
{
	osg::ref_ptr<osg::Node> rpNode = osgDB::readNodeFile(strPath);//读取路径所在的模型
	if (rpNode.valid())
	{
		rpNode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);//重新设置节点规模后，重置法向量
		//规模如果变大了，法向量是不变的，模型会变黑，加上上面这句就避免了这个情况，因为重新设置了法向量
	}
	return rpNode.release();//release(）释放超级指针并传出节点指针
}

void showVistor() {
	osg::ref_ptr <osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr <osg::Group> rootGroup = new osg::Group;
	osg::ref_ptr <osg::Node> node = readNode("cow.osg");
	rootGroup->addChild(node.get());
	MVisitor mvisitor;
	/*accept(Nodevisitor)方法是osg::Node类中的，当调用accept函数时，访问器会根据访问类型和traverse(Nodevisitor)函数遍历节点，
	根据子节点或父节点的类型，调用访问器中对应的apply()函数，从而达到访问器的操作目的。*/
	rootGroup->accept(mvisitor);
	mvisitor.printMap();
	viewer->setSceneData(rootGroup.get());
	viewer->setUpViewOnSingleScreen();
	viewer->run();
}

int main()
{
	osg::ref_ptr <osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<CModelCallbackNode> callback = new CModelCallbackNode;
	MVisitor mVisitor;
	callback->accept(mVisitor);
	mVisitor.printMap();
	viewer->setSceneData(callback.get());
	viewer->setUpViewOnSingleScreen();
	viewer->run();
	return 0;
}

