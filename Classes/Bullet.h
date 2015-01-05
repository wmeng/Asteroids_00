//
//  Bullet.h
//  Asteroids
//
//  Created by Wilson Meng on 12/20/14.
//
//

#ifndef __Asteroids__Bullet__
#define __Asteroids__Bullet__

#include "cocos2d.h"
#include "MovingObject.h"

class CBullet : public CMovingObject
{
protected:
    static const int BULLET_SPEED;
    
public:
    CREATE_FUNC(CBullet)
    virtual bool init();
    void PrepareForScene(float angle, CCPoint pos);
};

#endif /* defined(__Asteroids__Bullet__) */
