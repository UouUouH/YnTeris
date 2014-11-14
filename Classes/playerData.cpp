#include "playerData.h"
#include "cocos2d.h"

USING_NS_CC;

static PlayerData* playerDataInstance = NULL;
//如果调用了这个函数，应该在程序退出之前调用releaseInstance
PlayerData* PlayerData::getInstance()
{
	if(playerDataInstance == NULL)
	{
		playerDataInstance = new PlayerData();
		if(playerDataInstance)
			playerDataInstance->init();
		else
			return NULL;
	}
	return playerDataInstance;
}
void PlayerData::releaseInstance()
{
	if(playerDataInstance)
	{
		playerDataInstance->setTopLevel();
		playerDataInstance->setTopScore();
		delete playerDataInstance;
		playerDataInstance = NULL;
	}
}
void PlayerData::init()
{
	_score = 0;
	_level = 1;
	if(UserDefault::getInstance()->getBoolForKey("isPlayerDataExist"))
	{
		_topScore = UserDefault::getInstance()->getIntegerForKey("topScore");
		_topLevel = UserDefault::getInstance()->getIntegerForKey("topLevel");
		this->setMusicVoice(UserDefault::getInstance()->getFloatForKey("effectVoice"));
		this->setEffectVoice(UserDefault::getInstance()->getFloatForKey("effectVoice"));
		this->setInitLevel(UserDefault::getInstance()->getIntegerForKey("initLevel"));
	}
	else
	{
		_topScore = 0;
		_topLevel = 1;
		_initLevel = 1;
		_musicVoice = 0.5;
		_effectVoice = 0.5;
		UserDefault::getInstance()->setBoolForKey("isPlayerDataExist",true);
		UserDefault::getInstance()->setIntegerForKey("topScore",_topScore);
		UserDefault::getInstance()->setIntegerForKey("topLevel",_topLevel);
		UserDefault::getInstance()->setIntegerForKey("initLevel",_initLevel);
		UserDefault::getInstance()->setFloatForKey("musicVoice",_musicVoice);
		UserDefault::getInstance()->setFloatForKey("effectVoice",_effectVoice);
		UserDefault::getInstance()->flush();
	}
}

void PlayerData::setTopScore()
{
	if(_score > _topScore)
	{
		_topScore = _score;
		UserDefault::getInstance()->setIntegerForKey("topScore",_topScore);
		UserDefault::getInstance()->flush();
	}
}
//游戏中方块最大高度为4，所以可以消除的最大行数也为4
int PlayerData::addScore(int lines)
{
	if(lines == 1)
		_score++;
	else if(lines == 2)
		_score += 3;
	else if(lines == 3)
		_score += 5;
	else if(lines == 4)
		_score += 8;
	return _score;
}

int PlayerData::upgradeLevel()
{
	int n = _score/100;
	_level = n + _initLevel;
	if(_level > 10)
		_level = 10;
	return _level;
}
void PlayerData::setTopLevel()
{
	if(_level > _topLevel)
	{
		_topLevel = _level;
		UserDefault::getInstance()->setIntegerForKey("topLevel",_topLevel);
		UserDefault::getInstance()->flush();
	}
}
void PlayerData::setInitLevel(int initLevel)
{
	_initLevel = initLevel;
	_level = initLevel;
	UserDefault::getInstance()->setIntegerForKey("initLevel",_initLevel);
	UserDefault::getInstance()->flush();
}
void PlayerData::setMusicVoice(float musicVoice)
{
	_musicVoice = musicVoice;
	UserDefault::getInstance()->setFloatForKey("musicVoice",_musicVoice);
	UserDefault::getInstance()->flush();
}
void PlayerData::setEffectVoice(float effectVoice)
{
	_effectVoice = effectVoice;
	UserDefault::getInstance()->setFloatForKey("effectVoice",_musicVoice);
	UserDefault::getInstance()->flush();
}