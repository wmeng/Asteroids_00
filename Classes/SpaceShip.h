//
//  SpaceShip.h
//  Asteroids
//
//  Created by Wilson Meng on 11/13/14.
//
//

#ifndef __Asteroids__SpaceShip__
#define __Asteroids__SpaceShip__

#include "cocos2d.h"

USING_NS_CC;

enum Dir{
    IDLE,
    LEFT,
    RIGHT
};

enum SPACE_SHIP_STATUS {
    EXPLODED, // Just dead
    SPAWNING, // Blinking (invincible mode)
    READY  // Steady (spawned successfully)
};

class SpaceShip : public CCSprite
{
protected:
    bool   mAccel;
    Dir    mRotDir;
    float  mSpeed;

    float  mTimer;
    SPACE_SHIP_STATUS mStatus;
    float  mRadius;
    
    CCRepeatForever *m_pForeverNormalMode;
    CCRepeatForever *m_pForeverAccelerateMode;
    
public:
    ~SpaceShip();
    
    static const int NUM_SPACE_SHIP_PICS;
    static const int NUM_FRAMES_PER_SECOND;
    static const float ROTATION_FACTOR;
    static const float ACCELERATION_FACTOR;
    static const float FRICTION_FACTOR;
    static const float PI;
    static const float ROTATION_THRESHOLD;
    static const float RADIUS_FACTOR;
    static const float SPACE_SHIP_EXPLODE_TIME;
    static const float SPACE_SHIP_SPAWN_TIME;

    CREATE_FUNC(SpaceShip)
    virtual bool init();
    CCPoint GetDisp(float delta, const CCPoint& rTouchedPos);
    
    float GetRadius() { return mRadius; }
    void SetAcceleration(bool enable);
    bool GetAcceleration() { return mAccel; }
    void SetRotDir(Dir direction) {mRotDir = direction; }
    Dir GetRotDir() { return mRotDir; }
    
    void SetStatus(SPACE_SHIP_STATUS status) {
        mStatus = status;
        if (EXPLODED == status) {
            setVisible(false);
            SetRotDir(IDLE);
            SetAcceleration(false);
        }
        mTimer = 0;
    }
    SPACE_SHIP_STATUS GetStatus() { return mStatus; }

    void UpdateSpaceShipTimer(float delta);
};


#endif /* defined(__Asteroids__SpaceShip__) */
