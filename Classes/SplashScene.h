//
//  SplashScene.h
//  Asteroids
//
//  Created by Wilson Meng on 12/18/14.
//
//

#ifndef __Asteroids__SplashScene__
#define __Asteroids__SplashScene__

#include "cocos2d.h"

USING_NS_CC;

class SplashScreen : public cocos2d::CCLayer
{
protected:
    
    static const float DELAY_SHOW_PROMPT_TIME;
    static const float MOVE_TO_NEXT_SCENE_TIME;
    
    enum Z_OBJECT {
        Z_PROMPT,
        Z_TITLE
    };
    
    CCSprite    *m_pTitleLabel;
    CCLabelTTF  *m_pPromptLabel;
    CCLabelTTF  *m_pAssignmentLabel;
    
    float m_TimeCounter;
    bool m_IsScreenTouched;
    
public:
    ~SplashScreen();

    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet* pTouches, CCEvent *pEvent);

    virtual bool init();
    static cocos2d::CCScene* scene();

    void menuCloseCallback(CCObject* pSender);
    void update(float delta);
    
    CREATE_FUNC(SplashScreen);
    
};

#endif /* defined(__Asteroids__SplashScene__) */
