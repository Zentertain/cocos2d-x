//
//  WaterNodeTest.cpp
//  TestCpp
//
//  Created by 姚春晖 on 14-4-24.
//
//

#include "WaterNodeTest.h"

#include "../testResource.h"
#include "cocos2d.h"
#include "CCWaterNode.h"

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
_pos = _min;        \
else if (_pos > _max)   \
_pos = _max;        \

//------------------------------------------------------------------
//
// AccelerometerTest
//
//------------------------------------------------------------------
WaterNodeTest::WaterNodeTest(void)
: m_fLastTime(0.0)
{
}

WaterNodeTest::~WaterNodeTest(void)
{
}

std::string WaterNodeTest::title()
{
    return "WaterNodeTest";
}

void WaterNodeTest::onEnter()
{
    CCLayer::onEnter();
    
    setAccelerometerEnabled(true);
    
    
    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );
    
    CCWaterNode* pWaterNode = CCWaterNode::create(
                                                 VisibleRect::getVisibleRect().size.width,
                                                 VisibleRect::getVisibleRect().size.height,
                                                 CCTextureCache::sharedTextureCache()->addImage("Images/water_normal.jpg"));
    pWaterNode->setPosition(VisibleRect::leftBottom());
    pWaterNode->setColor(ccc3(1, 121, 254));
    
    CCSprite* pSprite = CCSprite::create("Images/island.png");
    pSprite->setScale(0.6f);
    pSprite->setPosition(VisibleRect::center());
    addChild(pWaterNode);
    addChild(pSprite, 1);
}

//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
void WaterNodeTestScene::runThisTest()
{
    CCLayer* pLayer = new WaterNodeTest();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}
