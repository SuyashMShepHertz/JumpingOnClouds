
#include "IntroScreen.h"
#include "MenuScreen.h"

using namespace cocos2d;

cocos2d::CCScene *IntroScreen::scene()
{
	CCScene *scene = CCScene::create();
	IntroScreen *layer = IntroScreen::create();
	scene->addChild(layer);

	return scene;
}

bool IntroScreen::init()
{
	if(!CCLayer::init())
		return false;

	CCLayerColor *bg = new CCLayerColor;
	bg->initWithColor(ccc4(255,255,255,255));
	this->addChild(bg);

	cocos2d::CCSprite *logo = new CCSprite;
	logo->initWithFile("shephertz.png");
	logo->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
	logo->runAction(CCSequence::create(CCFadeIn::create(3.0f),CCCallFuncN::create(this,callfuncN_selector(IntroScreen::LogoFadeInDone)),NULL));
	this->addChild(logo);

	return true;
}

void IntroScreen::LogoFadeInDone(CCNode *node)
{
	CCScene *menu = MenuScreen::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(2.0f,menu));
}

void IntroScreen::keyBackClicked()
{
	IwDebugTraceLinePrintf("Key Back");
}