//
//  Explosion.h
//  Asteroids
//
//  Created by Wilson Meng on 12/28/14.
//
//

#ifndef __Asteroids__Explosion__
#define __Asteroids__Explosion__

#include <cocos2d.h>

USING_NS_CC;

class CExplosion: public CCParticleExplosion
{
public:
    CREATE_FUNC(CExplosion);
    virtual bool init();
    void UpdatePosition(CCPoint displacement);    
};

#endif /* defined(__Asteroids__Explosion__) */
