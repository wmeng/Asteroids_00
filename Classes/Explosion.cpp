//
//  Explosion.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/28/14.
//
//

#include "Explosion.h"

bool CExplosion::init()
{
    bool retValue = true;
    
    if (!CCParticleExplosion::initWithTotalParticles(200)) {
        return false;
    }
    
    CCTextureCache::sharedTextureCache()->addImage("rock_break.png");
    setTexture(CCTextureCache::sharedTextureCache()->textureForKey("rock_break.png"));
    setAutoRemoveOnFinish(true);
    setPositionType(kCCPositionTypeRelative);
    
    m_tStartColor.r = 1.0f;
    m_tStartColor.g = 0.25f;
    m_tStartColor.b = 0.25f;
    m_tStartColor.a = 0.8f;

    m_tStartColorVar.r = 0.0f;
    m_tStartColorVar.g = 0.0f;
    m_tStartColorVar.b = 0.0f;
    m_tStartColorVar.a = 0.0f;

    m_tEndColor.r = 1.0f;
    m_tEndColor.g = 1.0f;
    m_tEndColor.b = 1.0f;
    m_tEndColor.a = 0.0f;

    m_tEndColorVar.r = 0.0f;
    m_tEndColorVar.g = 0.0f;
    m_tEndColorVar.b = 0.0f;
    m_tEndColorVar.a = 0.0f;
    
    return retValue;
}

void CExplosion::UpdatePosition(CCPoint displacement)
{
    setPosition(getPosition() - displacement);
}