//
//  Background.h
//  Asteroids
//
//  Created by Dickens on 6/11/2014.
//
//

#ifndef __Asteroids__Background__
#define __Asteroids__Background__

#include "cocos2d.h"

class Background : public cocos2d::CCNode
{
protected:
    float mSpeedRatio;
    cocos2d::CCSize mScreenSize;
    
public:
    // implement the "static node()" method manually
    static Background* create(const char* pzFileName, float speedRatio);
    bool init(const char* pzFileName, float speedRatio);
    void SetSpeedRatio(float speedRatio) { mSpeedRatio = speedRatio; }
    float GetSpeedRatio() { return mSpeedRatio; }
    
    bool updatePos(const cocos2d::CCPoint& displacement);
};

#endif /* defined(__Asteroids__Background__) */
