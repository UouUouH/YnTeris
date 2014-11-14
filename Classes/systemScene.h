#ifndef __SYSTEM_LAYER_H__
#define __SYSTEM_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class LevelCheckBox : public cocos2d::ui::CheckBox
{
public:
	 static LevelCheckBox* create(const std::string& backGround,
                            const std::string& backGroundSeleted,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);
	
	virtual void setTouchEnabled(bool enable) override;
	void enableTouch();
	void disableTouch();
private:
	
};
class LevelCheckBoxes : public cocos2d::Node
{
private:
	int _lastSelectedItemID;//1---10
	//选中时，在控件上边加额外的装饰品
	cocos2d::Sprite* _decorationSelected;
	void setDecorationPosition(float x, float y);
	virtual bool init();
	cocos2d::Map<int, cocos2d::ui::CheckBox*> _checkBoxMap;
	void setLastSelectdItemID(int n){_lastSelectedItemID = n;}
	int getLastSelectedItemID(){return _lastSelectedItemID;}
	void updateDecorationPosition(int selectedItemID);
public:
	void selectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	int getSelectedItemID(){return _lastSelectedItemID;}//这个没有错，last是相当于更改的那一瞬间，更改完成后其实就是相当于现在的了
	void setSelectedItemID(int id);
	CREATE_FUNC(LevelCheckBoxes);
};
class SystemSetLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
	void menuCancelCallback();
	void menuSaveCallback();
    CREATE_FUNC(SystemSetLayer);
	void effectVoiceChange(Ref* pSender,cocos2d::ui::Slider::EventType type);
	void musicVoiceChange(Ref* pSender,cocos2d::ui::Slider::EventType type);//background music
	//effectVoiceRate 0-1
	void setEffectVoiceRate(float effectVoiceRate){_effectVoiceRate = effectVoiceRate;}
	float getEffectVoiceRate(){return _effectVoiceRate;}
	//effectVoiceRate 0-1
	void setMusicVoiceRate(float musicVoiceRate){_musicVoiceRate = musicVoiceRate;}
	float getMusicVoiceRate(){return _musicVoiceRate;}

	int getSelectedLevel();
private:
	LevelCheckBoxes* _levelCheckboxes;
	float _effectVoiceRate;//0.01-1
	float _musicVoiceRate;//0.01-1
};

#endif // __SYSTEM_LAYER_H__
