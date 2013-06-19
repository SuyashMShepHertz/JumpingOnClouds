
#ifndef __INTRO_SCREEN__
#define __INTRO_SCREEN__

#include "cocos2d.h"

class IntroScreen : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene *scene();
	virtual bool init();
	virtual void keyBackClicked();
	void LogoFadeInDone(cocos2d::CCNode *);
	CREATE_FUNC(IntroScreen);
};

#endif