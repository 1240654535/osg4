/**************************************************************************************************
* @file name 文件名:ShaderDemo.h
* @note 描述：shader的应用实例库
* @author 作者：z00105
* @data 创建时间：2021 -3 -1
**************************************************************************************************/
#include <osg/Node>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Program>
#include "Export.h"


/**
* @class 类名：CAnimateCallback
* @brief 简要说明：为了演示的简单性，这个回调会设置所有着色器的动画
* @note详细说明：
* @author 作者：z00105
*/
class CAnimateCallback: public osg::UniformCallback
{
public:

	enum EOperation
	{
		OFFSET,//位移
		SIN,//正弦值
		COLOR1,//颜色值1
		COLOR2//颜色值2
	};

	CAnimateCallback(EOperation op) : m_bEnabled(true),m_eOperation(op) {}

	virtual void operator() ( osg::Uniform* pUniform, osg::NodeVisitor* pNv )
	{
		if( m_bEnabled )
		{
			float fAngle = 2.0 * pNv->getFrameStamp()->getSimulationTime();//渲染仿真时间
			float fSine = sinf( fAngle );        // -1 -> 1
			float fV01 = 0.5f * fSine + 0.5f;        //  0 -> 1
			float fV10 = 1.0f - fV01;                //  1 -> 0
			switch(m_eOperation)
			{
			case OFFSET : 
				pUniform->set( osg::Vec3(0.505f, 0.8f*fV01, 0.0f) );
				break;
			case SIN :
				pUniform->set( fSine ); break;
			case COLOR1 : 
				pUniform->set( osg::Vec3(fV10, 0.0f, 0.0f) );
				break;
			case COLOR2 : 
				pUniform->set( osg::Vec3(fV01, fV01, fV10) );
				break;
			}
		}
	}

private:
	bool m_bEnabled;//是否可回调
	EOperation m_eOperation;//更新哪种参数
};

/**
* @class 类名：CGlBuilder
* @brief 简要说明：着色器构造
* @note详细说明：
* @author 作者：z00105
*/
class SHADER_EXPORT CGlBuilder : public osg::Referenced
{
    public:
	CGlBuilder();

	/**
	  * @brief 简要说明：获取根节点
	  * @note 详细说明：
	  * @param m_rpRootNode [in]：场景根节点
	  * @return m_rpRootNode
	*/
	osg::ref_ptr<osg::Group> getRootNode() { return m_rpRootNode; }

	/**
	  * @brief 简要说明：重新加载着色器源
	  * @note 详细说明：
	  * @return 
	*/
	void reloadShaderSource();
protected:
	//析构函数
	~CGlBuilder();

	/**
	  * @brief 简要说明：创建模型
	  * @note 详细说明：包括三个基本的图元
	  * @return Geode
	*/
	osg::Geode* createModel();

	/**
	  * @brief 简要说明：模型创建后的属性设置
	  * @note 详细说明：在内部创建模型并加入根节点，将创建的模型属性设置返回
	  * @return StateSet
	*/
	osg::StateSet* modelInstance();

	/**
	  * @brief 简要说明：创建着色器
	  * @note 详细说明：生成所有节点
	  * @return Group
	*/
	osg::ref_ptr<osg::Group> buildShaders();

	/**
	  * @brief 简要说明：通过shader指针和shader文件路径，初始化shader
	  * @note 详细说明：通过文件添加shader
	  * @param pShader [in]：着色器
	  * @param strSourceFileName [in]：着色器文件路径
	  * @return 
	*/
	void loadShaderSource( osg::Shader* pShader, const std::string& strSourceFileName );
    
private:
	osg::ref_ptr<osg::Group> m_rpRootNode;//场景根节点
	osg::ref_ptr<osg::Group> m_rpShaderNode;//shader图元根节点
	std::vector< osg::ref_ptr<osg::Program> > m_vecProgramList;//程序列表
	//各类点元和片元着色器
	osg::Shader*  m_pBlockyVertObj;//块着色器点元对象
	osg::Shader*  m_pBlockyFragObj;//块着色器片元对象
	osg::Shader*  m_pErodedVertObj;//侵蚀着色器点元对象
	osg::Shader*  m_pErodedFragObj;//侵蚀着色器片元对象
	osg::Shader*  m_pMarbleVertObj;//大理石着色器点元对象
	osg::Shader*  m_pMarbleFragObj;//大理石着色器片元对象
	float		  m_fZvalue;//z方向的高度
};

