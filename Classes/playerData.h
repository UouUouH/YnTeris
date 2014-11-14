#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__


class PlayerData
{
public:
	
	static PlayerData* getInstance();
	static void releaseInstance();
	int getTopScore(){return _topScore;}
	//����score�趨��ǰ��topscore���洢
	void setTopScore();

	//�������������������µ�ǰscore�������겢��������score
	//��Ϸ����ʾ��scoreҪ�Ǵ˷�����*100
	int addScore(int lines);
	void setScore(int score){_score = score;}
	//��Ϸ����ʾ��scoreҪ�Ǵ˷�����*100
	int getScore(){return _score;}

	//���ݵ�ǰscore����Ϸ���Զ�����level������������level
	int upgradeLevel();
	int getLevel(){return _level;}
	//void setLevel(int level){_level = level;}

	//����level�趨��ǰ��topLevel���洢
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
	//��Ϸ����ʾ��scoreҪ�Ǵ���*100
	int _score;
	int _topScore;//save in local
	//��Ϸ��ǰlevel
	int _level;
	//��ʼ����Ϸʱ�����ѡ���level
	int _initLevel;//save in local
	int _topLevel;//save in local
	float _musicVoice;//save in local
	float _effectVoice;//save in local
};

#endif // __HELLOWORLD_SCENE_H__
