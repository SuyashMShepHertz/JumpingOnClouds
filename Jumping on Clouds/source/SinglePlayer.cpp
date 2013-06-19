
#include "SinglePlayer.h"
#include "MenuScreen.h"

using namespace cocos2d;

const int MAP_X = 3;
const int MAP_Y = 20;
float map[MAP_Y][MAP_X] = 
{
	{0.0f,1.0f,0.0f},
	{0.8f,0.0f,0.0f},
	{0.0f,1.2f,0.0f},
	{0.0f,0.0f,0.8f},
	{0.0f,1.2f,0.0f},
	{0.0f,0.0f,0.8f},
	{0.0f,1.0f,0.0f},
	{0.8f,0.0f,0.0f},
	{0.6f,0.0f,0.0f},
	{0.4f,0.0f,0.0f},
	{1.2f,0.0f,0.0f},
	{0.0f,1.0f,0.0f},
	{0.5f,0.0f,1.5f},
	{0.0f,1.0f,0.0f},
	{0.0f,1.2f,0.0f},
	{0.0f,1.4f,0.0f},
	{0.0f,1.6f,0.0f},
	{0.0f,1.8f,0.0f},
	{0.0f,1.2f,0.0f},
	{0.0f,0.6f,0.0f}
};

SinglePlayer::SinglePlayer()
{
	cloud_velocity = ccp(-10.0f,0.0f);
	Velocity = ccp(0.0f,300.0f);
	Acceleration = ccp(0.0f,-300.0f);
	direction = 3;

	scheduleUpdate();
}

cocos2d::CCScene *SinglePlayer::scene()
{
	CCScene *scene = CCScene::create();
	SinglePlayer *layer = SinglePlayer::create();
	scene->addChild(layer);

	return scene;
}

bool SinglePlayer::init()
{
	if(!CCLayer::init())
		return false;

	this->setAccelerometerEnabled(true);

	bg = new CCLayerColor;
	bg->initWithColor(ccc4(98,183,214,255));

	CCSprite *cloud1 = new CCSprite;
	cloud1->initWithFile("bg_cloud1.png");
	cloud1->setPosition(CCPoint(cloud1->getContentSize().width/2,CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height/2));
	CCSprite *cloud2 = new CCSprite;
	cloud2->initWithFile("bg_cloud2.png");
	cloud2->setPosition(CCPoint(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width - cloud2->getContentSize().width/2,CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height - cloud2->getContentSize().height/2));
	CCSprite *cloud3 = new CCSprite;
	cloud3->initWithFile("bg_cloud3.png");
	cloud3->setPosition(CCPoint(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width - cloud3->getContentSize().width/2,cloud3->getContentSize().height/2));

	bg->addChild(cloud1);
	bg->addChild(cloud2);
	bg->addChild(cloud3);

	this->addChild(bg);

	CCSize cloud_size;
	CCSprite *pad;
	game = new CCLayer;
	blocks = new CCLayer;
	for(int i=0; i<MAP_Y; i++)
	{
		for(int j=0; j<MAP_X; j++)
		{
			if(map[i][j] > 0.0f)
			{
				pad = new CCSprite;
				pad->initWithFile("cloud2.png");
				cloud_size = pad->getContentSize();
				pad->setPosition(CCPoint(map[i][j]*CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width/2, i*100.0f));
				blocks->addChild(pad);
			}
		}
	}
	game->addChild(blocks);

	hero = new CCSprite;
	hero->initWithFile("char_jump_1.png");
	hero->setPosition(CCPoint(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width/2, cloud_size.height));
	game->addChild(hero);

	this->addChild(game);

	return true;
}

void SinglePlayer::update(float delta)
{
	CCObject *obj;
	float x = 1.0f;
	CCPoint endPoint;
	CCARRAY_FOREACH(bg->getChildren(),obj)
	{
		CCSprite *spirit = (CCSprite *)obj;
		if(spirit->getPositionX() < -spirit->getContentSize().width/2)
		{
			spirit->setPositionX(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width + spirit->getContentSize().width/2);
		}
		else
		{
			spirit->setPosition(ccpAdd(spirit->getPosition(),ccpMult(CCPoint(cloud_velocity.x * x,cloud_velocity.y),delta)));
		}
		x+=1.0f;
	}

	CCPoint pos = hero->getPosition();
	Velocity = ccpAdd(Velocity, ccpMult(Acceleration,delta));
	
	CCARRAY_FOREACH(blocks->getChildren(),obj)
	{
		CCSprite *spirit = (CCSprite *)obj;
		CCRect heroBox(hero->getPositionX(),hero->getPositionY()-hero->getContentSize().height/2 + 2.0f,hero->getContentSize().width,2.0f);
		if(Velocity.y < 0.0f)
		{
			if(spirit->boundingBox().intersectsRect(heroBox))
			{
				Velocity = ccp(0.0f,300.0f);
				Acceleration = ccp(0.0f,-300.0f);
			}
		}
		if(blocks->convertToWorldSpace(spirit->getPosition()).y < 0.0f)
		{
			endPoint = spirit->getPosition();
			spirit->setPosition(ccpAdd(spirit->getPosition(),ccp(0.0f,MAP_Y*100.0f)));
		}
	}

	if(direction == 1)
		Velocity.x = -100.0f;
	else if(direction == 2)
		Velocity.x = 100.0f;
	else
		Velocity.x = 0.0f;

	pos = ccpAdd(pos, ccpMult(Velocity,delta));

	if(pos.y < endPoint.y)
	{
		CCScene *scene = MenuScreen::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
	}

	hero->setPosition(pos);
	game->setPosition(ccp(0.0f,-1*(pos.y - CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height/2)));

}

void SinglePlayer::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
	if(pAccelerationValue->x < 0)
	{
		direction = 1;
		hero->setFlipX(true);
	}
	else if(pAccelerationValue->x > 0)
	{
		direction = 2;
		hero->setFlipX(false);
	}
	else
	{
		direction = 3;
	}
}

void SinglePlayer::keyBackClicked()
{
	CCScene *scene = MenuScreen::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.0f,scene));
}