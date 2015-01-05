//
//  MovingObject.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/20/14.
//
//

#include "MovingObject.h"

void CMovingObject::UpdatePosition(CCPoint displacement, float delta)
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