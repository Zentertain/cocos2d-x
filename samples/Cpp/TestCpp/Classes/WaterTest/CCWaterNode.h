//
//  CCWaterNode.h
//  TestCpp
//
//  Created by 姚春晖 on 14-4-24.
//
//

#ifndef __TestCpp__CCWaterNode__
#define __TestCpp__CCWaterNode__

#include "cocos2d.h"

class CCWaterNode: public cocos2d::CCNodeRGBA
{
public:
    CCWaterNode();
    ~CCWaterNode();
    
    static CCWaterNode* create(float w, float h, cocos2d::CCTexture2D* pNormalMap);
    void Update(float dt);
    
    virtual bool init(float w, float h, cocos2d::CCTexture2D* pNormalMap);
    virtual void setContentSize(const cocos2d::CCSize & size);
    virtual void draw();
    
    void setNormalMap(cocos2d::CCTexture2D* pTexture);
    cocos2d::CCTexture2D* getNormalMap() const { return m_pNormalMap; }
    
    
protected:
    cocos2d::ccVertex2F m_aVertices[4];
    cocos2d::ccVertex2F m_aTexcoords[4];
    
    cocos2d::CCGLProgram* m_pProgram;
    float m_fTexOffset[4];
    float m_fTexSize[4];
    float m_fTexSpeed[4];
    cocos2d::ccVertex3F m_vLightDir;
    cocos2d::ccVertex3F m_vNormal;
    cocos2d::ccVertex3F m_vEyePos;
    GLint m_iUnifTexOffset;
    GLint m_iUnifTexScale;
    GLint m_iUnifLightDir;
    GLint m_iUnifEyePos;
    GLint m_iUnifNormalMap;
    GLint m_iUnifColor;
    cocos2d::CCTexture2D* m_pNormalMap;
    
};

#endif /* defined(__TestCpp__CCWaterNode__) */
