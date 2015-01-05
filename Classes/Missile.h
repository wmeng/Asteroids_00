//
//  Missile.h
//  Asteroids
//
//  Created by Wilson Meng on 12/27/14.
//
//

#ifndef __Asteroids__Missile__
#define __Asteroids__Missile__

#include "cocos2d.h"
#include "MovingObject.h"

class CMissile : public CMovingObject
{
protected:
    static const int MISSILE_SPEED;
    static const float ROTATION_FACTOR;
    
    CCNode *m_pTarget;
        
public:
    CREATE_FUNC(CMissile)
    virtual bool init();
    void PrepareForScene(float angle, CCPoint pos);
    void UpdatePosition(CCPoint displacement, float delta);
    bool searchTarget(CCNode* pTargetNode);
    bool updateMissile(float delta);
};

#endif /* defined(__Asteroids__Missile__) */
