//
//  Missile.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/27/14.
//
//

#include "Missile.h"
#include "GameCommon.h"
#include "Asteroids.h"

USING_NS_CC;
using namespace ASTEROIDS_GAME_COMMON;

const int CMissile::MISSILE_SPEED = 350;
const float CMissile::ROTATION_FACTOR = 100;

bool CMissile::init()
{
    m_pTarget = NULL;
    return initWithFile("MISSILE.png");
}

void CMissile::PrepareForScene(float angle, CCPoint loc)
{
    float sinAngle = sin(ToRadians(angle));
    float cosAngle = cos(ToRadians(angle));
    loc.x += getContentSize().height * sinAngle;
    loc.y += getContentSize().height * cosAngle;
    setAnchorPoint(ccp(0.5,0.95));
    setRotation(angle);
    setPosition(loc);
    m_Velocity.x = sinAngle * MISSILE_SPEED;
    m_Velocity.y = cosAngle * MISSILE_SPEED;
    
    CCLog("CMissile:PrepareForScene: Rotation = %.4f", angle);
}

void CMissile::UpdatePosition(CCPoint displacement, float delta)
{
    CCPoint loc = getPosition();
    loc = loc + m_Velocity * delta - displacement;
    CCSize vSize = CCDirector::sharedDirector()->getVisibleSize();
    if (loc.x < -vSize.width ||
        loc.x > 2 * vSize.width ||
        loc.y < -vSize.height ||
        loc.y > 2 * vSize.height) {
        stopAllActions();
        removeFromParent();
    } else {
        setPosition(loc);
    }
}

bool CMissile::searchTarget(CCNode* pTargetNode)
{
    float minDistanceSq = 99999999;
    bool retValue = false;
    
    // Walk through each existing asteroid and measure the distance between missile and asteroid
    // keep track of the one where the distance is shortest
    if (NULL != pTargetNode) {
        CCArray *pChildren = pTargetNode->getChildren();
        if (pChildren) {
            for (int i = 0; i < pChildren->count(); i++) {
                CAsteroids *pAsteroid = dynamic_cast<CAsteroids *>(pChildren->objectAtIndex(i));
                CCPoint asteroidPos = pAsteroid->getPosition();
                float distanceSq = getPosition().getDistanceSq(asteroidPos);
                if (distanceSq < minDistanceSq) {
                    minDistanceSq = distanceSq;
                    m_pTarget = pAsteroid;
                    retValue = true;
                }
            }
        }
    }

    return retValue;
}

bool CMissile::updateMissile(float delta)
{
    bool retValue = true;
    
    if (NULL == m_pTarget || NULL == m_pTarget->getParent()) {
        return retValue;
    }

    CCPoint missilePos = getPosition();
    CCPoint rockPos = m_pTarget->getPosition();
    
    // Assume the rockPos so it is now based on using the missilePos as the origin.
    // Use getAngle to calculate the angle of rockPos relative to x-axis.
    // Transpose this angle to 90 to get the angle relative to y-axis
    const float tmpDegree = (rockPos - missilePos).getAngle() / PI * 180;
    float rockAngleDegree = 90 - tmpDegree;
    
    // This rockAngle ranges from 0 to 360. Need to normalize it to 180 / -180
    while (rockAngleDegree > 180) {
        rockAngleDegree -= 360;
    }
    while (rockAngleDegree < -180) {
        rockAngleDegree += 360;
    }
    
    const float CURRENT_BEARING = getRotation();
    float rotateDegree = rockAngleDegree - CURRENT_BEARING;
    while (rotateDegree > 180) {
        rotateDegree -= 360;
    }
    while (rotateDegree < -180) {
        rotateDegree += 360;
    }
    
    float deltaDegree = delta * ROTATION_FACTOR;
    if (rotateDegree > 0) {
        if (rotateDegree < deltaDegree) {
            deltaDegree = rotateDegree;
        }
    } else {
        deltaDegree = -deltaDegree;
        if (rotateDegree > deltaDegree) {
            deltaDegree = rotateDegree;
        }
    }
    
    const float NEW_BEARING = CURRENT_BEARING + deltaDegree;
//    CCLog("rotDegree %.5f initDelta %.5f finalDelta %.5f newAngle %.5f", rotateDegree, delta * ROTATION_FACTOR, deltaDegree, NEW_BEARING);
    setRotation(NEW_BEARING);
    m_Velocity.x = sin(ToRadians(NEW_BEARING)) * MISSILE_SPEED;
    m_Velocity.y = cos(ToRadians(NEW_BEARING)) * MISSILE_SPEED;

    return retValue;
    
}