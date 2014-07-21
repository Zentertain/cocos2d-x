//
//  WaterNodeTest.h
//  TestCpp
//
//  Created by 姚春晖 on 14-4-24.
//
//

#ifndef __TestCpp__WaterNodeTest__
#define __TestCpp__WaterNodeTest__

#include "../testBasic.h"

USING_NS_CC;

class WaterNodeTest: public CCLayer
{
protected:
    double    m_fLastTime;
    
public:
    WaterNodeTest(void);
    ~WaterNodeTest(void);
    
    virtual std::string title();
    virtual void onEnter();
};

class WaterNodeTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* defined(__TestCpp__WaterNodeTest__) */
