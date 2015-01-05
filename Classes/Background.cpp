//
//  Background.cpp
//  Asteroids
//
//  Created by Dickens on 6/11/2014.
//
//
#include "Background.h"

USING_NS_CC;

bool Background::updatePos(const CCPoint& rDisplacement)
{
    bool retValue = true;
    
    CCPoint currentPos = getPosition();
    // Background is moving in opposite direction of displacement,
    // hence minus. Factor in the speed ration as well
    currentPos = currentPos - rDisplacement * mSpeedRatio;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSize worldSize = getContentSize();
    
    const float MIN_X = visibleSize.width - worldSize.width / 2;
    const float MAX_X = worldSize.width / 2;
    const float MIN_Y = visibleSize.height - worldSize.height / 2;
    const float MAX_Y = worldSize.height / 2;

    const float STEP_X = MAX_X;
    const float STEP_Y = MAX_Y;

    if (currentPos.x > MAX_X) currentPos.x -= STEP_X;
    if (currentPos.y > MAX_Y) currentPos.y -= STEP_Y;
    if (currentPos.x < MIN_X) currentPos.x += STEP_X;
    if (currentPos.y < MIN_Y) currentPos.y += STEP_Y;
    
    setPosition(currentPos.x, currentPos.y);
    
    return retValue;
}

bool Background::init(const char *pzFileName, float speedRatio)
{
    bool retValue = true;

    // Take 4 instances of the same picture, group them together to form
    // a much larger picture (4 quadrants, each of which is the original)
    // Set the anchor points of this larger picture, then the content size
    // Finally, set the speed ratio
    CCSprite *pLeaf;
    try {
        pLeaf = CCSprite::create(pzFileName);
        pLeaf->setAnchorPoint(ccp(0, 0));
        addChild(pLeaf, 0);

        pLeaf = CCSprite::create(pzFileName);
        pLeaf->setAnchorPoint(ccp(0, 1));
        addChild(pLeaf, 0);
        
        pLeaf = CCSprite::create(pzFileName);
        pLeaf->setAnchorPoint(ccp(1, 0));
        addChild(pLeaf, 0);
        
        pLeaf = CCSprite::create(pzFileName);
        pLeaf->setAnchorPoint(ccp(1, 1));
        addChild(pLeaf, 0);
        
        const CCSize tmpSize = pLeaf->getContentSize() * 2;
        setContentSize(tmpSize);
        
        mSpeedRatio = speedRatio;
        
    } catch (std::bad_alloc &rba) {
        CCLog("ERROR: Background::init has bad_alloc error : %s", rba.what());
        retValue = false;
    } catch(std::exception &re) {
        CCLog("ERROR: Background::init threw unknown exception : %s", re.what());
        retValue = false;
    }
    
    return retValue;
}

Background *Background::create(const char *pzFileName, float speedRatio)
{
    Background *pBkgd = new Background;
    if (pBkgd && pBkgd->init(pzFileName, speedRatio))
    {
        pBkgd->autorelease();
    }
    else
    {
        delete pBkgd;
        pBkgd = NULL;
    }
    return pBkgd;
}
