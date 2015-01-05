#ifndef __GAMESMAIN_SCENE_H__
#define __GAMESMAIN_SCENE_H__

#include "cocos2d.h"
#include "SpaceShip.h"
#include "Background.h"
#include "Asteroids.h"
#include "Bullet.h"
#include "Missile.h"
#include "Explosion.h"
#include "SecureData.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace ASTEROIDS_GAME_COMMON;

class GameMain : public cocos2d::CCLayer
{
protected:
    
    enum Z_OBJECT {
        Z_BACKGROUND,
        Z_BULLET,
        Z_MISSILE,
        Z_ASTEROIDS,
        Z_SPACESHIP,
        Z_EXPLOSION,
        Z_BUTTON
    };

    static const int NUM_BACKGROUND = 2;
    static const int CHANGE_THRESHOLD = 10; // Threshold for changing ship behaviour
    static const float ROT_THRESHOLD = 5;
    
    static const int MAX_ASTEROIDS = 50;
    static const int MAX_MISSILES = 5;
    static const int MAX_BULLETS = 20;
    static const float SPAWN_BULLET_TIME = 0.5;
    static const float SPAWN_MISSILE_TIME = 0.8;
    static const float SPAWN_ASTEROID_TIME = 0.5;
        
    CCSize mSize;
    int mAccelerateBoundary;
    int mTurnLeftBoundary;
    int mTurnRightBoundary;
    
    SpaceShip *m_pSpaceShip;
    Background *m_Background[NUM_BACKGROUND];
    CCSprite *m_Button[2];
    CCSprite *m_ButtonIcon[2];
    CCLabelTTF *m_pBulletStatus[2];
    CCLabelTTF *m_pMissileStatus[MAX_MISSILES + 1];
    
    CCNode *m_BulletNode, *m_MissileNode, *m_AsteroidNode, *m_ExplosionNode;
    float m_BulletTimer, m_MissileTimer, m_AsteroidTimer;

    CAsteroids *m_pAsteroids[MAX_ASTEROIDS];
    CBullet *m_pBullets[MAX_BULLETS];
    CMissile *m_pMissiles[MAX_MISSILES];
    
    CCTouch m_Touch;
    CCPoint m_ShipPos;
    CCPoint m_TouchedPos;
    bool m_IsTouchEvent;
    
    bool m_EnableAutoFire;
    
    CSecureData m_Score;
    CCLabelTTF *m_pScoreLabel;
    
    CCRect m_BulletRect;
    CCRect m_MissileRect;
    
    int m_NumAvailableMissiles;
    
    // Helper methods and attributes
    CCSize m_VisibleSize;
    CCPoint m_ScreenCentre;
    
    bool InitializeSpaceShip();
    bool InitializeBackGrounds();
    bool InitializeButtons();
    bool InitializeBullets();
    bool InitializeMissiles();
    bool InitializeAsteroids();
    bool InitializeExplosion();
    bool InitializeScore();
    
    void UpdateScoreDisplay();
    bool UpdateAutoFireDisplay();
    bool AutoFireEnabled(CCPoint& rPos);
    bool MissileEnabled(CCPoint& rPos);
    void FireBullet();
    void FireMissile();
    void CreateAsteroid(ASTEROID_SIZE size = LARGE, ASTEROID_CREATE create = NEW, const CCPoint& rPoint = ccp(0,0));
    void CheckCollision();
    void CheckBulletCollision();
    void CheckMissileCollision();
    void CheckShipCollision();
    
    
public:
    ~GameMain();

    void SetShipBehaviour();
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet* pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet* pTouches, CCEvent *pEvent);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void update(float delta);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameMain);
};

#endif // __GAMESMAIN_SCENE_H__
