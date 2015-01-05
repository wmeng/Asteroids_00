//
//  SpaceShip.cpp
//  Asteroids
//
//  Created by Wilson Meng on 11/13/14.
//
//

#include "GameCommon.h"
#include "SpaceShip.h"

using namespace ASTEROIDS_GAME_COMMON;

const int   SpaceShip::NUM_SPACE_SHIP_PICS   = 6;
const int   SpaceShip::NUM_FRAMES_PER_SECOND = 24;
const float SpaceShip::ROTATION_FACTOR       = 45;
const float SpaceShip::ACCELERATION_FACTOR   = 180;
const float SpaceShip::FRICTION_FACTOR       = 0.98;
const float SpaceShip::PI                    = 3.1415926536;
const float SpaceShip::ROTATION_THRESHOLD    = 5;
const float SpaceShip::RADIUS_FACTOR         = 0.3;
const float SpaceShip::SPACE_SHIP_EXPLODE_TIME = 2;
const float SpaceShip::SPACE_SHIP_SPAWN_TIME = 4;

SpaceShip::~SpaceShip()
{
    if (m_pForeverNormalMode) {
        m_pForeverNormalMode->release();
    }
    
    if (m_pForeverAccelerateMode) {
        m_pForeverAccelerateMode->release();
    }
}

bool SpaceShip::init()
{
    bool retValue = true;
    
    const float DELAY_PER_UNIT = 1.0 / 24;
    mSpeed = 0;
    mAccel = false;
    mRotDir = IDLE;
    setRotation(0); // This is the angle of rotation
    SetStatus(READY);
    mRadius = getContentSize().width * RADIUS_FACTOR;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PlayerShip.plist");

    if (!CCSprite::initWithSpriteFrameName("SHIP_A_01.png")) {
        return false;
    }
    
    char tmpBuf[64];
    
    // Normal Mode (small fire)
    CCAnimation *tmpNormalMode = CCAnimation::create();
    if (NULL == tmpNormalMode) {
        return false;
    }
    for (int i = 0; i < NUM_SPACE_SHIP_PICS; i++) {
        sprintf(tmpBuf, "SHIP_A_%02d.png", i+1);
        tmpNormalMode->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tmpBuf));
    }
    tmpNormalMode->setDelayPerUnit(DELAY_PER_UNIT);
    m_pForeverNormalMode = CCRepeatForever::create(CCAnimate::create(tmpNormalMode));
    if (NULL == m_pForeverNormalMode) {
        return false;
    }
    m_pForeverNormalMode->retain();
    
    // Accelerate Mode (big fire)
    CCAnimation *tmpAccelerateMode = CCAnimation::create();
    if (NULL == tmpAccelerateMode) {
        return false;
    }
    for (int i = 0; i < NUM_SPACE_SHIP_PICS; i++) {
        sprintf(tmpBuf, "SHIP_B_%02d.png", i+1);
        tmpAccelerateMode->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tmpBuf));
    }
    tmpAccelerateMode->setDelayPerUnit(DELAY_PER_UNIT);
    m_pForeverAccelerateMode = CCRepeatForever::create(CCAnimate::create(tmpAccelerateMode));
    if (NULL == m_pForeverAccelerateMode) {
        return false;
    }
    m_pForeverAccelerateMode->retain();
    
    runAction(m_pForeverNormalMode);
    
    return retValue;
}

// Update the ship's acceleration parameter
// Change the ship's picture if acceleration parameter is different from before
void SpaceShip::SetAcceleration(bool enable)
{
    // Check if the acceleration state has changed
    if (mAccel != enable) {
 //       stopAllActions();
        if (true == enable) {
            stopAction(m_pForeverNormalMode);
            runAction(m_pForeverAccelerateMode);
        } else {
            stopAction(m_pForeverAccelerateMode);
            runAction(m_pForeverNormalMode);
        }
    }
    
    mAccel = enable;
    return;
}

CCPoint SpaceShip::GetDisp(float delta, const CCPoint& rTouchedPos)
{
    // Calculate the rotation angle
    float angle = getRotation();
    if (IDLE != GetRotDir()) {
        if (LEFT == GetRotDir()) {
            angle -= delta * ROTATION_FACTOR;
        } else if (RIGHT == GetRotDir()) {
            angle += delta * ROTATION_FACTOR;
        }
        // normalize angle to between -180 and 180 degrees
        while (angle > 180) {
            angle -= 360;
        }
        while (angle < -180) {
            angle += 360;
        }
        setRotation(angle);
    }
    
    // Determine the acceleration value
    float acc = 0;
    if (true == mAccel) {
        acc = ACCELERATION_FACTOR;
    }
    
    // Get the displacement based on current rotation and speed
    // s = ut + 0.5(a)(t ^ 2)
    float disp = mSpeed * delta + 0.5 * acc * delta * delta;
    // convert the angle from degrees to radians and calculate x and y
    // displacement components
    // remember the angle starts from Y-axis and rotates clockwise
    float disp_X = disp * sin(ToRadians(angle));
    float disp_Y = disp * cos(ToRadians(angle));
                              
    // Calculate the new speed
    // v = u + at
    // we supply a friction factor such that the ship will stop when not
    // accelerating
    mSpeed = (mSpeed + acc * delta) * FRICTION_FACTOR;
    if (mSpeed < 0.01 && mSpeed > -0.01) {
        mSpeed = 0;
    }

//    CCLog("mSpeed = %05f disp_X = %0.05f disp_Y = %0.05f", mSpeed, disp_X, disp_Y);
    
    return ccp(disp_X, disp_Y);;
}

void SpaceShip::UpdateSpaceShipTimer(float delta)
{
    switch(mStatus) {
        case EXPLODED:
            mTimer += delta;
            if (mTimer > SPACE_SHIP_EXPLODE_TIME) {
                SetStatus(SPAWNING);
                setVisible(true);
                runAction(CCBlink::create(SPACE_SHIP_SPAWN_TIME, 15));
            }
            break;
        case SPAWNING:
            mTimer += delta;
            if (mTimer > SPACE_SHIP_SPAWN_TIME) {
                setVisible(true);
                SetStatus(READY);
            }
            break;
        case READY:
        default:
            break;
    }
}
