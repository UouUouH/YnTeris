#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "cocos2d.h"

class BlockSprite : public cocos2d::Sprite
{
private:
 
   //bool init( int id, unsigned int imgId, bool isOn = false);  
public:
   //每一个block 都有两种状态，即显示状态以及当背景状态（不显示）。
	//id 从0开始编号
   static BlockSprite* create(int id, unsigned int imgId, bool isOn = false);

   
   void turnOnBlock();
   void turnOffBlock();
   bool isBlockTurnOn();

};
class PreBlocks :public cocos2d::Node
{
private:
	cocos2d::Map<int, cocos2d::Sprite*> _preBlockMap;
	
public:
	virtual bool init();
	CREATE_FUNC(PreBlocks);
	void updatePosition(cocos2d::Point* points);
};


//			
//			17*7	...		17*7+6
//			.		...		.
//			.		...		.
//			.		...		.
//			.		...		.
//			2*7		...		2*7+6	
//			1*7		...		1*7+6
//			0*7		...		0*7+6
class BlockMap :public cocos2d::Node
{
private:
	cocos2d::Map<int, BlockSprite*> _blockMap;
	

public:
	
	virtual bool init();
	CREATE_FUNC(BlockMap);
	void turnOnBlock(unsigned int id);
	void turnOffBlock(unsigned int id);
	bool isBlockTurnOn(unsigned int id);
	bool canMoveBlockLeft(unsigned int id);
	bool canMoveBlockRight(unsigned int id);
	bool canMoveBlockDown(unsigned int id);
	
	void turnOffAll();
	void turnOnAll();
	//line: 0 BLOCK_Y_NUM-1
	void turnOnLine(unsigned int line);
	void turnOffLine(unsigned int line);
	bool isLineOn(unsigned int line);
	void removeLine(unsigned int line);
	int isSomeLineOn();//返回检测到的第一个全亮的行号，如果没有折返回-1；
};

class Blocks :public cocos2d::Node
{
private:
	//int _preBlocks[4][4];
	cocos2d::Point _blocksInMap[4];//preblock 在blockmap中的position，左下为原点
	int _blocksShape;
	int _preBlocksShape;
	enum  { O_SHAPE_1 = 0, 
			NL_SHAPE_1, NL_SHAPE_2,NL_SHAPE_3,NL_SHAPE_4,
			L_SHAPE_1, L_SHAPE_2, L_SHAPE_3, L_SHAPE_4,
			Z_SHAPE_1, Z_SHAPE_2,
			NZ_SHAPE_1, NZ_SHAPE_2,
			T_SHAPE_1, T_SHAPE_2, T_SHAPE_3, T_SHAPE_4,
			I_SHAPE_1, I_SHAPE_2};
	int _flagId;
public:
	void getReady();//开始游戏前需要调用此函数
	void moveBlocksLeft();
	void moveBlocksRight();
	void moveBlocksDown();
	void moveBlocksToBottom();
	void trunBlocksRight();//顺时针旋转90度
	
	void getRandomBlcoks();
	int getPreBlocksShape(){return _preBlocksShape;}
	bool canMoveBlocksDown();
	bool isGameOver();//
	bool turnOnNextLine();//如果所有行都已经turnon了，就返回true否则返回false
	int removeFullLines();//每一个新的俄罗斯方块move到底以后检测当前是否有可以消除的行，如果有消除，返回消除了的行数，考虑在这里加计分环节。
	void getBlcoks(cocos2d::Point* preBlocksInMap,int shape, int offsetX, int offsetY);
	virtual bool init();
	CREATE_FUNC(Blocks);
private:
	void getRandomPreBlcoks();
	void moveDownAnimate(float);
	void updatePreBlocks(cocos2d::Point* preBlocksInMap);
	PreBlocks* _preBlocks;
	BlockMap* _blockMap;
	
	bool canMoveBlocksHere(cocos2d::Point* preBlocksInMap);//可不可以将方块移动到当前的位置，在canTurnBlocksRight中被调用。
	bool canMoveBlocksLeft();
	bool canMoveBlocksRight();
	
	bool canTurnBlocksRight();
	
	bool isInBlocks(int x, int y);//用来判断下一个move到的地方point在不在当前blocks占据的区域内。
	bool isOutofBlockMap(int x, int y);//用来判断point在不在当前blockmap区域内。
	bool isOutofBlockMap(cocos2d::Point point);//用来判断point在不在当前blockmap区域内。
	void moveBlocksInMap(int offsetX, int offsetY);
	void turnOnBlocksInMap();
	void turnoffBlocksInMap();
};
#endif // __HELLOWORLD_SCENE_H__
