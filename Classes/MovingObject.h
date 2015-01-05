//
//  MovingObject.h
//  Asteroids
//
//  Created by Wilson Meng on 12/20/14.
//
//

#ifndef __Asteroids__MovingObject__
#define __Asteroids__MovingObject__

#include "cocos2d.h"

USING_NS_CC;

class CMovingObject : public CCSprite
{
protected:
    CCPoint m_Velocity;

public:
    CMovingObject() : m_Velocity(ccp(0,0)) {}
    
    virtual void UpdatePosition(CCPoint displacement, float delta);
    
};

#endif /* defined(__Asteroids__MovingObject__) */
