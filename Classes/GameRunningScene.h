#ifndef __GAMERUNNING_SCENE_H__
#define __GAMERUNNING_SCENE_H__

#include "cocos2d.h"

class GameRunning : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
   
	void runCountdownAnimate(bool isNewGame = true);
    // implement the "static create()" method manually
    CREATE_FUNC(GameRunning);
	
private:
	//更新游戏数据，score， level，lines
	void updateData(int lines);//
	void setLines(int lines){_lines = lines;}
	void addLines(int lines){_lines += lines;}
	int getLines(){return _lines;}
	void countdownAnimate(int num,bool isNewGame);//

	
	void resumeGame();
	 void menuMoveLeftCallback();
	void menuMoveRightCallback();
	void menuMoveDownCallback();
	void menuMoveFastCallback();
	void menuTurnCallback();
	void menuPauseCallback();
	void menuSysSetCallback();
	void menuPlayCallback();
	void runMoveDownAnimate();
	void stopMoveDownAnimate();
	void gameOver();
	void newGame();
	void runGameOverAnimate();
	cocos2d::Menu* _controlMenu;
	cocos2d::Layer* _pauseLayer;
	cocos2d::Node* _blocks;
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _levelLabel;
	cocos2d::Label* _linesLabel;
	void gameOverAnimate(float);
	void moveDownAnimate(float);
	void setVelocityFactor(int level);
	float getVelocityFactor(){return _velocityFactor;}
	float _velocityFactor;//向下移动的速度系数由level决定level越大_velocityFactor越小，速度 = _velocityFactor*BLOCK_MOVE_DOWN_TIME
	void setPaused(bool paused){_isPaused = paused;}
	bool isPaused(){return _isPaused;}
	int _lines;
	cocos2d::Sprite* _sprite3;// number 3 for count down
	cocos2d::Sprite* _sprite2;// number 2 for count down
	cocos2d::Sprite* _sprite1;// number 1 for count down
	bool _isPaused;
};

#endif // __HELLOWORLD_SCENE_H__
