
#ifndef __SINGLE_PLAYER__
#define __SINGLE_PLAYER__

#include "cocos2d.h"

class SinglePlayer : public cocos2d::CCLayer
{
	cocos2d::CCPoint cloud_velocity;
	cocos2d::CCLayerColor *bg;
	cocos2d::CCPoint Velocity;
	cocos2d::CCPoint Acceleration;
	cocos2d::CCLayer *game;
	cocos2d::CCLayer *blocks;
	cocos2d::CCSprite *hero;
	int direction; // 1-left,2-right,3-neutral
public:
	SinglePlayer();
	static cocos2d::CCScene *scene();
	virtual bool init();
	virtual void update(float);
	virtual void didAccelerate(cocos2d::CCAcceleration*);
	virtual void keyBackClicked();
	CREATE_FUNC(SinglePlayer);
};

#endif