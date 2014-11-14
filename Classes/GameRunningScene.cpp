#include "GameRunningScene.h"
#include "Define.h"
#include "pauseLayer.h"
#include "Block.h"
#include "playerData.h"
#include "GameOverScene.h"
USING_NS_CC;

Scene* GameRunning::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameRunning::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameRunning::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	srand((unsigned)time(NULL));  
	auto spriteBg = Sprite::createWithSpriteFrameName("gameBg.png");
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg, 0);

	auto pauseNormal = Sprite::createWithSpriteFrameName("pause_n.png");
	auto pauseSelected = Sprite::createWithSpriteFrameName("pause_s.png");
	auto pauseItem = MenuItemSprite::create(pauseNormal, pauseSelected, CC_CALLBACK_0(GameRunning::menuPauseCallback,this));
	pauseItem->setPosition(PAUSE_X, PAUSE_Y);

	auto rightNormal = Sprite::createWithSpriteFrameName("right_n.png");
	auto rightSelected = Sprite::createWithSpriteFrameName("right_s.png");
	auto rightItem = MenuItemSprite::create(rightNormal, rightSelected,CC_CALLBACK_0(GameRunning::menuMoveRightCallback,this));
	rightItem->setPosition(RIGHT_X, RIGHT_Y);

	auto leftNormal = Sprite::createWithSpriteFrameName("left_n.png");
	auto leftSelected = Sprite::createWithSpriteFrameName("left_s.png");
	auto leftItem = MenuItemSprite::create(leftNormal, leftSelected,CC_CALLBACK_0(GameRunning::menuMoveLeftCallback,this));
	leftItem->setPosition(LEFT_X, LEFT_Y);

	auto downNormal = Sprite::createWithSpriteFrameName("down_n.png");
	auto downSelected = Sprite::createWithSpriteFrameName("down_s.png");
	auto downItem = MenuItemSprite::create(downNormal, downSelected,CC_CALLBACK_0(GameRunning::menuMoveDownCallback,this));
	downItem->setPosition(DOWN_X, DOWN_Y);

	auto fastNormal = Sprite::createWithSpriteFrameName("fast_n.png");
	auto fastSelected = Sprite::createWithSpriteFrameName("fast_s.png");
	auto fastItem = MenuItemSprite::create(fastNormal, fastSelected,CC_CALLBACK_0(GameRunning::menuMoveFastCallback,this));
	fastItem->setPosition(FAST_X, FAST_Y);

	auto turnNormal = Sprite::createWithSpriteFrameName("turn_n.png");
	auto turnSelected = Sprite::createWithSpriteFrameName("turn_s.png");
	auto turnItem = MenuItemSprite::create(turnNormal, turnSelected,CC_CALLBACK_0(GameRunning::menuTurnCallback,this));
	turnItem->setPosition(TURN_X, TURN_Y);

	_controlMenu = Menu::create(pauseItem, rightItem, leftItem, downItem, fastItem, turnItem, NULL);
	_controlMenu->setPosition(Vec2::ZERO);
	this->addChild(_controlMenu);

	_blocks = Blocks::create();
	_blocks->setPosition(Vec2::ZERO);
	_blocks->setVisible(false);
	this->addChild(_blocks);
	
	

	Value level(PlayerData::getInstance()->getInitLevel());
	_levelLabel = Label::createWithBMFont("teris_font.fnt"
									,level.getDescription()
									,TextHAlignment::CENTER);
	_levelLabel->setPosition(232,245);
	this->addChild(_levelLabel);

	Value score(PlayerData::getInstance()->getScore());
	_scoreLabel = Label::createWithBMFont("teris_font.fnt"
									,score.getDescription()
									,TextHAlignment::CENTER);
	_scoreLabel->setPosition(232,322);
	this->addChild(_scoreLabel);

	_lines = 0;
	Value lines(_lines);
	_linesLabel = Label::createWithBMFont("teris_font.fnt"
									,lines.getDescription()
									,TextHAlignment::CENTER);
	_linesLabel->setPosition(232,165);
	this->addChild(_linesLabel);

	

	_sprite3 = Sprite::createWithSpriteFrameName("3.png");
	_sprite2 = Sprite::createWithSpriteFrameName("2.png");
	_sprite1 = Sprite::createWithSpriteFrameName("1.png");
	auto contentSize = _sprite1->getContentSize();
	_sprite3->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height+contentSize.height/2);
	_sprite2->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height+contentSize.height/2);
	_sprite1->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height+contentSize.height/2);

	this->addChild(_sprite3);
	this->addChild(_sprite2);
	this->addChild(_sprite1);

	
	_pauseLayer = PauseLayer::create();
	_pauseLayer->setVisible(false);
	this->addChild(_pauseLayer);

	setPaused(false);
	runCountdownAnimate();
	
    return true;
}
void GameRunning::runCountdownAnimate(bool isNewGame)
{
	_sprite3->setVisible(false);
	_sprite2->setVisible(false);
	_sprite1->setVisible(false);
	setPaused(false);
	
	countdownAnimate(3,isNewGame);
}
void GameRunning::resumeGame()
{
	Sleep(1);
	_sprite1->setVisible(false);
	((Blocks*)_blocks)->setVisible(true);
	if(isPaused())
		return;
	else
		runMoveDownAnimate();
}
void GameRunning::countdownAnimate(int num,bool isNewGame)
{
	this->pause();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto contentSize = _sprite3->getContentSize();
	auto countDownAction = MoveTo::create(0.8,Point(origin.x+visibleSize.width/2, origin.y+visibleSize.height*0.7));
	if(num == 3)
	{
		
		_sprite3->setVisible(true);

		//auto callback = CallFuncN::create(CC_CALLBACK_2(GameRunning::countdownAnimate,this,num-1,isNewGame));
		auto sequence = Sequence::create(countDownAction,CallFuncN::create(CC_CALLBACK_0(GameRunning::countdownAnimate,this,num-1,isNewGame)),NULL);
		_sprite3->runAction(sequence);
	}
	else if(num == 2)
	{
		Sleep(2);

		_sprite3->setVisible(false);
		_sprite2->setVisible(true);
		auto callback = CallFuncN::create(CC_CALLBACK_0(GameRunning::countdownAnimate,this,num-1,isNewGame));
		auto sequence = Sequence::create(countDownAction,callback,NULL);
		_sprite2->runAction(sequence);
	}
	else if(num == 1)
	{
		Sleep(2);

		_sprite2->setVisible(false);
		_sprite1->setVisible(true);
		if(isNewGame)
		{
			
			auto callback = CallFuncN::create(CC_CALLBACK_0(GameRunning::newGame,this));
			auto sequence = Sequence::create(countDownAction,callback,NULL);
			_sprite1->runAction(sequence);
		}
		else
		{
			auto callback = CallFuncN::create(CC_CALLBACK_0(GameRunning::resumeGame,this));
			auto sequence = Sequence::create(countDownAction,callback,NULL);
			_sprite1->runAction(sequence);
		}
	}
}

void GameRunning::menuMoveLeftCallback()
{
	((Blocks*)_blocks)->moveBlocksLeft();
}
void GameRunning::menuMoveRightCallback()
{
	((Blocks*)_blocks)->moveBlocksRight();
}
void GameRunning::menuMoveDownCallback()
{
	((Blocks*)_blocks)->moveBlocksDown();
}
void GameRunning::menuMoveFastCallback()
{
	((Blocks*)_blocks)->moveBlocksToBottom();
}
void GameRunning::menuTurnCallback()
{
	((Blocks*)_blocks)->trunBlocksRight();
}
void GameRunning::menuPauseCallback()
{
	stopMoveDownAnimate();
	setPaused(true);
	_pauseLayer->setVisible(true);
	
	//_controlMenu->setEnabled(false);
	//_playMenu->setVisible(true);
}
void GameRunning::menuPlayCallback()
{
	//_controlMenu->setEnabled(true);
	//_playMenu->setVisible(false);
}
void GameRunning::menuSysSetCallback()
{
}
void GameRunning::updateData(int lines)
{
	addLines(lines);
	Value vlines(this->getLines());
	_linesLabel->setString(vlines.getDescription());

	Value vscore(10*PlayerData::getInstance()->addScore(lines));
	_scoreLabel->setString(vscore.getDescription());
	 
	Value vlevel(PlayerData::getInstance()->upgradeLevel());
	_levelLabel->setString(vlevel.getDescription());
}
void GameRunning::newGame()
{
	Sleep(1);
	_sprite1->setVisible(false);
	
	PlayerData::getInstance()->setScore(0);
	this->setLines(0);
	this->updateData(0);

	this->setVelocityFactor(PlayerData::getInstance()->getInitLevel());

	((Blocks*)_blocks)->getReady();
	((Blocks*)_blocks)->setVisible(true);
	if(isPaused())
		return;
	else
	{
		this->runMoveDownAnimate();
	}
}
void GameRunning::gameOver()
{
	stopMoveDownAnimate();
	runGameOverAnimate();
	PlayerData::getInstance()->setTopScore();
	PlayerData::getInstance()->setTopLevel();
	
}
void GameRunning::setVelocityFactor(int level)
{
	_velocityFactor = 1.1-0.1*(float)level;
}
void GameRunning::runMoveDownAnimate()
{
	this->schedule(schedule_selector(GameRunning::moveDownAnimate)
		,BLOCK_MOVE_DOWN_TIME*getVelocityFactor());
}
void GameRunning::stopMoveDownAnimate()
{
	this->unschedule(schedule_selector(GameRunning::moveDownAnimate));
}
void GameRunning::moveDownAnimate(float)
{
	if(((Blocks*)_blocks)->canMoveBlocksDown() == false)
	{
		if(((Blocks*)_blocks)->isGameOver())
		{
			gameOver();
		}
		else
		{
			updateData(((Blocks*)_blocks)->removeFullLines());
			((Blocks*)_blocks)->getRandomBlcoks();
		}
	}
	else
	{
		((Blocks*)_blocks)->moveBlocksDown();
	}
}
void GameRunning::runGameOverAnimate()
{
	this->schedule(schedule_selector(GameRunning::gameOverAnimate),BLOCK_GAME_OVER_TIME);
}
void GameRunning::gameOverAnimate(float)
{
	if(((Blocks*)_blocks)->turnOnNextLine())
	{
		this->unschedule(schedule_selector(GameRunning::gameOverAnimate));
		Director::getInstance()->replaceScene(GameOverLayer::createScene());
	}
}