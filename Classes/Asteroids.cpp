//
//  Asteroids.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/23/14.
//
//

#include "Asteroids.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace ASTEROIDS_GAME_COMMON;

const int CAsteroids::ASTEROID_BASE_SPEED = 40;
const int CAsteroids::ASTEROID_VARIANT_SPEED = 20;
const float CAsteroids::SCALING_FACTOR = 0.8;

const float CAsteroids::SCALE_ASTEROID_SMALL = 0.8;
const float CAsteroids::SCALE_ASTEROID_MEDIUM = 1.2;
const float CAsteroids::SCALE_ASTEROID_LARGE = 1.5;

const int CAsteroids::SCORE_ASTEROID_SMALL  = 300;
const int CAsteroids::SCORE_ASTEROID_MEDIUM = 200;
const int CAsteroids::SCORE_ASTEROID_LARGE  = 100;

CAsteroids::~CAsteroids()
{
    CCLog("~CAsteroids invoked");
}

bool CAsteroids::init()
{
    return initWithFile("rock1.png");
}

void CAsteroids::PrepareForScene(ASTEROID_CREATE create, ASTEROID_SIZE size, const CCPoint &rPoint)
{
    float init_x = 0, init_y = 0;
    int asteroidAngle = 0;
    
    if (NEW == create) {
        const int ASTEROID_DELTA_ANGLE = rand() % 90;
        
        const int SPRITE_HEIGHT = getContentSize().height;
        const int SPRITE_WIDTH = getContentSize().width;
        const CCSize SCREEN_SIZE = CCDirector::sharedDirector()->getVisibleSize();
        const int SCREEN_WIDTH = SCREEN_SIZE.width;
        const int SCREEN_HEIGHT = SCREEN_SIZE.height;
        
        // Determine the (random) side of the screen the asteroid will appear
        // Determine the (random) height / width of the side the asteroid will appear from
        // Determine the (random) direction the asteroid is travelling. This is represented
        // by the asteroidAngle. Please note that the way of measurement is same as spaceship
        // i.e. starts at Y-axis and proceeds in clockwise direction. i.e. Y axis is 0 degree
        // X axis is 90 degree etc
        
        const int SIDE = rand() % 4;
        switch(SIDE) {
            case 0:  // TOP - direction should be down, angle between 135 to 225
                init_x = rand() % SCREEN_WIDTH;
                init_y = SCREEN_HEIGHT + SPRITE_HEIGHT / 2;
                asteroidAngle = 135 + ASTEROID_DELTA_ANGLE;
                break;
            case 1:  // LEFT - direction should be right, angle between 45 to 135
                init_x = -SPRITE_WIDTH / 2;
                init_y = rand() % SCREEN_HEIGHT;
                asteroidAngle = 45 + ASTEROID_DELTA_ANGLE;
                break;
            case 2:  // RIGHT - direction should be left, angle between 225 to 315
                init_x = SCREEN_WIDTH + SPRITE_WIDTH / 2;
                init_y = rand() % SCREEN_HEIGHT;
                asteroidAngle = 225 + ASTEROID_DELTA_ANGLE;
                break;
            case 3:  // BOTTOM (and default) - direction should be up, angle normalized to 315 and 45
            default:
                init_x = rand() % SCREEN_WIDTH;
                init_y = -SPRITE_HEIGHT / 2;
                asteroidAngle = 315 + ASTEROID_DELTA_ANGLE;
                while (asteroidAngle > 360) {
                    asteroidAngle -= 360;
                }
                break;
        }
    } else if (SPLIT == create) {
        init_x = rPoint.x;
        init_y = rPoint.y;

        // randomly determine the asteroid angle and normalize it between 180 and -180
        asteroidAngle = rand() % 360;
        while (asteroidAngle > 180) {
            asteroidAngle -= 360;
        }
    }
    // Next, determine the direction, size and velocity of the asteroid
    setRotation(asteroidAngle);
    setAnchorPoint(ccp(0.5, 0.5));
    
    setPosition(ccp(init_x, init_y));
    
    m_Size = size;
    switch(m_Size) {
        case LARGE:  setScale(SCALE_ASTEROID_LARGE);  break;
        case MEDIUM: setScale(SCALE_ASTEROID_MEDIUM); break;
        case SMALL:  setScale(SCALE_ASTEROID_SMALL);  break;
    }

    const int ASTEROID_SPEED = ASTEROID_BASE_SPEED + rand() % ASTEROID_VARIANT_SPEED;
    m_Velocity.x = sin(ToRadians(asteroidAngle)) * ASTEROID_SPEED;
    m_Velocity.y = cos(ToRadians(asteroidAngle)) * ASTEROID_SPEED;

    // Set the asteroid to rotate, randomly decide whether to rotate clockwise or counter-clockwise
    CCRepeatForever *pAction = (rand() % 2) ?
                                CCRepeatForever::create(CCRotateBy::create(1,180)) :
                                CCRepeatForever::create(CCRotateBy::create(1,180)->reverse());
            
    if (pAction) {
        runAction(pAction);
    }
    
    return;
}

float CAsteroids::getRadius()
{
    CCSize tmpSize = getContentSize() * SCALING_FACTOR;
    return tmpSize.width;
}
