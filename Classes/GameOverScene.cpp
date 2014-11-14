#include "GameOverScene.h"
#include "systemScene.h"
#include "GameRunningScene.h"

#include "playerData.h"

USING_NS_CC;

cocos2d::Scene* GameOverLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	auto spriteBg = Sprite::createWithSpriteFrameName("gameOver.png");//"game_over.png"
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg, 0);

	auto systemNormal = Sprite::createWithSpriteFrameName("smallSys_n.png");
	auto systemSelected = Sprite::createWithSpriteFrameName("smallSys_s.png");
	auto systemItem = MenuItemSprite::create(systemNormal,systemSelected,CC_CALLBACK_0(GameOverLayer::menuSystemCallback,this));
	systemItem->setPosition(Vec2(origin.x + visibleSize.width - systemNormal->getContentSize().width ,origin.y + systemNormal->getContentSize().height));

	auto continueNormal = Sprite::createWithSpriteFrameName("playagain_n.png");
	auto continueSelected = Sprite::createWithSpriteFrameName("playagain_s.png");
	auto continueItem = MenuItemSprite::create(continueNormal,continueSelected,CC_CALLBACK_0(GameOverLayer::menuNewGameCallback,this));
	continueItem->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-continueSelected->getContentSize().height*2);

	auto scoreSprite = Sprite::createWithSpriteFrameName("score.png");
	Value score(PlayerData::getInstance()->getScore());
	auto scoreLabel = Label::createWithBMFont("teris_font.fnt"
											,score.getDescription());

	//sprite.x = [v.w-(sprite.w+label.w)]/2+sprite.w/2 = v.w/2-label.w/2
	//label.x = v.w-[v.w-(sprite.w+label.w)]/2-label.w/2 = v.w/2 + sprite.w/2
	scoreSprite->setPosition(origin.x+visibleSize.width/2-scoreLabel->getContentSize().width*0.5-1, origin.y+visibleSize.height*0.6);
	scoreLabel->setPosition(Vec2(origin.x+visibleSize.width/2+scoreSprite->getContentSize().width/2+1,origin.y+visibleSize.height*0.615));
	
	this->addChild(scoreLabel);
	this->addChild(scoreSprite);

	auto topScoreSprite = Sprite::createWithSpriteFrameName("topScore.png");
	Value topScore(PlayerData::getInstance()->getTopScore());
	auto topScoreLabel = Label::createWithBMFont("teris_font.fnt"
											,topScore.getDescription());

	//sprite.x = [v.w-(sprite.w+label.w)]/2+sprite.w/2 = v.w/2-label.w/2
	//label.x = v.w-[v.w-(sprite.w+label.w)]/2-label.w/2 = v.w/2 + sprite.w/2
	topScoreSprite->setPosition(origin.x+visibleSize.width/2-topScoreLabel->getContentSize().width*0.5-1, origin.y+visibleSize.height*0.5);
	topScoreLabel->setPosition(Vec2(origin.x+visibleSize.width/2+topScoreSprite->getContentSize().width/2+1,origin.y+visibleSize.height*0.518));
	this->addChild(topScoreSprite);
	this->addChild(topScoreLabel);

	auto menu = Menu::create(continueItem, systemItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

    return true;
}

void GameOverLayer::menuNewGameCallback()
{
	Director::getInstance()->replaceScene(GameRunning::createScene());

}

void GameOverLayer::menuSystemCallback()
{
	Director::getInstance()->pushScene(SystemSetLayer::createScene());
}
