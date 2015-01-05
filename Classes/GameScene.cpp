#include "GameScene.h"
#include "Background.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// const float GameMain::PI = SpaceShip::PI;

GameMain::~GameMain()
{
    int i = 0;
    // releasing missile memory
    for (i = 0; i < MAX_MISSILES; i++) {
        if (m_pMissiles[i] != NULL) {
            m_pMissiles[i]->release();
        }
    }
    
    // releasing bullet memory
    for (i = 0; i < MAX_BULLETS; i++) {
        if (m_pBullets[i] != NULL) {
            m_pBullets[i]->release();
        }
    }
    
    // release asteroids memory
    for (i = 0; i < MAX_ASTEROIDS; i++) {
        if (m_pAsteroids[i] != NULL) {
            m_pAsteroids[i]->release();
        }
    }
}

CCScene* GameMain::scene()
{    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameMain *layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameMain::InitializeSpaceShip()
{
    bool retValue = true;
    
    // Create the Spaceship;
    m_pSpaceShip = SpaceShip::create();
    if (NULL != m_pSpaceShip) {
        m_pSpaceShip->setPosition(m_ScreenCentre);
        m_ShipPos = m_ScreenCentre;
    } else {
        retValue = false;
    }

    return retValue;
}

bool GameMain::InitializeBackGrounds()
{
    bool retValue = true;

    // Create the background 0 (picture and speed-ratio)
    m_Background[0] = Background::create("background_1.png", 0.5);
    if (NULL != m_Background[0]) {
        m_Background[0]->setPosition(m_ScreenCentre);
    } else {
        retValue = false;
    }
    
    // Create the background 1 (picture and speed-ratio)
    m_Background[1] = Background::create("background_2.png", 1);
    if (NULL != m_Background[1]) {
        m_Background[1]->setPosition(m_ScreenCentre);
    } else {
        retValue = false;
    }
    
    return retValue;
}

// Initialize the bullet and the missile button
bool GameMain::InitializeButtons()
{
    bool retValue = true;
    
    // Create the bullet button (lower-left corner of visible screen)
    m_Button[0] = CCSprite::create("ui_wondow.png");
    if (NULL != m_Button[0]) {
        m_Button[0]->setAnchorPoint(ccp(0.5, 0.5));
        m_Button[0]->setPosition(ccp(m_Button[0]->getContentSize().width / 2,
                                     m_Button[0]->getContentSize().height / 2));
    } else {
        retValue = false;
    }
    
    m_ButtonIcon[0] = CCSprite::create("BULLET.png");
    if (NULL != m_ButtonIcon[0]) {
        m_ButtonIcon[0]->setAnchorPoint(ccp(0.5, 0.5));
        m_ButtonIcon[0]->setPosition(ccp( 20, /*m_Button[0]->getContentSize().width / 2, */
                                         m_Button[0]->getContentSize().height / 2));
    } else {
        retValue = false;
    }
    
    // Create the bullet status display inside the bullet button
    m_pBulletStatus[0] = CCLabelTTF::create("AUTO-FIRE ON", "Arial", 10);
    if (NULL != m_pBulletStatus[0]) {
        m_pBulletStatus[0]->setAnchorPoint(ccp(0.5, 0.5));
        m_pBulletStatus[0]->setPosition(ccp( 20 + m_ButtonIcon[0]->getContentSize().width / 2 +
                                            m_pBulletStatus[0]->getContentSize().width / 2,
                                             80 + m_pBulletStatus[0]->getContentSize().height / 2));
        m_pBulletStatus[0]->setVisible(false);
    } else {
        retValue = false;
    }
    
    m_pBulletStatus[1] = CCLabelTTF::create("AUTO-FIRE OFF", "Arial", 10);
    if (NULL != m_pBulletStatus[1]) {
        m_pBulletStatus[1]->setAnchorPoint(ccp(0.5, 0.5));
        m_pBulletStatus[1]->setPosition(ccp( 20 + m_ButtonIcon[0]->getContentSize().width / 2 +
                                            m_pBulletStatus[1]->getContentSize().width / 2,
                                            40 + m_pBulletStatus[1]->getContentSize().height / 2));
    }
    
    const CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // Set the bullet button rect
    m_BulletRect = CCRect(origin.x, origin.y,
                          m_Button[0]->getContentSize().width,
                          m_Button[0]->getContentSize().height);
    
    const CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    // Create the missile button (lower-right corner of visible screen)
    m_Button[1] = CCSprite::create("ui_wondow.png");
    if (NULL != m_Button[1]) {
        m_Button[1]->setAnchorPoint(ccp(0.5, 0.5));
        m_Button[1]->setPosition(ccp(visibleSize.width - m_Button[1]->getContentSize().width / 2,
                                     m_Button[1]->getContentSize().height / 2));
    } else {
        return false;
    }
    
    // Create the missile icon to be inside the missile button
    m_ButtonIcon[1] = CCSprite::create("MISSILE.png");
    if (NULL != m_ButtonIcon[1]) {
        m_ButtonIcon[1]->setAnchorPoint(ccp(0.5, 0.5));
        m_ButtonIcon[1]->setPosition(ccp(visibleSize.width - m_Button[1]->getContentSize().width / 2,
                                         m_Button[1]->getContentSize().height / 2));
    } else {
        retValue = false;
    }
    
    // Create the missile status
    const float MISSILE_DISPLAY_OFFSET_X = 15 + visibleSize.width - m_Button[1]->getContentSize().width;
    float MISSILE_DISPLAY_OFFSET_Y = 20;
    char tmpBuf[30];
    for (int i = 0; i < MAX_MISSILES + 1; i++) {
        if (0 == i) {
            sprintf(tmpBuf, "GENERATING ...");
        } else {
            sprintf(tmpBuf, "%d", i);
        }
        m_pMissileStatus[i] = CCLabelTTF::create(tmpBuf, "Arial", 12);
        m_pMissileStatus[i]->setAnchorPoint(ccp(0, 0));
        m_pMissileStatus[i]->setPosition(ccp(MISSILE_DISPLAY_OFFSET_X, MISSILE_DISPLAY_OFFSET_Y));
        m_pMissileStatus[i]->setVisible(false);
        MISSILE_DISPLAY_OFFSET_Y += m_pMissileStatus[i]->getContentSize().height;
    }
    // Initially, maximum number of  missiles are available
    m_pMissileStatus[MAX_MISSILES]->setVisible(true);
    
    // Set the missile button rect
    m_MissileRect = CCRect(visibleSize.width - m_Button[1]->getContentSize().width,
                           origin.y,
                           m_Button[1]->getContentSize().width,
                           m_Button[1]->getContentSize().height);

    return retValue;
}

bool GameMain::InitializeBullets()
{
    bool retValue = true;
    
    // Prepare the bullet node
    m_BulletNode = CCNode::create();
    
    // Prepare the bullet array
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_pBullets[i] = CBullet::create();
        if (m_pBullets[i]) {
            m_pBullets[i]->retain();
        } else {
            retValue = false;
            break;
        }
    }
    
    // Ready the bullet timer to fire the first bullet as soon
    // as auto-fire is enabled.
    m_BulletTimer = SPAWN_BULLET_TIME;
    
    return retValue;
}

bool GameMain::InitializeMissiles()
{
    bool retValue = true;
    
    // Prepare the missiles
    m_MissileNode = CCNode::create();
    
    for (int i = 0; i < MAX_MISSILES; i++) {
        m_pMissiles[i] = CMissile::create();
        if (m_pMissiles[i]) {
            m_pMissiles[i]->retain();
        } else {
            retValue = false;
            break;
        }
    }
    
    m_MissileTimer = SPAWN_MISSILE_TIME;

    return retValue;
}

bool GameMain::InitializeAsteroids()
{
    bool retValue = true;

    // Prepare the asteroid node
    m_AsteroidNode = CCNode::create();

    // Prepare the asteroid array
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        m_pAsteroids[i] = CAsteroids::create();
        if (m_pAsteroids[i]) {
            m_pAsteroids[i]->retain();
        } else {
            retValue = false;
            break;
        }
    }
    
    // Initialize the asteroid timer
    m_AsteroidTimer = 0;

    return retValue;
}

bool GameMain::InitializeExplosion()
{
    bool retValue = true;
    
    m_ExplosionNode = CCNode::create();
    
    return retValue;
}

bool GameMain::InitializeScore()
{
    bool retValue = true;

    m_Score = 0;
    char tmpBuf[40];
    sprintf(tmpBuf, "SCORE: %018u", m_Score.GetDecryptedData());
    m_pScoreLabel = CCLabelTTF::create(tmpBuf, "Arial", 18);
    if (m_pScoreLabel) {
        m_pScoreLabel->setPosition(ccp(m_VisibleSize.width - m_pScoreLabel->getContentSize().width/2,
                                       m_VisibleSize.height - m_pScoreLabel->getContentSize().height/2));
    } else {
        retValue = false;
    }

    return retValue;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    m_ScreenCentre = ccp(m_VisibleSize.width/2 + origin.x, m_VisibleSize.height/2 + origin.y);

    InitializeSpaceShip();
    InitializeBackGrounds();
    InitializeBullets();
    InitializeMissiles();
    InitializeAsteroids();
    InitializeExplosion();
    InitializeButtons();
    InitializeScore();
    
    m_EnableAutoFire = false;
    m_NumAvailableMissiles = MAX_MISSILES;
        
    this->addChild(m_Background[0], Z_BACKGROUND);
    this->addChild(m_Background[1], Z_BACKGROUND);
    this->addChild(m_BulletNode, Z_BULLET);
    this->addChild(m_MissileNode, Z_MISSILE);
    this->addChild(m_AsteroidNode, Z_ASTEROIDS);
    this->addChild(m_ExplosionNode, Z_EXPLOSION);
    this->addChild(m_pSpaceShip, Z_SPACESHIP);
    this->addChild(m_Button[0], Z_BUTTON);
    this->addChild(m_ButtonIcon[0], Z_BUTTON);
    this->addChild(m_pBulletStatus[0], Z_BUTTON);
    this->addChild(m_pBulletStatus[1], Z_BUTTON);
    this->addChild(m_Button[1], Z_BUTTON);
    this->addChild(m_ButtonIcon[1], Z_BUTTON);
    this->addChild(m_pMissileStatus[0], Z_BUTTON);
    this->addChild(m_pMissileStatus[1], Z_BUTTON);
    this->addChild(m_pMissileStatus[2], Z_BUTTON);
    this->addChild(m_pMissileStatus[3], Z_BUTTON);
    this->addChild(m_pMissileStatus[4], Z_BUTTON);
    this->addChild(m_pMissileStatus[5], Z_BUTTON);
    this->addChild(m_pScoreLabel, Z_BUTTON);
    
    m_IsTouchEvent = false;

    scheduleUpdate();
    setTouchEnabled(true);
    
    return true;
}

void GameMain::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

// Helper function to determine how ship should rotate or accelerate
void GameMain::SetShipBehaviour()
{
    // Determine if the ship should rotate
    const int distanceX = (int) (m_TouchedPos.x - m_ShipPos.x);
    const int distanceY = (int) (m_TouchedPos.y - m_ShipPos.y);
    const float shipAngleDegree = m_pSpaceShip->getRotation();
    
    // Normalize the touchPosAR between 180 and -180 degrees
    const CCPoint touchPosAR = convertToNodeSpaceAR(m_TouchedPos);
    
    float touchPosDegree = 90 - (touchPosAR.getAngle() * 180 / PI);
    if (touchPosDegree > 180) {
        touchPosDegree -= 360;
    }
    if (touchPosDegree < -180) {
        touchPosDegree += 360;
    }
    
    // If the angle between ship and touched point is less than
    // ROT_THRESHOLD, then good enough, no rotation. Else, rotation.
    // Will rotate clockwise or counterclockwise depending on where
    // touched point is.
    // This method is more natural to cross product, which will only
    // rotate in one direction
    const float deltaAngle = shipAngleDegree - touchPosDegree;
    if (deltaAngle < ROT_THRESHOLD && deltaAngle > 0) {
        m_pSpaceShip->SetRotDir(IDLE);
    } else {
        if (shipAngleDegree < touchPosDegree) {
            if ((touchPosDegree - shipAngleDegree) < 180) {
                m_pSpaceShip->SetRotDir(RIGHT);
            } else {
                m_pSpaceShip->SetRotDir(LEFT);
            }
        } else {
            if ((shipAngleDegree - touchPosDegree) < 180) {
                m_pSpaceShip->SetRotDir(LEFT);
            } else {
                m_pSpaceShip->SetRotDir(RIGHT);
            }
        }
    }
    
    // Determine if ship should accelerate
    if ( abs(distanceX) > CHANGE_THRESHOLD || abs(distanceY) > CHANGE_THRESHOLD ) {
        m_pSpaceShip->SetAcceleration(true);
    } else {
        m_pSpaceShip->SetAcceleration(false);
    }

    /*
    char buf[512];
    sprintf(buf, "ShipBehaviour: ship %0.02f touch %0.02f distX %d distY %d ",
            shipAngleDegree, touchPosDegree, distanceX, distanceY);
    Dir rotDir = m_pSpaceShip->GetRotDir();
    bool acc = m_pSpaceShip->GetAcceleration();
    switch(rotDir) {
        case LEFT:
            strcat(buf, "ROTATE-LEFT  ");
            break;
        case RIGHT:
            strcat(buf, "ROTATE-RIGHT ");
            break;
        case IDLE:
            strcat(buf, "ROTATE-IDLE  ");
            break;
        default:
            strcat(buf, "ROTATE-ERROR ");
    }
    if (true == acc) {
        strcat(buf, "ACCELERATE-TRUE");
    } else {
        strcat(buf, "ACCELERATE-FALSE");
    }
    
    CCLog(buf);
    */
}

bool GameMain::UpdateAutoFireDisplay()
{
    bool retValue = true;
    
    if (true == m_EnableAutoFire) {
        m_pBulletStatus[0]->setVisible(true);
        m_pBulletStatus[1]->setVisible(false);
    } else {
        m_pBulletStatus[0]->setVisible(false);
        m_pBulletStatus[1]->setVisible(true);
    }
    
    return retValue;
}

bool GameMain::AutoFireEnabled(CCPoint& rPos)
{
    bool retValue = false;
    
    if (m_BulletRect.containsPoint(rPos)) {
        retValue = true;
        if (true == m_EnableAutoFire) {
            m_EnableAutoFire = false;
            
        } else {
            m_EnableAutoFire = true;
            
            // To ensure the first bullet can be fired as soon as
            // auto-fire is newly turned on
            m_BulletTimer = SPAWN_BULLET_TIME;
        }
        UpdateAutoFireDisplay();
    }
    
    return retValue;
}

bool GameMain::MissileEnabled(CCPoint& rPos)
{
    bool retValue = false;
    if (m_MissileRect.containsPoint(rPos)) {
        retValue = true;
        if (m_NumAvailableMissiles > 0) {
            m_pMissileStatus[m_NumAvailableMissiles]->setVisible(false);
            m_NumAvailableMissiles -= 1;
            m_pMissileStatus[m_NumAvailableMissiles]->setVisible(true);
            m_MissileTimer = 0.0;
            
            FireMissile();
        }
    }
    
    return retValue;
}

void GameMain::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
    if (EXPLODED != m_pSpaceShip->GetStatus()) {
        CCSetIterator it = pTouches->begin();
        CCTouch tmpTouch = *(dynamic_cast<CCTouch *> (*it));
        CCPoint tmpTouchedPos = tmpTouch.getLocation();
        
        // Update the touched position only if the user is not setting
        // auto-fire or firing missiles
        if (false == AutoFireEnabled(tmpTouchedPos) && (false == MissileEnabled(tmpTouchedPos))) {
            m_IsTouchEvent = true;
            m_Touch = tmpTouch;
            m_TouchedPos = tmpTouchedPos;
        }
    }
    
    CCLayer::ccTouchesBegan(pTouches, pEvent);
}

void GameMain::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (EXPLODED != m_pSpaceShip->GetStatus()) {
        // Ensure the user is not moving inside firing or missile button
        for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
            CCTouch *pTouch = (CCTouch *) (*it);
            if (m_Touch.getID() == pTouch->getID() && true == m_IsTouchEvent) {
                m_Touch = *pTouch;
                m_TouchedPos = m_Touch.getLocation();
                SetShipBehaviour();
            }
        }
    }
    
    CCLayer::ccTouchesMoved(pTouches, pEvent);
}

void GameMain::ccTouchesEnded( CCSet* pTouches, CCEvent* pEvent)
{
    if (EXPLODED != m_pSpaceShip->GetStatus()) {
        m_IsTouchEvent = false;
        m_pSpaceShip->SetAcceleration(false);
        m_pSpaceShip->SetRotDir(IDLE);
    }
    
    CCLayer::ccTouchesEnded(pTouches, pEvent);
}

void GameMain::UpdateScoreDisplay()
{
    char tmpBuf[40];
    sprintf(tmpBuf, "SCORE: %018u", m_Score.GetDecryptedData());
    m_pScoreLabel->setString(tmpBuf);
}

void GameMain::FireBullet()
{
    if (false == m_EnableAutoFire) {
        return;
    }
    
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (NULL == m_pBullets[i]->getParent()) {
            m_pBullets[i]->PrepareForScene(m_pSpaceShip->getRotation(), m_pSpaceShip->getPosition());
            m_BulletNode->addChild(m_pBullets[i]);
            CocosDenshion::SimpleAudioEngine *tmpEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
            if (tmpEngine) {
                tmpEngine->playEffect("shoot.wav");
            }

            break;
        }
    }
    
 //   CCLog("FireBullet!");
}

void GameMain::FireMissile()
{
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (NULL == m_pMissiles[i]->getParent()) {
            m_pMissiles[i]->PrepareForScene(m_pSpaceShip->getRotation(), m_pSpaceShip->getPosition());
            m_pMissiles[i]->searchTarget(m_AsteroidNode);
            m_MissileNode->addChild(m_pMissiles[i]);
            CocosDenshion::SimpleAudioEngine *tmpEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
            if (tmpEngine) {
                tmpEngine->playEffect("shoot.wav");
            }
            
            break;
        }
    }
    
//    CCLog("FireMissile!");
}

void GameMain::CreateAsteroid(ASTEROID_SIZE size, ASTEROID_CREATE create, const CCPoint& rPoint)
{
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (NULL == m_pAsteroids[i]->getParent()) {
            m_pAsteroids[i]->PrepareForScene(create, size, rPoint);
            m_AsteroidNode->addChild(m_pAsteroids[i]);
//            CCLog("GameMain::CreateAsteroid: i = %d", i);
            break;
        }
    }
}

void GameMain::update(float delta)
{
    CCPoint disp = m_pSpaceShip->GetDisp(delta, m_TouchedPos);
    
    // Processing background
    m_Background[0]->updatePos(disp);
    m_Background[1]->updatePos(disp);

    CCArray *pChildren = NULL;
    
    // Processing bullets
    pChildren = m_BulletNode->getChildren();
    if (pChildren) {
        for (int i = 0; i < pChildren->count(); i++) {
            CBullet *pBullet = dynamic_cast<CBullet *> (pChildren->objectAtIndex(i));
            if (pBullet) {
                pBullet->UpdatePosition(disp, delta);
            }
        }
    }
    
    // Processing missiles
    pChildren = m_MissileNode->getChildren();
    if (pChildren) {
        for (int i = 0; i < pChildren->count(); i++) {
            CMissile *pMissile = dynamic_cast<CMissile *> (pChildren->objectAtIndex(i));
            if (pMissile) {
                pMissile->UpdatePosition(disp, delta);
            }
        }
    }
    
    // processing asteroids
    pChildren = m_AsteroidNode->getChildren();
    if (pChildren) {
        for (int i = 0; i < pChildren->count(); i++) {
            CAsteroids *pAsteroids = dynamic_cast<CAsteroids *> (pChildren->objectAtIndex(i));
            if (pAsteroids) {
                pAsteroids->UpdatePosition(disp, delta);
            }
        }
    }

    // processing explosion
    pChildren = m_ExplosionNode->getChildren();
    if (pChildren) {
        for (int i = 0; i < pChildren->count(); i++) {
            CExplosion *pExplosion = dynamic_cast<CExplosion *> (pChildren->objectAtIndex(i));
            if (pExplosion) {
                pExplosion->UpdatePosition(disp);
            }
        }
    }
    
    // Update missile course relative to updated asteroid position
    pChildren = m_MissileNode->getChildren();
    if (pChildren) {
        for (int i = 0; i < pChildren->count(); i++) {
            CMissile *pMissile = dynamic_cast<CMissile *> (pChildren->objectAtIndex(i));
            if (pMissile) {
                pMissile->updateMissile(delta);
            }
        }
    }
    
    CheckCollision();
    
    m_pSpaceShip->UpdateSpaceShipTimer(delta);
    
    m_BulletTimer += delta;
//    CCLog("Before: m_BulletTimer = %0.4f", m_BulletTimer);
    while (m_BulletTimer > SPAWN_BULLET_TIME) {
        FireBullet();
        m_BulletTimer -= SPAWN_BULLET_TIME;
//        CCLog("After: m_BulletTimer = %0.4f", m_BulletTimer);
    }
    
    m_MissileTimer += delta;
    while (m_MissileTimer > SPAWN_MISSILE_TIME) {
        if (m_NumAvailableMissiles < MAX_MISSILES) {
            m_pMissileStatus[m_NumAvailableMissiles]->setVisible(false);
            m_NumAvailableMissiles += 1;
            m_pMissileStatus[m_NumAvailableMissiles]->setVisible(true);
        }
        m_MissileTimer -= SPAWN_MISSILE_TIME;
    }
    
    m_AsteroidTimer += delta;
    while (m_AsteroidTimer > SPAWN_ASTEROID_TIME) {
        CreateAsteroid();
        m_AsteroidTimer -= SPAWN_ASTEROID_TIME;
    }

    if (true == m_IsTouchEvent) {
        SetShipBehaviour();
    }
    
    UpdateScoreDisplay();

}

void GameMain::CheckCollision()
{
    CheckBulletCollision();
    CheckMissileCollision();
    // Commented out during debugging
    CheckShipCollision();
}

void GameMain::CheckBulletCollision()
{
    CCArray *pBulletArray = m_BulletNode->getChildren();
    if (pBulletArray) {
        int i = 0;
        while (i < pBulletArray->count()) {
            bool hit = false;
            CBullet *pBullet = dynamic_cast<CBullet *>(pBulletArray->objectAtIndex(i));
            if (pBullet) {
                const CCPoint loc = pBullet->getPosition();
                
                CCArray *pAsteroidsArray = m_AsteroidNode->getChildren();
                if (pAsteroidsArray) {
                    int j = 0;
                    while (j < pAsteroidsArray->count()) {
                        CAsteroids *pAsteroid = dynamic_cast<CAsteroids *>(pAsteroidsArray->objectAtIndex(j));
                        const CCPoint asteroidPos = pAsteroid->getPosition();
                        const float rockRadius = pAsteroid->getRadius();
                        
                        if (loc.getDistanceSq(asteroidPos) < (rockRadius * rockRadius)) {
                            // perform explosion effects
                            CExplosion *pExplosion = CExplosion::create();
                            if (pExplosion) {
                                pExplosion->retain();
                                pExplosion->setPosition(loc);
                                m_ExplosionNode->addChild(pExplosion);
                            }
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explo.wav");
     
                            // get the score
                            m_Score += pAsteroid->getAsteroidScore();
                            const ASTEROID_SIZE asteroidSize = pAsteroid->getAsteroidSize();
                            
                            // Tidy up
                            pBullet->removeFromParent();
                            pAsteroid->removeFromParent();
                            
                            
                            // Spawn new asteroids whose size and positionis based on current one
                            switch(asteroidSize) {
                                case LARGE:
                                    CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                                    CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                                    break;
                                case MEDIUM:
                                    CreateAsteroid(SMALL, SPLIT, asteroidPos);
                                    CreateAsteroid(SMALL, SPLIT, asteroidPos);
                                    break;
                                // do nothing for small
                            }
                            
                            hit = true;
                            break;
                        }
                        
                        ++j;
                    }
                }
            }

            // If hit, current entry is removed and next entry shared same index
            // hence, only increment index if not hit
            if (true == hit) {
                continue;
            } else {
                i++;
            }
        }
    }
}

void GameMain::CheckMissileCollision()
{
    CCArray *pMissileArray = m_MissileNode->getChildren();
    if (pMissileArray) {
        int i = 0;
        while (i < pMissileArray->count()) {
            bool hit = false;
            CMissile *pMissile = dynamic_cast<CMissile *>(pMissileArray->objectAtIndex(i));
            if (pMissile) {
                const CCPoint loc = pMissile->getPosition();
                
                CCArray *pAsteroidsArray = m_AsteroidNode->getChildren();
                if (pAsteroidsArray) {
                    int j = 0;
                    while (j < pAsteroidsArray->count()) {
                        CAsteroids *pAsteroid = dynamic_cast<CAsteroids *>(pAsteroidsArray->objectAtIndex(j));
                        const CCPoint asteroidPos = pAsteroid->getPosition();
                        const float rockRadius = pAsteroid->getRadius();
                        
                        if (loc.getDistanceSq(asteroidPos) < (rockRadius * rockRadius)) {
                            // perform explosion effects
                            CExplosion *pExplosion = CExplosion::create();
                            if (pExplosion) {
                                pExplosion->retain();
                                pExplosion->setPosition(loc);
                                m_ExplosionNode->addChild(pExplosion);
                            }
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explo.wav");
                            
                            // get the score
                            m_Score += pAsteroid->getAsteroidScore();
                            const ASTEROID_SIZE asteroidSize = pAsteroid->getAsteroidSize();
                            
                            // Tidy up
                            pMissile->removeFromParent();
                            pAsteroid->removeFromParent();
                            
                            // Spawn new asteroids whose size and positionis based on current one
                            switch(asteroidSize) {
                                case LARGE:
                                    CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                                    CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                                    break;
                                case MEDIUM:
                                    CreateAsteroid(SMALL, SPLIT, asteroidPos);
                                    CreateAsteroid(SMALL, SPLIT, asteroidPos);
                                    break;
                                // do nothing for small
                            }
                            
                            hit = true;
                            break;
                        }
                        
                        ++j;
                    }
                }
            }
            
            // Same logic goes for bullet as in asteroid
            if (true == hit) {
                continue;
            } else {
                i++;
            }
        }
    }
}

void GameMain::CheckShipCollision()
{
    // Don't need to continue if space-ship has exploded and is resetting
    if (READY != m_pSpaceShip->GetStatus()) return;

    const CCPoint shipPos = m_pSpaceShip->getPosition();
    const float shipRadius = m_pSpaceShip->GetRadius();
    CCArray *pAsteroidArray = m_AsteroidNode->getChildren();
    if (pAsteroidArray) {
        int i = 0;
        while (i < pAsteroidArray->count()) {
            CAsteroids *pAsteroid = dynamic_cast<CAsteroids *>(pAsteroidArray->objectAtIndex(i));
            const CCPoint asteroidPos = pAsteroid->getPosition();
            const float rockRadius = pAsteroid->getRadius();
            
            if (shipPos.getDistanceSq(asteroidPos) < (rockRadius * rockRadius + shipRadius * shipRadius)) {
                CExplosion *pExplosion = CExplosion::create();
                if (pExplosion) {
                    pExplosion->retain();
                    pExplosion->setPosition(shipPos);
                    m_ExplosionNode->addChild(pExplosion);
                }
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explo.wav");
                
                // get the score
                m_Score += pAsteroid->getAsteroidScore();
                const ASTEROID_SIZE asteroidSize = pAsteroid->getAsteroidSize();
                
                // Tidy up
                pAsteroid->removeFromParent();
                // Reset SpaceShip's game parameters
                m_EnableAutoFire = false;
                UpdateAutoFireDisplay();
                m_IsTouchEvent = false;
                m_pSpaceShip->SetStatus(EXPLODED);

                // Spawn new asteroids whose size and positionis based on current one
                switch(asteroidSize) {
                    case LARGE:
                        CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                        CreateAsteroid(MEDIUM, SPLIT, asteroidPos);
                        break;
                    case MEDIUM:
                        CreateAsteroid(SMALL, SPLIT, asteroidPos);
                        CreateAsteroid(SMALL, SPLIT, asteroidPos);
                        break;
                        // do nothing for small
                }

                break;
            }
            
            ++i;
        }
    }
}

void GameMain::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
