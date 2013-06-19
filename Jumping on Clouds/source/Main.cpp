
#include "IwGL.h"
#include "cocos2d.h"
#include "appwarp.h"
#include "AppDelegate.h"

static int32 Pause(void *sys, void *user)
{
	cocos2d::CCDirector::sharedDirector()->pause();
	cocos2d::CCDirector::sharedDirector()->stopAnimation();

	return 0;
}

static int32 UnPause(void *sys, void *user)
{
	cocos2d::CCDirector::sharedDirector()->resume();
	cocos2d::CCDirector::sharedDirector()->startAnimation();

	return 0;
}

int main()
{
	AppDelegate app;
	s3eDeviceRegister(S3E_DEVICE_PAUSE, Pause,NULL);
	s3eDeviceRegister(S3E_DEVICE_UNPAUSE, UnPause,NULL);
	return cocos2d::CCApplication::sharedApplication()->Run();
}