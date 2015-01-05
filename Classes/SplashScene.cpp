//
//  SplashScene.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/18/14.
//
//

#include "SplashScene.h"
#include "GameScene.h"

const float SplashScreen::DELAY_SHOW_PROMPT_TIME = 1;
const float SplashScreen::MOVE_TO_NEXT_SCENE_TIME = 1;

SplashScreen::~SplashScreen()
{
}

CCScene* SplashScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScreen *layer = SplashScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool SplashScreen::init()
{
    if ( !CCLayer::init())
    {
        return false;
    }

    m_TimeCounter = 0;
    m_IsScreenTouched = false;
    
    const CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    const CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    const CCPoint titleCtr(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    const CCPoint promptCtr(ccp(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));

    // Create the title
    m_pTitleLabel = CCSprite::create("TITLE.png");
    if (NULL != m_pTitleLabel) {
        m_pTitleLabel->cocos2d::CCNode::setPosition(titleCtr);
    } else {
        return false;
    }
    
    // Create the prompt
    m_pPromptLabel = CCLabelTTF::create("Please tap screen to continue", "Arial", 20);
    if (NULL != m_pPromptLabel) {
        m_pPromptLabel->cocos2d::CCNode::setPosition(promptCtr);
        m_pPromptLabel->setVisible(false);
    } else {
        return false;
    }
    
    // Create the assignment label
    m_pAssignmentLabel = CCLabelTTF::create("By Wilson Meng", "Arial", 20);
    if (NULL != m_pAssignmentLabel) {
        m_pAssignmentLabel->setAnchorPoint(ccp(0,0));
        m_pAssignmentLabel->cocos2d::CCNode::setPosition(ccp(0,0));
    } else {
        return false;
    }
    
    this->addChild(m_pTitleLabel, Z_TITLE);
    this->addChild(m_pPromptLabel, Z_PROMPT);
    this->addChild(m_pAssignmentLabel, Z_PROMPT);
    
    scheduleUpdate();
    setTouchEnabled(true);
    
    return true;
}

void SplashScreen::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (false == m_IsScreenTouched) {
        m_IsScreenTouched = true;
        m_pPromptLabel->setVisible(false);
        m_pAssignmentLabel->setVisible(false);
    
        // reset time counter to track when to move to next screen
        m_TimeCounter = 0;
    
        CCSpawn *pSpawn = CCSpawn::create(CCFadeOut::create(MOVE_TO_NEXT_SCENE_TIME),
                                          CCScaleBy::create(MOVE_TO_NEXT_SCENE_TIME, 8),
                                          NULL);

        if (pSpawn) {
            m_pTitleLabel->runAction(pSpawn);
        }
    }
}

void SplashScreen::ccTouchesCancelled(CCSet* pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

// If screen is not touched, then display the prompt after a period of time (DELAY_SHOW_PROMPT_TIME)
// If screen is touched, then change to next scene after a period of time (MOVE_TO_NEXT_SCENE_TIME)
void SplashScreen::update(float delta)
{
    m_TimeCounter += delta;
    if (true == m_IsScreenTouched) {
        if (m_TimeCounter > MOVE_TO_NEXT_SCENE_TIME) {

            CCScene *pScene = GameMain::scene();
            if (pScene) {
                CCDirector::sharedDirector()->replaceScene(pScene);
            }
        }
    } else {
        if (m_TimeCounter > DELAY_SHOW_PROMPT_TIME) {
            m_pPromptLabel->setVisible(true);
        }
    }
}

void SplashScreen::menuCloseCallback(CCObject* pSender)
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