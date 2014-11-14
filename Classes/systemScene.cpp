//#include "cocos-ext.h"

#include "systemScene.h"
#include "playerData.h"
USING_NS_CC;
//USING_NS_CC_EXT;
LevelCheckBox* LevelCheckBox::create(const std::string& backGround,
                           const std::string& backGroundSeleted,
                           const std::string& cross,
                           const std::string& backGroundDisabled,
                           const std::string& frontCrossDisabled,
                           TextureResType texType)
{
    LevelCheckBox *pWidget = new LevelCheckBox;
    if (pWidget && pWidget->init(backGround,
                                 backGroundSeleted,
                                 cross,
                                 backGroundDisabled,
                                 frontCrossDisabled,
                                 texType))
    {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}

void LevelCheckBox::setTouchEnabled(bool enable)
{
	if(enable)
		cocos2d::ui::CheckBox::onPressStateChangedToNormal();
	else
		cocos2d::ui::CheckBox::onPressStateChangedToDisabled();

	cocos2d::ui::CheckBox::setTouchEnabled(enable);
}
//------------------------level check boxes----------------------
bool LevelCheckBoxes::init()
{
	auto checkbox1 = LevelCheckBox::create("level1.png","level1.png","level1.png","level1.png","level1.png",ui::Widget::TextureResType::PLIST);
	checkbox1->setTouchEnabled(true);
	checkbox1->setPosition(Vec2(40+33/2,366));
	this->_checkBoxMap.insert(1,checkbox1);
	checkbox1->addEventListener(CC_CALLBACK_2(LevelCheckBoxes::selectedEvent, this));
	this->addChild(checkbox1);
	checkbox1->setTag(1);
	int n = PlayerData::getInstance()->getInitLevel();
	int tn = PlayerData::getInstance()->getTopLevel();
	for(int i = 2; i <= 10; i++)
	{
		//Value v(i);
		char str[20],nstr[20];
		sprintf(str,"level%d.png",i);
		sprintf(nstr,"nlevel%d.png",i);
		//str.createWithFormat("level%d.png",i);
		//nstr.createWithFormat("nlevel%d.png",i);
		LevelCheckBox* checkbox = LevelCheckBox::create(str,str,str,nstr,nstr,ui::Widget::TextureResType::PLIST);
		if(i <= tn)
			checkbox->setTouchEnabled(true);
		else
			checkbox->setTouchEnabled(false);

	//	checkbox->setEnabled(false);
		if(i <= 5)
			checkbox->setPosition(Vec2(40+(i-1)*(33+10)+33/2,366));
		else
			checkbox->setPosition(Vec2(40+(i-6)*(33+10)+33/2,313));
		this->_checkBoxMap.insert(i,checkbox);
		checkbox->addEventListener(CC_CALLBACK_2(LevelCheckBoxes::selectedEvent, this));
		this->addChild(checkbox);
		checkbox->setTag(i);

	}
	_decorationSelected = Sprite::createWithSpriteFrameName("butterfly.png");
	this->addChild(_decorationSelected);
	this->_checkBoxMap.at(n)->setSelectedState(true);
	updateDecorationPosition(n);
	setLastSelectdItemID(n);
	return true;
}
void LevelCheckBoxes::setDecorationPosition(float x, float y)
{
	_decorationSelected->setPosition(x,y);
}
void LevelCheckBoxes::updateDecorationPosition(int selectedItemID)
{

	if(selectedItemID <= 5)
			setDecorationPosition(40+(selectedItemID-1)*(33+10)+33/2,366+18);
		else
			setDecorationPosition(40+(selectedItemID-6)*(33+10)+33/2,313+15);
}
void LevelCheckBoxes::selectedEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
	int n = ((cocos2d::ui::CheckBox*)pSender)->getTag();
	switch (type)
	{
		case ui::CheckBox::EventType::SELECTED:
			setSelectedItemID(n);
            break;
		default:
			break;
	}
}

void LevelCheckBoxes::setSelectedItemID(int id)
{
	if(getLastSelectedItemID() != id)
	{
		updateDecorationPosition(id);
		_checkBoxMap.at(getLastSelectedItemID())->setSelectedState(false);
		setLastSelectdItemID(id);
	}
}
//-----------------------------------system set layer--------------------------
cocos2d::Scene* SystemSetLayer::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = SystemSetLayer::create();
	scene->addChild(layer);

	return scene;
}
// on "init" you need to initialize your instance
bool SystemSetLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	setEffectVoiceRate(PlayerData::getInstance()->getEffectVoice());
	setMusicVoiceRate(PlayerData::getInstance()->getMusicVoice());
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spriteBg = Sprite::createWithSpriteFrameName("systemSet.png");
	spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(spriteBg);

	_levelCheckboxes = LevelCheckBoxes::create();
	this->addChild(_levelCheckboxes);
	
	auto effectVoice = ui::Slider::create();
	effectVoice->loadBarTexture("slider_l.png",ui::Widget::TextureResType::PLIST);
	effectVoice->loadSlidBallTextures("slider_ss.png","slider_ss.png","",ui::Widget::TextureResType::PLIST);
	effectVoice->setPosition(Vec2(40+212/2,120));
	effectVoice->addEventListener(CC_CALLBACK_2(SystemSetLayer::effectVoiceChange,this));
	this->addChild(effectVoice);
	effectVoice->setPercent(getEffectVoiceRate()*100);

	auto musicVoice = ui::Slider::create();
	musicVoice->loadBarTexture("slider_l.png",ui::Widget::TextureResType::PLIST);
	musicVoice->loadSlidBallTextures("slider_ss.png","slider_ss.png","",ui::Widget::TextureResType::PLIST);
	musicVoice->setPosition(Vec2(40+212/2,210));
	musicVoice->addEventListener(CC_CALLBACK_2(SystemSetLayer::musicVoiceChange,this));
	this->addChild(musicVoice);
	musicVoice->setPercent(getMusicVoiceRate()*100);

	auto saveNormal = Sprite::createWithSpriteFrameName("save.png");
	auto saveItem = MenuItemSprite::create(saveNormal,saveNormal,CC_CALLBACK_0(SystemSetLayer::menuSaveCallback,this));
	saveItem->setPosition(saveNormal->getContentSize().width*0.7 + origin.x, origin.y+saveNormal->getContentSize().height*0.85);

	auto cancelNormal = Sprite::createWithSpriteFrameName("cancel.png");
	auto continueItem = MenuItemSprite::create(cancelNormal,cancelNormal,CC_CALLBACK_0(SystemSetLayer::menuCancelCallback,this));
	continueItem->setPosition(visibleSize.width+ origin.x - cancelNormal->getContentSize().width*0.8 , origin.y+cancelNormal->getContentSize().height*0.85);

	auto menu = Menu::create(saveItem, continueItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//_levelCheckboxes->setSelectedItemID(PlayerData::getInstance()->getLevel());

    return true;
}
void SystemSetLayer::effectVoiceChange(Ref* pSender,cocos2d::ui::Slider::EventType type)
{
	switch (type)
	{
	case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		setEffectVoiceRate(((ui::Slider*)pSender)->getPercent()/100.0);
		break;
	default:
		break;
	}
}
void SystemSetLayer::musicVoiceChange(Ref* pSender,cocos2d::ui::Slider::EventType type)
{
	switch (type)
	{
	case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		setMusicVoiceRate(((ui::Slider*)pSender)->getPercent()/100.0);
		break;
	default:
		break;
	}
}
void SystemSetLayer::menuCancelCallback()
{
	Director::getInstance()->popScene();
}
int SystemSetLayer::getSelectedLevel()
{
	return _levelCheckboxes->getSelectedItemID();
}
void SystemSetLayer::menuSaveCallback()
{
	PlayerData::getInstance()->setEffectVoice(this->getEffectVoiceRate());
	PlayerData::getInstance()->setMusicVoice(this->getMusicVoiceRate());
	PlayerData::getInstance()->setInitLevel(this->getSelectedLevel());
	Director::getInstance()->popScene();

	//Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(0.5f,GameRunning::createScene()));
	//Director::getInstance()->replaceScene(GameRunning::createScene());
}

