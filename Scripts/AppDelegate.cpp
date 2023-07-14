#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Scene/LoadingScene.h"
#include "GameData/EntityData.h"
#include "GameConfig.h"
#include "Manager/GameManager.h"
#include "Player/InformationScene.h"
#include "Scene/HomeScene.h"
#include "Scene/SettingScene.h"
#include "Settings/Setting.h"

#include "Scene/SkillCollection.h"
#include "Scene/ShopScene.h"


#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 720);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Luna's Chronicles", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Luna's Chronicles");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    designResolutionSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    director->setContentScaleFactor(720.0f / frameSize.height);
    register_all_packages();


    // Init Game Config first
    GameConfig::getIns();
    Setting::loadSettings();

    // Init Database first
    //GameData::Database::getIns()->deleteDatabase();
    GameData::Database::getIns();

    //-------------------------------

    auto scene = HomeScene::create();
    //auto scene = SettingScene::create();
    // create a scene. it's an autorelease object

    //GameManager::getIns()->playChapterID(1);

    auto skillScene = SkillCollection::create();
    auto shopScene = ShopScene::create();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
