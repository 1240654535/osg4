#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Node>
#include <osg/Material>
#include <osg/Notify>
#include <osg/Vec3>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/Texture3D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>

#include <osg/Program>
#include <osg/Shader>
#include <osg/Uniform>
#include <osgUtil/PerlinNoise>

#include <iostream>

#include <ShaderDemo.h>
#include "osg/BlendFunc"

///////////////////////////////////////////////////////////////////////////
//制作一维正弦图像
static osg::Image* make1DSineImage( int nTexSize )
{
    const float cons_fPI = 3.1415927;

    osg::Image* pImage = new osg::Image;
    pImage->setImage(nTexSize, 1, 1,
            4, GL_RGBA, GL_UNSIGNED_BYTE,
            new unsigned char[4 * nTexSize],
            osg::Image::USE_NEW_DELETE);

    GLubyte* pData = pImage->data();
    float fDelta = 2. * cons_fPI / (float)nTexSize;
    for(int i = 0; i < nTexSize; i++)
    {
        *pData++ = (GLubyte)((sinf(i * fDelta) * 0.5 + 0.5) * 255.);
        *pData++ = 0;
        *pData++ = 0;
        *pData++ = 1;
    }
    return pImage;
}

//制作一维纹理，大理石着色器会使用
static osg::Texture1D* make1DSineTexture( int nTexSize )
{
    osg::Texture1D* pSineTexture = new osg::Texture1D;
    pSineTexture->setWrap(osg::Texture1D::WRAP_S, osg::Texture1D::REPEAT);
    pSineTexture->setFilter(osg::Texture1D::MIN_FILTER, osg::Texture1D::LINEAR);
    pSineTexture->setFilter(osg::Texture1D::MAG_FILTER, osg::Texture1D::LINEAR);
    pSineTexture->setImage( make1DSineImage(nTexSize) );
    return pSineTexture;
}

///////////////////////////////////////////////////////////////////////////
// 简单着色器的内嵌glsl源码示例
//varying 标识的变量在点元中定义，在片元中使用
//gl_Vertex:gl语言自带的变量，标识当前点的位置
//color:点元定义的变量，用于设置颜色值
//gl_Position:gl自带的变量
static const char *s_cMicroshaderVertSource = {
    "// 根据碎片的位置给它着色\n"
    "varying vec4 color;\n"
    "void main(void)\n"
    "{\n"
    "    color = gl_Vertex;\n"
	"	 color.a = 0.5;\n"
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
    "}\n"
};

//片元着色器
//基于点元着色器的一些变量varying
//片元的颜色由color插值生成
static const char *s_cMicroshaderFragSource = {
    "varying vec4 color;\n"
    "void main(void)\n"
	"{\n"
    "    gl_FragColor = clamp( color, 0.0, 1.0);\n"
    "}\n"
};


// 创建一些要在其上渲染GLSL着色器的几何体
osg::Geode* CGlBuilder::createModel()
{
    osg::Geode* pGeode = new osg::Geode();
    pGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),1.0f)));//创建球
    pGeode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(2.2f,0.0f,-0.4f),0.9f,1.8f)));//创建圆锥
    pGeode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(4.4f,0.0f,0.0f),1.0f,1.4f)));//创建圆柱
    return pGeode;
}

//添加模型的指针，返回其StateSet，以便关联StateAttributes
osg::StateSet* CGlBuilder::modelInstance()
{
    //float fZvalue = 0.0f;
    osg::Node* s_pMasterModel = createModel();

    osg::PositionAttitudeTransform* pPosMtform = new osg::PositionAttitudeTransform();
    pPosMtform->setPosition(osg::Vec3( 0.0f, -1.0f, m_fZvalue ));
    m_fZvalue = m_fZvalue + 2.2f;
    pPosMtform->addChild(s_pMasterModel);
    m_rpShaderNode->addChild(pPosMtform);
    return pPosMtform->getOrCreateStateSet();
}

// 通过文件添加shader
void CGlBuilder::loadShaderSource( osg::Shader* pShader, const std::string& strSourceFileName )
{
	if (!pShader)
	{
		return;
	}
    std::string strFileName = osgDB::findDataFile(strSourceFileName);
    if( strFileName.length() != 0 )
    {
        pShader->loadShaderSourceFromFile( strFileName.c_str() );
    }
    else
    {
        osg::notify(osg::WARN) << "File \"" << strFileName << "\" not found." << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////
//用GLSL着色器的示例组成场景图

#define TEXUNIT_SINE        1
#define TEXUNIT_NOISE        2

osg::ref_ptr<osg::Group> CGlBuilder::buildShaders()
{
    osg::Texture3D* pNoiseTexture = osgUtil::create3DNoiseTexture( 32 /*128*/ );

    // 根节点
    m_rpShaderNode = new osg::Group;

	bool bDebugTest  = true; // = false;//
    // 关联一些uniform变量到根节点, 由程序继承
    {
        osg::Uniform* pOffsetUniform = new osg::Uniform( "Offset", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* pSineUniform   = new osg::Uniform( "Sine", 0.0f );
        osg::Uniform* pColor1Uniform = new osg::Uniform( "Color1", osg::Vec3(0.0f, 0.0f, 0.0f) );
        osg::Uniform* pColor2Uniform = new osg::Uniform( "Color2", osg::Vec3(0.0f, 0.0f, 0.0f) );

        pOffsetUniform->setUpdateCallback(new CAnimateCallback(CAnimateCallback::OFFSET));
        pSineUniform->setUpdateCallback(new CAnimateCallback(CAnimateCallback::SIN));
        pColor1Uniform->setUpdateCallback(new CAnimateCallback(CAnimateCallback::COLOR1));
        pColor2Uniform->setUpdateCallback(new CAnimateCallback(CAnimateCallback::COLOR2));

		osg::StateSet* pState = m_rpShaderNode->getOrCreateStateSet();
		osg::ref_ptr<osg::BlendFunc> rpBlendFunc = new osg::BlendFunc();//混合功能
		pState->setAttributeAndModes(rpBlendFunc.get(),osg::StateAttribute::PROTECTED | osg::StateAttribute::ON );//添加混合功能属性
		pState->addUniform( pOffsetUniform );
		pState->addUniform( pSineUniform );
		pState->addUniform( pColor1Uniform );
		pState->addUniform( pColor2Uniform );
    }

	// 简单的微阴影（源码写在本文件前面）
	//if (bDebugTest)
    {
        osg::StateSet* pState = modelInstance();
        osg::Program* pProgram = new osg::Program;
        pProgram->setName( "microshader" );
        //m_vecProgramList.push_back( pProgram );
        pProgram->addShader( new osg::Shader( osg::Shader::VERTEX, s_cMicroshaderVertSource ) );
        pProgram->addShader( new osg::Shader( osg::Shader::FRAGMENT, s_cMicroshaderFragSource ) );
        pState->setAttributeAndModes( pProgram, osg::StateAttribute::ON );
    }

	// 块状着色器，一个简单的动画测试
	if (bDebugTest)
    {
        osg::StateSet* pState = modelInstance();
        static osg::Program* pBlockyProgram = new osg::Program;
        pBlockyProgram->setName( "blocky" );
        m_vecProgramList.push_back( pBlockyProgram );
        m_pBlockyVertObj = new osg::Shader( osg::Shader::VERTEX );
        m_pBlockyFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        pBlockyProgram->addShader( m_pBlockyFragObj );
        pBlockyProgram->addShader( m_pBlockyVertObj );
        pState->setAttributeAndModes(pBlockyProgram, osg::StateAttribute::ON);
    }

	// 侵蚀着色器使用噪波纹理来丢弃碎片
	if (bDebugTest)
    {
        osg::StateSet* pState = modelInstance();
        pState->setTextureAttribute(TEXUNIT_NOISE, pNoiseTexture);
        osg::Program* pErodedProgram = new osg::Program;
        pErodedProgram->setName( "eroded" );
        m_vecProgramList.push_back( pErodedProgram );
		m_pErodedVertObj = new osg::Shader( osg::Shader::VERTEX );
		m_pErodedFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        pErodedProgram->addShader( m_pErodedFragObj );
        pErodedProgram->addShader( m_pErodedVertObj );
        pState->setAttributeAndModes(pErodedProgram, osg::StateAttribute::ON);

        pState->addUniform( new osg::Uniform("LightPosition", osg::Vec3(0.0f, 0.0f, 4.0f)) );
        pState->addUniform( new osg::Uniform("Scale", 1.0f) );
        pState->addUniform( new osg::Uniform("sampler3d", TEXUNIT_NOISE) );
    }

	//大理石着色器使用两种纹理
	if (bDebugTest)
	{
		osg::Texture1D* pSineTexture = make1DSineTexture( 32 /*1024*/ );
        osg::StateSet* pState = modelInstance();
        pState->setTextureAttribute(TEXUNIT_NOISE, pNoiseTexture);
        pState->setTextureAttribute(TEXUNIT_SINE, pSineTexture);
        osg::Program* pMarbleProgram = new osg::Program;
        pMarbleProgram->setName( "marble" );
        m_vecProgramList.push_back( pMarbleProgram );
        m_pMarbleVertObj = new osg::Shader( osg::Shader::VERTEX );
        m_pMarbleFragObj = new osg::Shader( osg::Shader::FRAGMENT );
        pMarbleProgram->addShader( m_pMarbleFragObj );
        pMarbleProgram->addShader( m_pMarbleVertObj );
        pState->setAttributeAndModes(pMarbleProgram, osg::StateAttribute::ON);

        pState->addUniform( new osg::Uniform("NoiseTex", TEXUNIT_NOISE) );
        pState->addUniform( new osg::Uniform("SineTex", TEXUNIT_SINE) );
    }
    reloadShaderSource();
    return m_rpShaderNode;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

CGlBuilder::CGlBuilder()
	:m_fZvalue(0.0)
	,m_pBlockyVertObj(NULL)
	,m_pBlockyFragObj(NULL)
	,m_pErodedVertObj(NULL)
	,m_pErodedFragObj(NULL)
	,m_pMarbleVertObj(NULL)
	,m_pMarbleFragObj(NULL)
{
	m_rpRootNode = buildShaders();
}

CGlBuilder::~CGlBuilder()
{
}

void CGlBuilder::reloadShaderSource()
{
    osg::notify(osg::INFO) << "reloadShaderSource()" << std::endl;

	loadShaderSource( m_pBlockyVertObj, "shaders/blocky.vert" );
	loadShaderSource( m_pBlockyFragObj, "shaders/blocky.frag" );
					  
	loadShaderSource( m_pErodedVertObj, "shaders/eroded.vert" );
	loadShaderSource( m_pErodedFragObj, "shaders/eroded.frag" );
					  
	loadShaderSource( m_pMarbleVertObj, "shaders/marble.vert" );
	loadShaderSource( m_pMarbleFragObj, "shaders/marble.frag" );
}
