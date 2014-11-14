#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "cocos2d.h"

class BlockSprite : public cocos2d::Sprite
{
private:
 
   //bool init( int id, unsigned int imgId, bool isOn = false);  
public:
   //ÿһ��block ��������״̬������ʾ״̬�Լ�������״̬������ʾ����
	//id ��0��ʼ���
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
	int isSomeLineOn();//���ؼ�⵽�ĵ�һ��ȫ�����кţ����û���۷���-1��
};

class Blocks :public cocos2d::Node
{
private:
	//int _preBlocks[4][4];
	cocos2d::Point _blocksInMap[4];//preblock ��blockmap�е�position������Ϊԭ��
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
	void getReady();//��ʼ��Ϸǰ��Ҫ���ô˺���
	void moveBlocksLeft();
	void moveBlocksRight();
	void moveBlocksDown();
	void moveBlocksToBottom();
	void trunBlocksRight();//˳ʱ����ת90��
	
	void getRandomBlcoks();
	int getPreBlocksShape(){return _preBlocksShape;}
	bool canMoveBlocksDown();
	bool isGameOver();//
	bool turnOnNextLine();//��������ж��Ѿ�turnon�ˣ��ͷ���true���򷵻�false
	int removeFullLines();//ÿһ���µĶ���˹����move�����Ժ��⵱ǰ�Ƿ��п����������У���������������������˵�����������������ӼƷֻ��ڡ�
	void getBlcoks(cocos2d::Point* preBlocksInMap,int shape, int offsetX, int offsetY);
	virtual bool init();
	CREATE_FUNC(Blocks);
private:
	void getRandomPreBlcoks();
	void moveDownAnimate(float);
	void updatePreBlocks(cocos2d::Point* preBlocksInMap);
	PreBlocks* _preBlocks;
	BlockMap* _blockMap;
	
	bool canMoveBlocksHere(cocos2d::Point* preBlocksInMap);//�ɲ����Խ������ƶ�����ǰ��λ�ã���canTurnBlocksRight�б����á�
	bool canMoveBlocksLeft();
	bool canMoveBlocksRight();
	
	bool canTurnBlocksRight();
	
	bool isInBlocks(int x, int y);//�����ж���һ��move���ĵط�point�ڲ��ڵ�ǰblocksռ�ݵ������ڡ�
	bool isOutofBlockMap(int x, int y);//�����ж�point�ڲ��ڵ�ǰblockmap�����ڡ�
	bool isOutofBlockMap(cocos2d::Point point);//�����ж�point�ڲ��ڵ�ǰblockmap�����ڡ�
	void moveBlocksInMap(int offsetX, int offsetY);
	void turnOnBlocksInMap();
	void turnoffBlocksInMap();
};
#endif // __HELLOWORLD_SCENE_H__
