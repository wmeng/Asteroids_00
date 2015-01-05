 //
//  Asteroids.h
//  Asteroids
//
//  Created by Wilson Meng on 12/23/14.
//
//

#ifndef __Asteroids__Asteroids__
#define __Asteroids__Asteroids__

#include "cocos2d.h"
#include "MovingObject.h"

enum ASTEROID_CREATE {
    NEW,
    SPLIT
};

enum ASTEROID_SIZE {
    SMALL,
    MEDIUM,
    LARGE
};

class CAsteroids : public CMovingObject
{
protected:
    static const int ASTEROID_BASE_SPEED;
    static const int ASTEROID_VARIANT_SPEED;
    static const float SCALING_FACTOR;
    
    static const float SCALE_ASTEROID_SMALL;
    static const float SCALE_ASTEROID_MEDIUM;
    static const float SCALE_ASTEROID_LARGE;
    
    static const int SCORE_ASTEROID_SMALL;
    static const int SCORE_ASTEROID_MEDIUM;
    static const int SCORE_ASTEROID_LARGE;
    
    int m_Score;
    ASTEROID_SIZE m_Size;
    
public:
    
    ~CAsteroids();

    CREATE_FUNC(CAsteroids)
    virtual bool init();
    void PrepareForScene(ASTEROID_CREATE create = NEW, ASTEROID_SIZE size = LARGE, const CCPoint &rPos = ccp(0,0));
    float getRadius();
    
    ASTEROID_SIZE getAsteroidSize() { return m_Size; }
    int getAsteroidScore() {
        int SCORE = 0;
        switch (m_Size) {
            case SMALL: SCORE  = SCORE_ASTEROID_SMALL; break;
            case MEDIUM: SCORE = SCORE_ASTEROID_MEDIUM; break;
            case LARGE: SCORE  = SCORE_ASTEROID_LARGE; break;
        }
        return SCORE;
    }
};

#endif /* defined(__Asteroids__Asteroids__) */
