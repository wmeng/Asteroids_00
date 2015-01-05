//
//  Bullet.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/20/14.
//
//

#include "Bullet.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace ASTEROIDS_GAME_COMMON;

const int CBullet::BULLET_SPEED = 1000;

bool CBullet::init()
{
    return initWithFile("BULLET.png");
}

void CBullet::PrepareForScene(float angle, CCPoint loc)
{
//    CCLog("CBullet: angle %.4f loc.x %.4f loc.y %.4f", angle, loc.x, loc.y);
    
    float sinAngle = sin(ToRadians(angle));
    float cosAngle = cos(ToRadians(angle));
    loc.x += getContentSize().height * sinAngle;
    loc.y += getContentSize().height * cosAngle;
    setAnchorPoint(ccp(0.5,0.95));
    setRotation(angle);
    setPosition(loc);
    m_Velocity.x = sinAngle * BULLET_SPEED;
    m_Velocity.y = cosAngle * BULLET_SPEED;
}
