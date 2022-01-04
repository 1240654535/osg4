#include <Windows.h>
#include <osg/Geode>
#include <osg/Point>
#include <osg/LineWidth>
#include <osg/TexGen>
#include <osg/TexEnv>

#include "PrimitiveObject.h"
#include <osg/CullFace>
CPrimitiveObject::CPrimitiveObject()
	:m_rpDrawArrays(nullptr)
	,m_rpVertexArray(nullptr)
	,m_rpGeo(nullptr)
	,m_rpTexture(nullptr)
	,m_dUnit(1.0)
{
	//(该类为重点部分)
	osg::ref_ptr<osg::Geode> rpGeode = new osg::Geode;
	//获取或创建状态集->设置模式；OVERRIDE让下面所有的子节 点都要受该影响
	rpGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);//关闭光照
	rpGeode->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);//打开混合模式，从而可以设置图元透明度、纹理等
	rpGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);//作用到所有节点
	//rpGeode->getOrCreateStateSet()->setRenderBinDetails(11,"DepthSortedBin");
	this->addChild(rpGeode.get());
	{
		//创建图元
		m_rpGeo = new osg::Geometry;
		//设置为true时，强制绘制方法使用OpenGL显示列表进行渲染。如果为false，则直接渲染。如果显示列表尚未编译，则下一次调用draw将自动创建显示列表。
		m_rpGeo->setUseDisplayList(false);
		//设置为true时，忽略setUseDisplayList（）设置，并提示drawImplementation方法使用OpenGL顶点缓冲区对象进行渲染。在osg:：Geometry中重新实现。
		m_rpGeo->setUseVertexBufferObjects(true);
		
		//创建顶点集
		m_rpVertexArray = new osg::Vec3Array;
		//设置顶点数组
		m_rpGeo->setVertexArray(m_rpVertexArray.get());

		//创建颜色集
		osg::ref_ptr<osg::Vec4Array> rpColorArray = new osg::Vec4Array;
		rpColorArray->push_back(osg::Vec4(1.0,1.0,1.0,1.0));
		m_rpGeo->setColorArray(rpColorArray.get(),osg::Array::BIND_OVERALL);//绑定方式，和每一个顶点都绑定

		//贴纹理
		osg::ref_ptr<osg::Image> rpImage = FeCommon::readImage("Images/land_shallow_topo_2048.jpg");
		m_rpTexture = new osg::Texture2D;
		//设置成动态，可以动态刷新
		m_rpTexture->setDataVariance(Object::DYNAMIC);
		//设置图片
		m_rpTexture->setImage(rpImage.get());//将图片设置到纹理上
		m_rpTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);//x轴重复纹理绘制
		m_rpTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);//y轴重复纹理绘制
		m_rpTexture->setWrap(osg::Texture::WRAP_R, osg::Texture::REPEAT);//z轴重复纹理绘制
		m_rpTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);//纹理渲染层级模式
		m_rpTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

		//创建自动生成纹理坐标节点
		osg::ref_ptr<osg::TexGen> rpTexGen = new osg::TexGen;
		rpTexGen->setMode(osg::TexGen::OBJECT_LINEAR);//设置模式为对象线性
		m_rpGeo->getOrCreateStateSet()->setTextureAttributeAndModes(0,rpTexGen.get(),osg::StateAttribute::ON);
		m_rpGeo->getOrCreateStateSet()->setTextureAttributeAndModes(0,m_rpTexture.get(),osg::StateAttribute::ON);
		
		//添加图元
		m_rpDrawArrays = new osg::DrawArrays();
		m_rpGeo->addPrimitiveSet(m_rpDrawArrays.get());//设置顶点连接方式
		osg::ref_ptr<osg::Point> rpPoint = new osg::Point(1);
		m_rpGeo->getOrCreateStateSet()->setAttribute(rpPoint.get(),osg::StateAttribute::ON);
		osg::ref_ptr<osg::LineWidth> rpLineWidth = new osg::LineWidth(1);
		m_rpGeo->getOrCreateStateSet()->setAttribute(rpLineWidth.get(),osg::StateAttribute::ON);

		//设置背部剔除看不见背面东西
		/*osg::ref_ptr<osg::CullFace> cullface=new osg::CullFace(osg::CullFace::FRONT);
		m_rpGeo->getOrCreateStateSet()->setAttribute(cullface.get());
		m_rpGeo->getOrCreateStateSet()->setMode(GL_CULL_FACE,osg::StateAttribute::ON);*/
		rpGeode->addDrawable(m_rpGeo.get());
		setPrimitive(osg::PrimitiveSet::POLYGON);
	}
}

CPrimitiveObject::~CPrimitiveObject()
{

}
//外面传进来模式Mode作为参数
void CPrimitiveObject::setPrimitive( osg::PrimitiveSet::Mode mode )
{
	m_rpVertexArray->clear();
	switch(mode)
	{
	//根据传入的模式绘制不同图元
	case osg::PrimitiveSet::POINTS:
	case osg::PrimitiveSet::LINES:
	case osg::PrimitiveSet::LINE_STRIP:
	case osg::PrimitiveSet::LINE_LOOP:
		{
			m_rpVertexArray->push_back(osg::Vec3(0*m_dUnit,0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(1*m_dUnit,0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(2*m_dUnit,0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(3*m_dUnit,0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(4*m_dUnit,0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(4*m_dUnit,2*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(3*m_dUnit,2*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(2*m_dUnit,2*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(1*m_dUnit,2*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(0*m_dUnit,2*m_dUnit,0));
			break;
		}
	case osg::PrimitiveSet::TRIANGLES:
		{
			m_rpVertexArray->push_back(osg::Vec3(-2*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit, 1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 2*m_dUnit,-1*m_dUnit,0));
			break;
		}
	case osg::PrimitiveSet::TRIANGLE_STRIP:
	case osg::PrimitiveSet::QUAD_STRIP:
		{
			m_rpVertexArray->push_back(osg::Vec3(-2*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-2*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 2*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 2*m_dUnit, 0*m_dUnit,0));
			break;
		}
	case osg::PrimitiveSet::TRIANGLE_FAN:
		{
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			break;
		}
	case osg::PrimitiveSet::QUADS:
		{
			m_rpVertexArray->push_back(osg::Vec3(-2*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-2*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3(-1*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit,-1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit,-1*m_dUnit,0));
			break;
		}
	case osg::PrimitiveSet::POLYGON:
		{
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 0*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 1*m_dUnit, 1*m_dUnit,0));
			m_rpVertexArray->push_back(osg::Vec3( 0*m_dUnit, 1*m_dUnit,0));
			break;
		}
	}
	m_rpVertexArray->dirty();//更新点集
	m_rpDrawArrays->setMode(mode);//图元设置
	m_rpDrawArrays->setCount(m_rpVertexArray->size());//设置关键点数量
	//CTextureGenerator textureGenerator;
	//this->accept(textureGenerator);
	m_rpGeo->dirtyBound();//更新图元
}

void CPrimitiveObject::setPointSize( int nSize )
{
	osg::ref_ptr<osg::Point> rpPoint = dynamic_cast<osg::Point*>(m_rpGeo->getOrCreateStateSet()->getAttribute(osg::StateAttribute::POINT));
	if (rpPoint.valid())
	{
		rpPoint->setSize(nSize);
	}
}

void CPrimitiveObject::setLineWidth( int nWidth )
{
	osg::ref_ptr<osg::LineWidth> rpLineWidth = dynamic_cast<osg::LineWidth*>(m_rpGeo->getOrCreateStateSet()->getAttribute(osg::StateAttribute::LINEWIDTH));
	if (rpLineWidth.valid())
	{
		rpLineWidth->setWidth(nWidth);
	}
}

void CPrimitiveObject::setColor( const osg::Vec4& vecColor )
{
	osg::ref_ptr<osg::Vec4Array> rpColorArray = dynamic_cast<osg::Vec4Array*>(m_rpGeo->getColorArray());
	if (rpColorArray.valid())
	{
		rpColorArray->clear();
		rpColorArray->push_back(vecColor);
		rpColorArray->dirty();
	}
}

void CPrimitiveObject::setTexture( bool bState )
{
	m_rpGeo->getOrCreateStateSet()->setTextureAttributeAndModes(0,m_rpTexture.get(),bState?osg::StateAttribute::ON:osg::StateAttribute::OFF);
}

