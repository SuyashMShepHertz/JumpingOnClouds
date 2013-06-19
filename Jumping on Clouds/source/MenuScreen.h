
#ifndef __MENU_SCREEN__
#define __MENU_SCREEN__

#include "cocos2d.h"

class MenuScreen : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene *scene();
	virtual bool init();
	virtual void keyBackClicked();
	void StartSinglePlayer(CCObject* );
	CREATE_FUNC(MenuScreen);
};

#endif