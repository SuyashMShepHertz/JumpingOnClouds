
#include "MenuScreen.h"
#include "SinglePlayer.h"

using namespace cocos2d;

cocos2d::CCScene *MenuScreen::scene()
{
	CCScene *scene = CCScene::create();
	MenuScreen *layer = MenuScreen::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScreen::init()
{
	if(!CCLayer::init())
		return false;

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("bg.png");
	ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	texture->setTexParameters(&params);
	CCSprite *bg = CCSprite::createWithTexture(texture,CCRectMake(0,0,CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width+32,CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height+32));
	bg->setPosition(CCPoint(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width/2,CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height/2));
	bg->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.5f,CCPoint(-16.0f,16.0f)),CCMoveBy::create(0.0f,CCPoint(16.0f,-16.0f)),NULL)));
	this->addChild(bg);

	CCMenuItemImage *title = CCMenuItemImage::create("gametitle.png","gametitle.png",NULL,NULL);
	CCMenuItemImage *btn_new = CCMenuItemImage::create("btn_new.png","btn_new.png",this,menu_selector(MenuScreen::StartSinglePlayer));
	CCMenuItemImage *btn_multi = CCMenuItemImage::create("btn.png","btn.png",NULL,NULL);
	CCMenuItemImage *btn_help = CCMenuItemImage::create("btn.png","btn.png",NULL,NULL);
	CCMenuItemImage *btn_credits = CCMenuItemImage::create("btn.png","btn.png",NULL,NULL);
	CCMenu *menu = CCMenu::create(title,btn_new,btn_multi,btn_help,btn_credits,NULL);
	menu->alignItemsVerticallyWithPadding(4.0f);
	this->addChild(menu);

	return true;
}

void MenuScreen::StartSinglePlayer(CCObject* sender)
{
	CCScene *scene = SinglePlayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL ::create(1.0f,scene));
}

void MenuScreen::keyBackClicked()
{
	s3eDeviceExit();
}