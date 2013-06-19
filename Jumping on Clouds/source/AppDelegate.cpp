#include "AppDelegate.h"
#include "IntroScreen.h"

using namespace cocos2d;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

	CCScene *scene = IntroScreen::scene();
	CCDirector::sharedDirector()->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    cocos2d::CCDirector::sharedDirector()->pause();
	cocos2d::CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    cocos2d::CCDirector::sharedDirector()->resume();
	cocos2d::CCDirector::sharedDirector()->startAnimation();
}

void AppDelegate::applicationBackKeyPressed()
{
	//s3eDeviceExit();
	CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
	if(scene->getChildrenCount() > 0)
	{
		CCArray *layers = scene->getChildren();
		CCLayer *layer = (CCLayer*)layers->lastObject();
		layer->keyBackClicked();
	}
}
