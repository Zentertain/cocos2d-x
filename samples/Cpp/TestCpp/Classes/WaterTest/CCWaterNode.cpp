//
//  CCWaterNode.cpp
//  TestCpp
//
//  Created by 姚春晖 on 14-4-24.
//
//

#include "CCWaterNode.h"

USING_NS_CC;

inline float GetLength(const cocos2d::ccVertex3F& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline cocos2d::ccVertex3F Normalize(const cocos2d::ccVertex3F& v)
{
    cocos2d::ccVertex3F r = {0, 0, 0};
    float fLen = GetLength(v);
    if (fLen == 0.0f)
        return r;
    r.x = v.x / fLen;
    r.y = v.y / fLen;
    r.z = v.z / fLen;
    return r;
}

inline float fracf(float f)
{
    return f - floorf(f);
}


static const char* s_szShaderVS =
"														\n\
attribute vec4 a_position;								\n\
attribute vec4 a_texCoord;								\n\
uniform vec4 u_texOffset;                               \n\
uniform vec4 u_texScale;                                \n\
uniform vec3 u_eyePos;                                  \n\
\n\
#ifdef GL_ES											\n\
varying mediump vec4 v_texCoord;                        \n\
varying mediump vec3 v_eyeDir;                          \n\
varying lowp vec3 v_color;                              \n\
uniform lowp vec4 u_color;								\n\
#else													\n\
varying vec4 v_texCoord;                                \n\
varying vec3 v_eyeDir;                                  \n\
varying vec3 v_color;                                   \n\
uniform vec4 u_color;                                   \n\
#endif													\n\
\n\
void main()												\n\
{														\n\
gl_Position = CC_MVPMatrix * a_position;			\n\
vec2 worldPos = gl_Position.xy / gl_Position.w;     \n\
v_eyeDir = u_eyePos - vec3(worldPos, 0.0);          \n\
float grad = mix(0.3, 1.1, (worldPos.y + 1.0) * 0.5);\n\
v_color = u_color.xyz * grad; \n\
v_texCoord = vec4(a_texCoord.xy, a_texCoord.xy) * u_texScale + u_texOffset; \n\
}														\n\
";

static const char* s_szShaderFS =
"																		\n\
#ifdef GL_ES															\n\
precision mediump float;													\n\
#endif																	\n\
\n\
#ifdef GL_ES											\n\
varying mediump vec4 v_texCoord;                        \n\
varying mediump vec3 v_eyeDir;                          \n\
varying lowp vec3 v_color;                              \n\
#else													\n\
varying vec4 v_texCoord;                                \n\
varying vec3 v_eyeDir;                                  \n\
varying vec3 v_color;                               \n\
#endif													\n\
\n\
uniform sampler2D u_normalmap;							\n\
uniform vec3 u_lightDir;								\n\
\n\
void main()												\n\
{														\n\
vec3 eyeDir = normalize(v_eyeDir);                  \n\
vec3 halfDir = normalize(eyeDir + u_lightDir);      \n\
\n\
vec3 normal1 = texture2D(u_normalmap, v_texCoord.xy).xyz * 2.0 - 1.0;          \n\
vec3 normal2 = texture2D(u_normalmap, v_texCoord.zw).xyz * 2.0 - 1.0;          \n\
vec3 normal =  normalize(normal1  + normal2 * 0.6);     \n\
float dt1 = pow(max(0.0, dot(halfDir, normal)), 30.0);  \n\
vec3 spec1 = vec3(0.8, 0.5, 0.2) * dt1;                 \n\
float ndotv = max(0.0, dot(normal, eyeDir));          \n\
float dt2 = pow(ndotv, 3.0);                          \n\
vec3 spec2 = vec3(0.3, 0.5, 0.4) * dt2;               \n\
vec3 color = v_color.xyz;                               \n\
//vec3 color = mix(v_color.xyz, spec2, ndotv * 0.4);    \n\
gl_FragColor =  vec4(color + spec1, 1.0);               \n\
//gl_FragColor =  vec4(v_pos.zw, 0.0, 1.0);             \n\
//gl_FragColor =  vec4(u_lightDir, 1.0);                \n\
}                                                           \n\
";


CCWaterNode::CCWaterNode()
{
    m_pProgram = NULL;
    m_pNormalMap = NULL;
    m_vLightDir = Normalize(vertex3(-1.3f, 2.0f, 1.5f));
    m_vNormal = vertex3(0, 0, 1);
    m_vEyePos = vertex3(0, -1.6f, 0.1f);
    m_fTexSize[0] = 150;
    m_fTexSize[1] = 150;
    m_fTexSize[2] = 30;
    m_fTexSize[3] = 30;
    
    m_fTexSpeed[0] = 4;
    m_fTexSpeed[1] = -2;
    m_fTexSpeed[2] = -0.5f;
    m_fTexSpeed[3] = 1.5f;
}

CCWaterNode::~CCWaterNode()
{
    CC_SAFE_RELEASE(m_pProgram);
    CC_SAFE_RELEASE(m_pNormalMap);
}

CCWaterNode* CCWaterNode::create(float w, float h, cocos2d::CCTexture2D *pNormalMap)
{
    CCWaterNode* pNode = new CCWaterNode();
    pNode->init(w, h, pNormalMap);
    pNode->autorelease();
    return pNode;
}

bool CCWaterNode::init(float w, float h, cocos2d::CCTexture2D* pNormalMap)
{
	CCGLProgram* pProgram = new CCGLProgram();
	pProgram->autorelease();
	if (!pProgram->initWithVertexShaderByteArray(s_szShaderVS, s_szShaderFS))
	{
        CCAssert(false, "Load shader error!");
		return false;
	}
    
	pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	if (!pProgram->link())
    {
        CCAssert(false, "Link shader error!");
        return false;
    }
	pProgram->updateUniforms();
    
    m_iUnifLightDir = pProgram->getUniformLocationForName("u_lightDir");
    m_iUnifTexOffset = pProgram->getUniformLocationForName("u_texOffset");
    m_iUnifTexScale = pProgram->getUniformLocationForName("u_texScale");
    m_iUnifNormalMap = pProgram->getUniformLocationForName("u_normalmap");
    m_iUnifEyePos = pProgram->getUniformLocationForName("u_eyePos");
    m_iUnifColor = pProgram->getUniformLocationForName("u_color");
    
    if (CCNode::init())
    {
        for (size_t i = 0; i < 4; i++ )
        {
            m_aVertices[i].x = 0.0f;
            m_aVertices[i].y = 0.0f;
        }
        
        m_aTexcoords[0] = vertex2(0, 0);
        m_aTexcoords[1] = vertex2(1, 0);
        m_aTexcoords[2] = vertex2(0, 1);
        m_aTexcoords[3] = vertex2(1, 1);
        
        setShaderProgram(pProgram);
        m_pProgram = pProgram;
        m_pProgram->retain();
        m_pNormalMap = pNormalMap;
        m_pNormalMap->retain();
        ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        m_pNormalMap->setTexParameters(&params);
        
        memset(m_fTexOffset, 0, sizeof(m_fTexOffset));
        setContentSize(CCSize(w, h));
    }
    
    this->schedule(schedule_selector(CCWaterNode::Update));
    
    return true;
}

void CCWaterNode::setNormalMap(cocos2d::CCTexture2D *pTexture)
{
    CC_SAFE_RETAIN(pTexture);
    CC_SAFE_RELEASE(m_pNormalMap);
    m_pNormalMap = pTexture;
    ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    m_pNormalMap->setTexParameters(&params);
}

/// override contentSize
void CCWaterNode::setContentSize(const CCSize & size)
{
    m_aVertices[1].x = size.width;
    m_aVertices[2].y = size.height;
    m_aVertices[3].x = size.width;
    m_aVertices[3].y = size.height;
    
    CCNode::setContentSize(size);
}

void CCWaterNode::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pNormalMap->getName());
    
    m_pProgram->setUniformLocationWith1i(m_iUnifNormalMap, 0);
    m_pProgram->setUniformLocationWith3fv(m_iUnifLightDir, &m_vLightDir.x, 1);
    m_pProgram->setUniformLocationWith3fv(m_iUnifEyePos, &m_vEyePos.x, 1);
    m_pProgram->setUniformLocationWith4f(m_iUnifColor,
                                         _displayedColor.r / 255.0f,
                                         _displayedColor.g / 255.0f,
                                         _displayedColor.b / 255.0f,
                                         _displayedOpacity / 255.0f);
    m_pProgram->setUniformLocationWith4f(m_iUnifTexOffset,
                                         fracf(m_fTexOffset[0] / m_fTexSize[0]),
                                         fracf(m_fTexOffset[1] / m_fTexSize[1]),
                                         fracf(m_fTexOffset[2] / m_fTexSize[2]),
                                         fracf(m_fTexOffset[3] / m_fTexSize[3]));
    m_pProgram->setUniformLocationWith4f(m_iUnifTexScale,
                                         m_obContentSize.width / m_fTexSize[0],
                                         m_obContentSize.height / m_fTexSize[1],
                                         m_obContentSize.width / m_fTexSize[2],
                                         m_obContentSize.height / m_fTexSize[3]);
    //
    // Attributes
    //
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_aVertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, m_aTexcoords);
    
    ccGLBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CC_INCREMENT_GL_DRAWS(1);
}

void CCWaterNode::Update(float dt)
{
    for (int i = 0; i < 4; i++)
        m_fTexOffset[i] += m_fTexSpeed[i] * dt;
}


