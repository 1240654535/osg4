/**************************************************************************************************
* @file name 文件名:ManupulatorTest.h
* @note 描述：自定义操作器编写示例
* @author 作者：z00105
* @data 创建时间：2020 -12 -23
**************************************************************************************************/

#include <osgGA/CameraManipulator>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include "Export.h"

class MANUPULATOR_EXPORT CDriveManupulator: public osgGA::CameraManipulator
{
public:
	CDriveManupulator();

	osg::Node* getBallNode(){return m_rpMtBall.get();}

	//必须重写的四个相机操作器函数
	virtual void setByMatrix(const osg::Matrixd& matrix){}

	virtual void setByInverseMatrix(const osg::Matrixd& matrix){}

	virtual osg::Matrixd getMatrix() const
	{
		osg::Matrixd mat;
		mat.makeRotate(m_vecRotation.x(), osg::Vec3(1.0, 0.0, 0.0),
			m_vecRotation.y(), osg::Vec3(0.0, 1.0, 0.0),
			m_vecRotation.z(), osg::Vec3(0.0, 0.0, 1.0));
		return mat * osg::Matrixd::translate(m_vecPosition);
	}

	virtual osg::Matrixd getInverseMatrix() const
	{
		osg::Matrixd mat;
		mat.makeRotate(m_vecRotation.x(), osg::Vec3(1.0, 0.0, 0.0),
			m_vecRotation.y(), osg::Vec3(0.0, 1.0, 0.0),
			m_vecRotation.z(), osg::Vec3(0.0, 0.0, 1.0));
		return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vecPosition));
	}

	/**
	  * @brief 简要说明：相机移动函数
	  * @note 详细说明：
	  * @param 参数1 [in/out/inout]：移动距离
	  * @return 返回值以及说明：
	*/
	void ChangePosition(osg::Vec3 vec3Delta);

	/**
	  * @brief 简要说明：小球前后移动函数
	  * @note 详细说明：
	  * @param 参数1 [in/out/inout]：移动距离
	  * @return 返回值以及说明：
	*/
	void ChangePositionCar(osg::Vec3 vec3Delta);

	/**
	  * @brief 简要说明：小球左右移动函数
	  * @note 详细说明：
	  * @param 参数1 [in/out/inout]：移动距离
	  * @return 返回值以及说明：
	*/
	void ChangePositionCarLeftRight(osg::Vec3 vec3Delta);

	/**
	  * @brief 简要说明：重写事件处理
	  * @note 详细说明：
	  * @return 返回值以及说明：
	*/
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

private:
	osg::Vec3							m_vecPosition;		//相机位置
	osg::Vec3							m_vecRotation;		//相机姿态
	float								m_fMoveSpeed;		//移动速度
	float								m_fAnglg;			//变化角度
	osg::Vec3							m_vecBallPosition;	//小球位置
	osg::ref_ptr<osg::MatrixTransform>	m_rpMtBall;			//小球矩阵

};
