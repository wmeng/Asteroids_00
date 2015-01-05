#include "AppDelegate.h"
#include "SplashScene.h"
#include "GameScene.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    int AppDelegate::SCREEN_WIDTH = 960;
    int AppDelegate::SCREEN_HEIGHT = 540;
#else // XCODE
    int AppDelegate::SCREEN_WIDTH = 960;
    int AppDelegate::SCREEN_HEIGHT = 640;
#endif

AppDelegate::AppDelegate() {
    // use simple way to seed the random algorithm
    srand(time(NULL));
    
    m_pSimpleAudioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    if (m_pSimpleAudioEngine) {
        m_pSimpleAudioEngine->preloadBackgroundMusic("BGM.mp3");
        m_pSimpleAudioEngine->preloadEffect("explo.wav");
        m_pSimpleAudioEngine->preloadEffect("shoot.wav");
        
        // play background music
        m_pSimpleAudioEngine->playBackgroundMusic("BGM.mp3", true);
    }
}

AppDelegate::~AppDelegate()
{
    if (m_pSimpleAudioEngine)
    {
        m_pSimpleAudioEngine->stopBackgroundMusic(true);
        m_pSimpleAudioEngine->stopAllEffects();
        m_pSimpleAudioEngine->unloadEffect("explo.wav");
        m_pSimpleAudioEngine->unloadEffect("shoot.wav");

        m_pSimpleAudioEngine->end();
    }
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    pEGLView->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, kResolutionNoBorder);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = SplashScreen::scene();
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    m_pSimpleAudioEngine->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    m_pSimpleAudioEngine->resumeBackgroundMusic();
}
