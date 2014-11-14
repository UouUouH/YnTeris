#include "HelloWorldScene.h"
#include "GameRunningScene.h"

#include "systemScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto spriteBg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Default.png"));
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg, 0);
	
	this->scheduleOnce(schedule_selector(HelloWorld::loadImg),1);

    return true;
}
void HelloWorld::loadImg(float)
{
	

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("teris.plist");
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spriteBg = Sprite::createWithSpriteFrameName("guide1Bg.png");
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg);

	auto sysSetNormal = Sprite::createWithSpriteFrameName("smallSys_n.png");
	auto sysSetSelected = Sprite::createWithSpriteFrameName("smallSys_s.png");
	auto sysSetItem = MenuItemSprite::create(sysSetNormal,sysSetSelected,
		CC_CALLBACK_1(HelloWorld::menuSysSetCallback,this));
	sysSetItem->setPosition(Vec2(origin.x + visibleSize.width - sysSetNormal->getContentSize().width ,origin.y + sysSetNormal->getContentSize().height));

	auto playNormal = Sprite::createWithSpriteFrameName("play_n.png");
	auto playSelected = Sprite::createWithSpriteFrameName("play_s.png");
	auto playItem = MenuItemSprite::create(playNormal,playSelected,
		CC_CALLBACK_1(HelloWorld::menuPlayCallback,this));
	playItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-playNormal->getContentSize().height));

	auto menu = Menu::create(sysSetItem, playItem,NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}
void HelloWorld::menuSysSetCallback(Ref* pSender)
{
	Director::getInstance()->pushScene(SystemSetLayer::createScene());
}
void HelloWorld::menuPlayCallback(Ref* pSender)
{
	//Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(0.5f,GameRunning::createScene()));
	Director::getInstance()->replaceScene(GameRunning::createScene());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
