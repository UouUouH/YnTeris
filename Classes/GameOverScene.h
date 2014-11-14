#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
	void menuNewGameCallback();
	void menuSystemCallback();
    CREATE_FUNC(GameOverLayer);
};

#endif // __GAME_OVER_SCENE_H__
