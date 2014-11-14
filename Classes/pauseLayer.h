#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
	void menuContinueCallback();
	void menuNewGameCallback();
	void menuSystemCallback();
    CREATE_FUNC(PauseLayer);
};

#endif // __HELLOWORLD_SCENE_H__
