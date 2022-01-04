/**************************************************************************************************
* @file name 文件名:EventInteract.h
* @note 描述：事件交互
* @author 作者：z00105
* @data 创建时间：2020 -12 -10
**************************************************************************************************/
#ifndef HUD_RTT_CAMERA_H
#define HUD_RTT_CAMERA_H
#include <iostream>
#include <osg/Camera>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/Texture2D>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Geode>
#include <osgText/Text>
#include <osg/StateSet>
#include <osg/ImageSequence>
#include <osg/MatrixTransform>
#include <CommonLib/HudRtt/Export.h>
using namespace std;

/**
 * @class CUpdateViewPort
 * @brief 视口更新回调
 * @note 用于在窗口尺寸变化后，更新主相机视口和对应的附加纹理
*/
 class CUpdateViewPort : public osg::NodeCallback
 {
 public:
 	// 构造函数
 	CUpdateViewPort(osg::Camera* pMainCamera, osgViewer::Viewer * viewer)
 		: m_pMainCamera(pMainCamera)
		,m_pViewer(viewer)
 	{
 		m_nWidth = 0;
 		m_nHeight = 0;
 	}
 
 	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
 	{
 		if(m_pMainCamera && m_pViewer && m_pViewer->getCamera())
 		{
 			osg::Viewport* pViewport = m_pViewer->getCamera()->getViewport();
 			if((pViewport->width() != m_nWidth) || (pViewport->height() != m_nHeight))
 			{
 				// 当窗口尺寸变化后，保存信息
 				m_nWidth = pViewport->width();
 				m_nHeight = pViewport->height();
 
 				// 设置主相机视口和投影矩阵
 				double dFov, dAsp, dNear, fFar;
 				m_pMainCamera->getProjectionMatrixAsPerspective(dFov, dAsp, dNear, fFar);
 				m_pMainCamera->setProjectionMatrixAsPerspective(30.0f, m_nWidth / (double)m_nHeight, dNear, fFar);
 				m_pMainCamera->setViewport(0, 0, m_nWidth, m_nHeight);
 
 				// 更新主相机的附加对象尺寸
 				m_pMainCamera->resizeAttachments(m_nWidth, m_nHeight);
 				m_pMainCamera->dirtyAttachmentMap();
 			}
 		}
 
 		traverse(node, nv);
 	}
 
 	osg::Camera* m_pMainCamera;    // 场景主相机
 	osgViewer::Viewer * m_pViewer;
 
 	int m_nWidth, m_nHeight;  // 记录当前窗口尺寸
 };
 
  /**
 * @class 类名：CHUDProvider
 * @brief 简要说明：提供hud相机
 * @note详细说明：对hud相机和rtt相机进行封装，可通过函数直接获取
 * @author 作者：z00105
 */
class HUDRTT_EXPORT CHUDProvider
{
public:
	CHUDProvider(){};
	~CHUDProvider(){};

	//创建hud相机
	osg::Camera* createHUD();

	//创建纹理
	osg::Node* CreateTexture();

	//创建rtt相机
	osg::Camera* createRTT();

	//烘培纹理
	osg::Group* CreateRTTScale(osgViewer::Viewer * viewer);
protected:
	//做一个圆，并贴上纹理
	osg::Node* CreateNode(osg::Texture2D* t2d);

	//创建一个HUD，固定圆盘
	osg::Camera* CreateHUD(osg::Texture2D* t2d);

};
#endif
