// Day02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include <CommonLib/Common/Common.h>
#include <windows.h>
#include <iostream>

#include <osg/MatrixTransform>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>

#include <osgDB/ReadFile>
#include <osg/BlendColor>
#include <osg/BlendFunc>
/**
  * @brief 简要说明：读取模型
  * @note 详细说明：根据路径，读取模型
  * @param strPath [in]：路径信息，要求绝对路径
  * @return ：模型指针
*/
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
/**
	  * @brief 简要说明：设置模型颜色
	  * @note 详细说明：通过给出模型指针和目标颜色数值，修改模型的显示颜色
	  * @param pNode [in]：目标模型
	  * @param vecColor [in]：目标颜色值
	  * @return 返回值以及说明：
	*/
void setColor(osg::Node* pNode, osg::Vec4 vecColor)
{
	osg::StateSet* StateSet = pNode->getOrCreateStateSet();//获取节点状态设置
	osg::ref_ptr<osg::BlendColor> rpBlendColor = new osg::BlendColor();//混合颜色
	osg::ref_ptr<osg::BlendFunc> rpBlendFunc = new osg::BlendFunc();//混合功能
	StateSet->setAttributeAndModes(rpBlendFunc.get(), osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);//添加混合功能属性
	StateSet->setAttributeAndModes(rpBlendColor.get(), osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);//添加混合颜色属性
	rpBlendFunc->setSource(osg::BlendFunc::ONE_MINUS_CONSTANT_COLOR);//一减常量颜色
	rpBlendFunc->setDestination(osg::BlendFunc::ONE_MINUS_CONSTANT_ALPHA);//一减常量透明度
	osg::Vec4 vecColorNew = osg::Vec4(1.0, 1.0, 1.0, 1.0) - vecColor;
	vecColorNew.a() = vecColor.a();
	rpBlendColor->setConstantColor(vecColorNew);//设置颜色
}
//第二天实践作业单独封装到函数,加载多个模型，并排列成一个圆，模型头部指向圆心。
void HomeWork2() {
	osg::ref_ptr<osgViewer::Viewer> hViewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> hGroup = new osg::Group;
	osg::ref_ptr<osg::Node> hCow = readNode("cow.osg");
	
	for (float i = 0.0; i < 360; i+=60)
	{
		osg::ref_ptr<osg::MatrixTransform> hMt = new osg::MatrixTransform;
		//先自转，再平移，再旋转
		hMt->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(180.0),osg::Vec3(0,0,1)) *osg::Matrix::translate(10, 0, 0)*osg::Matrix::rotate(osg::DegreesToRadians(0.0+i),osg::Vec3(0,0,1)));
		hMt->addChild(hCow.get());
		setColor(hMt.get(), osg::Vec4(1.0, 0.0, 0.0, 1.0));
		hGroup->addChild(hMt.get());
	}
	hViewer->setSceneData(hGroup.get());
	hViewer->setUpViewOnSingleScreen();
	hViewer->run();
}
int main()
{
	osg::ref_ptr<osgViewer::Viewer> rpViewer = new osgViewer::Viewer;
	//这里是将Group设为根节点，判断方法是后面的rpViewer->setSceneData(rpGroup.get());
	osg::ref_ptr<osg::Group> rpGroup = new osg::Group;
	//思想，模型加载进来相当于原材料，后面用的时候进行变化修改，再将变换好的"产品"加载到场景树中
	osg::ref_ptr<osg::Node> rpCow = readNode("cow.osg");
	rpGroup->addChild(rpCow.get());
	{
		osg::ref_ptr<osg::MatrixTransform> rpMT = new osg::MatrixTransform;
		rpMT->setMatrix(osg::Matrix::translate(0, 0, 10));//朝0,0,10方向移动，即朝z轴的正方向移动10单位
		rpMT->addChild(rpCow.get());
		//红色
		setColor(rpMT.get(), osg::Vec4(1.0, 0.0, 0.0, 1.0));
		rpGroup->addChild(rpMT.get());
	}
	{
		//矩阵旋转关键函数为osg::Matrix::rotate，并且根据重载的方法，入参也各不相同
		//实例中为：绕（0，0，1）轴（Z轴），旋转90.0角度，即绕z轴旋转90.0角度
		//X轴：osg::X_AXIS本质是：const Vec3f X_AXIS(1.0,0.0,0.0); 还有osg::Y_AXIS等
		//矩阵平移osg::Matrix::translate
		//osg::Matrix::translate(10,0,0)，即按照x轴正方向平移10个单位；osg::Matrix::rotate(参数一：旋转弧度，参数二：轴)；
		osg::ref_ptr<osg::MatrixTransform> rpMTRT = new osg::MatrixTransform;
		//先旋转再平移，旋转九十度，
		rpMTRT->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1))*osg::Matrix::translate(10, 0, 0));
		rpMTRT->addChild(rpCow.get());
		//绿色
		setColor(rpMTRT.get(), osg::Vec4(0.0, 1.0, 0.0, 1.0));
		rpGroup->addChild(rpMTRT.get());

		osg::ref_ptr<osg::MatrixTransform> rpMTTR = new osg::MatrixTransform;
		//先平移再旋转
		rpMTTR->setMatrix(osg::Matrix::translate(10, 0, 0)*osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1)));
		rpMTTR->addChild(rpCow.get());
		//蓝色
		setColor(rpMTTR.get(), osg::Vec4(0.0, 0.0, 1.0, 1.0));
		rpGroup->addChild(rpMTTR.get());
	}
	{
		//矩阵缩放，osg::Matrix::scale
		//osg::Matrix::scale(10,10,10)，按照x，y，z三个轴方向放大10倍，少放大某个方向会导致变形
		osg::ref_ptr<osg::MatrixTransform> rpMTRT = new osg::MatrixTransform;
		rpMTRT->setMatrix(osg::Matrix::scale(10, 10, 10)*osg::Matrix::rotate(osg::DegreesToRadians(90.0), osg::Vec3(0, 0, 1))*osg::Matrix::translate(50, 0, 0));
		rpMTRT->addChild(rpCow.get());
		setColor(rpMTRT.get(), osg::Vec4(1.0, 1.0, 0.0, 1.0));
		rpGroup->addChild(rpMTRT.get());
	}
	rpViewer->setSceneData(rpGroup.get());
	rpViewer->addEventHandler(new osgViewer::StatsHandler);
	rpViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	rpViewer->addEventHandler(new osgGA::StateSetManipulator(rpViewer->getCamera()->getOrCreateStateSet()));
	//解决双屏问题，只在单独的屏幕显示
	rpViewer->setUpViewOnSingleScreen();
	return rpViewer->run();


}

