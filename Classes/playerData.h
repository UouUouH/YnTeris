#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__


class PlayerData
{
public:
	
	static PlayerData* getInstance();
	static void releaseInstance();
	int getTopScore(){return _topScore;}
	//根据score设定当前的topscore并存储
	void setTopScore();

	//根据消除的行数，更新当前score，更新完并返回最新score
	//游戏中显示的score要是此返回数*100
	int addScore(int lines);
	void setScore(int score){_score = score;}
	//游戏中显示的score要是此返回数*100
	int getScore(){return _score;}

	//根据当前score，游戏中自动升级level，并返回最新level
	int upgradeLevel();
	int getLevel(){return _level;}
	//void setLevel(int level){_level = level;}

	//根据level设定当前的topLevel并存储
	void setTopLevel();
	int getTopLevel(){return _topLevel;}
	
	void setInitLevel(int initLevel);
	int getInitLevel(){return _initLevel;}
	void setMusicVoice(float musicVoice);
	float getMusicVoice(){return _musicVoice;}

	void setEffectVoice(float effectVoice);
	float getEffectVoice(){return _effectVoice;}
private:
	void init();
	//游戏中显示的score要是此数*100
	int _score;
	int _topScore;//save in local
	//游戏当前level
	int _level;
	//开始玩游戏时，玩家选择的level
	int _initLevel;//save in local
	int _topLevel;//save in local
	float _musicVoice;//save in local
	float _effectVoice;//save in local
};

#endif // __HELLOWORLD_SCENE_H__
