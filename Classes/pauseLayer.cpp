#include "pauseLayer.h"
#include "systemScene.h"
#include "GameRunningScene.h"
USING_NS_CC;



// on "init" you need to initialize your instance
bool PauseLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto spriteBg = Sprite::createWithSpriteFrameName("guide1Bg.png");
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg, 0);

	auto systemNormal = Sprite::createWithSpriteFrameName("system_n.png");
	auto systemSelected = Sprite::createWithSpriteFrameName("system_s.png");
	auto systemItem = MenuItemSprite::create(systemNormal,systemSelected,CC_CALLBACK_0(PauseLayer::menuSystemCallback,this));
	systemItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-systemNormal->getContentSize().height*0.5);

	auto continueNormal = Sprite::createWithSpriteFrameName("continue_n.png");
	auto continueSelected = Sprite::createWithSpriteFrameName("continue_s.png");
	auto continueItem = MenuItemSprite::create(continueNormal,continueSelected,CC_CALLBACK_0(PauseLayer::menuContinueCallback,this));
	continueItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-continueSelected->getContentSize().height*1.5);



	auto newGameNormal = Sprite::createWithSpriteFrameName("newGame_n.png");
	auto newGameSelected = Sprite::createWithSpriteFrameName("newGame_s.png");
	auto newGameItem = MenuItemSprite::create(newGameNormal,newGameSelected,CC_CALLBACK_0(PauseLayer::menuNewGameCallback,this));
	newGameItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-newGameSelected->getContentSize().height*2.5);

	
	auto menu = Menu::create(continueItem, newGameItem, systemItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
    return true;
}

void PauseLayer::menuContinueCallback()
{
	this->setVisible(false);
	((GameRunning*)this->getParent())->runCountdownAnimate(false);
}
void PauseLayer::menuNewGameCallback()
{
	Director::getInstance()->replaceScene(GameRunning::createScene());
	//Director::getInstance()->re
}

void PauseLayer::menuSystemCallback()
{
	Director::getInstance()->pushScene(SystemSetLayer::createScene());
}
