#include "Blocks.h"
#include "Define.h"

USING_NS_CC;



BlockSprite* BlockSprite::create(int id, unsigned int imgId, bool isOn)
{
	 BlockSprite *sprite = new (std::nothrow) BlockSprite();
	 if(imgId < BLOCK_IMG_NUM)
	{
		auto imageName = __String::createWithFormat("block%d.png",imgId);
		if(sprite && sprite->initWithSpriteFrameName(imageName->getCString()))
		{
			sprite->autorelease();
			if(isOn)
				sprite->turnOnBlock();
			else
				sprite->turnOffBlock();

			sprite->setTag(id);
			sprite->setPosition(BLOCK_X+(id%BLOCK_X_NUM)*BLOCK_WIDTH+BLOCK_WIDTH/2, BLOCK_Y+(id/BLOCK_X_NUM)*BLOCK_HEIGHT+BLOCK_HEIGHT/2+3);
			return sprite;
		}
	}
	else
	{
		if(sprite && sprite->initWithSpriteFrameName("block1.png"))
		{
			sprite->autorelease();
			sprite->turnOffBlock();
			sprite->setTag(id);
			sprite->setPosition(BLOCK_X+(id%BLOCK_X_NUM)*BLOCK_WIDTH+BLOCK_WIDTH/2, BLOCK_Y+(id/BLOCK_X_NUM)*BLOCK_HEIGHT+BLOCK_HEIGHT/2+3);
			if(isOn)
				sprite->turnOnBlock();
			else
				sprite->turnOffBlock();
			return sprite;
		}
	}
   
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BlockSprite::turnOffBlock()
{
	this->setVisible(false);
}

void BlockSprite::turnOnBlock()
{
	this->setVisible(true);

}
bool BlockSprite::isBlockTurnOn()
{
	return this->isVisible();
	
}
//---------------------------pre block map-----------
bool PreBlocks::init()
{
	

	for(int i = 0; i < 4; i++)
	{
		this->_preBlockMap.insert(i, Sprite::createWithSpriteFrameName("preBlock.png"));
		this->addChild(this->_preBlockMap.at(i));
		//这里最好给一个初始位置然后 turn on
	}
	return true;
}
void PreBlocks::updatePosition(cocos2d::Point* points)
{
	for(int i = 0; i < 4; i++)
	{
		this->_preBlockMap.at(i)->setPosition(PRE_BLOCK_X+(points[i].x-BLOCKS_X_POSITION)*PRE_BLOCK_WIDTH+0.5*PRE_BLOCK_WIDTH,PRE_BLOCK_Y+(points[i].y-BLOCKS_Y_POSITION)*PRE_BLOCK_HEIGHT+0.5*PRE_BLOCK_HEIGHT );
	}
}

//-----------------------block map------------------
bool BlockMap::init()
{
	for(int i = 0; i < BLOCK_X_NUM*BLOCK_Y_NUM; i++)
	{
		this->_blockMap.insert(i, BlockSprite::create(i, 1, false));
		this->addChild(this->_blockMap.at(i));
	}
	
	return true;
}
void BlockMap::turnOnBlock(unsigned int id)
{
	_blockMap.at(id)->turnOnBlock();
}
void BlockMap::turnOffBlock(unsigned int id)
{
	_blockMap.at(id)->turnOffBlock();
}
bool BlockMap::isBlockTurnOn(unsigned int id)
{
	return _blockMap.at(id)->isBlockTurnOn();
}
void BlockMap::turnOnAll()
{
	for(int i = 0; i < BLOCK_X_NUM*BLOCK_Y_NUM; i++)
	{
		_blockMap.at(i)->turnOnBlock();
	}
}
void BlockMap::turnOffAll()
{
	for(int i = 0; i < BLOCK_X_NUM*BLOCK_Y_NUM; i++)
	{
		_blockMap.at(i)->turnOffBlock();
	}
}
void BlockMap::turnOnLine(unsigned int line)
{
	if(line < BLOCK_Y_NUM)
	{
		for(int i = line*BLOCK_X_NUM; i < (line*BLOCK_X_NUM+BLOCK_X_NUM); i++)
		{
			_blockMap.at(i)->turnOnBlock();
		}
	}
}
void BlockMap::turnOffLine(unsigned int line)
{
	if(line < BLOCK_Y_NUM)
	{
		for(int i = line*BLOCK_X_NUM; i < (line*BLOCK_X_NUM+BLOCK_X_NUM); i++)
		{
			_blockMap.at(i)->turnOffBlock();
		}
	}
}


bool BlockMap::canMoveBlockDown(unsigned int id)
{
	int n = id%BLOCK_X_NUM;
	int line = id/BLOCK_X_NUM;
	
	int k = (line-1)*BLOCK_X_NUM+n;
	if(k < 0)
		return false;

	if(_blockMap.at(k)->isBlockTurnOn())
		return false;

	return true;
}
//有问题，需要修改
bool BlockMap::canMoveBlockRight(unsigned int id)
{
	int n = id%BLOCK_X_NUM;
	if((n+1) >= BLOCK_X_NUM)
		return false;
	int k = id + 1;
	if(_blockMap.at(k)->isVisible())
		return false;
	return true;
}
bool BlockMap::canMoveBlockLeft(unsigned int id)
{
	int n = id%BLOCK_X_NUM;
	if((n-1) < 0)
		return false;
	int k = id - 1;
	if(_blockMap.at(k)->isVisible())
		return false;
	return true;
}
bool BlockMap::isLineOn(unsigned int line)
{
	for(int i = 0; i < BLOCK_X_NUM; i++)
	{
		if(!isBlockTurnOn(line*BLOCK_X_NUM+i))
			return false;
	}
	return true;
}
void BlockMap::removeLine(unsigned int line)
{
	for(int i = line; i < (BLOCK_Y_NUM-1); i++)
	{
		for(int j = 0; j < BLOCK_X_NUM; j++)
		{
			if(isBlockTurnOn((i+1)*BLOCK_X_NUM+j))
				turnOnBlock(i*BLOCK_X_NUM+j);
			else
				turnOffBlock(i*BLOCK_X_NUM+j);
		}
	}
	for(int j = 0; j < BLOCK_X_NUM; j++)
	{
		turnOffBlock((BLOCK_Y_NUM-1)*BLOCK_X_NUM+j);
	}
	return ;
}
int BlockMap::isSomeLineOn()
{
	for(int i = 0; i < BLOCK_Y_NUM; i++)
	{
		if(isLineOn(i))
			return i;
	}
	return -1;
}
//------------blocks------------
bool Blocks::init()
{
	/*if(!Layer::init())
	{
		return false;
	}*/
	this->_preBlocks = PreBlocks::create();

	this->addChild(this->_preBlocks);

	this->_blockMap = BlockMap::create();
	this->addChild(this->_blockMap);
	
	//this->_blockMap->turnOnAll();
	_flagId = 0;
	return true;
}
void Blocks::getReady()
{
	getRandomPreBlcoks();
	turnoffBlocksInMap();
	getRandomBlcoks();
}
void Blocks::getRandomPreBlcoks()
{
	_preBlocksShape = rand()%BLOCKS_SHAPES;
	cocos2d::Point preBlocksInMap[4];
	getBlcoks(preBlocksInMap,_preBlocksShape,BLOCKS_X_POSITION,BLOCKS_Y_POSITION);
	updatePreBlocks(preBlocksInMap);
}
void Blocks::getRandomBlcoks()
{
	_blocksShape = _preBlocksShape;
	getBlcoks(_blocksInMap,_blocksShape,BLOCKS_X_POSITION,BLOCKS_Y_POSITION);
	getRandomPreBlcoks();
}
void Blocks::getBlcoks(cocos2d::Point* preBlocksInMap,int shape, int offsetX, int offsetY)
{
	switch (shape)
	{
	case O_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case L_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,2+offsetY);
			break;
		}
	case L_SHAPE_2:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(-1+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case L_SHAPE_3:
		{
			preBlocksInMap[0] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,2+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,2+offsetY);
			break;
		}
	case L_SHAPE_4:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case NL_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,2+offsetY);
			break;
		}
	case NL_SHAPE_2:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[3] = Point(-1+offsetX,1+offsetY);
			break;
		}
	case NL_SHAPE_3:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,2+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,2+offsetY);
			break;
		}
	case NL_SHAPE_4:
		{
			preBlocksInMap[0] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(-1+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case Z_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(-1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,1+offsetY);
			break;
		}
	case Z_SHAPE_2:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,2+offsetY);
			break;
		}
	case NZ_SHAPE_1:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case NZ_SHAPE_2:
		{
			preBlocksInMap[0] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,2+offsetY);
			break;
		}
	case T_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(-1+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,1+offsetY);
			break;
		}
	case T_SHAPE_2:
		{
			preBlocksInMap[0] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(1+offsetX,2+offsetY);
			break;
		}
	case T_SHAPE_3:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,1+offsetY);
			break;
		}
	case T_SHAPE_4:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,1+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,2+offsetY);
			break;
		}
	case I_SHAPE_1:
		{
			preBlocksInMap[0] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,1+offsetY);
			preBlocksInMap[2] = Point(0+offsetX,2+offsetY);
			preBlocksInMap[3] = Point(0+offsetX,3+offsetY);
			break;
		}
	case I_SHAPE_2:
		{
			preBlocksInMap[0] = Point(-1+offsetX,0+offsetY);
			preBlocksInMap[1] = Point(0+offsetX,0+offsetY);
			preBlocksInMap[2] = Point(1+offsetX,0+offsetY);
			preBlocksInMap[3] = Point(2+offsetX,0+offsetY);
			break;
		}
	default:
		break;
	}
	turnOnBlocksInMap();
	
}
void Blocks::moveBlocksInMap(int offsetX, int offsetY)
{
	turnoffBlocksInMap();
	for(int i = 0; i < 4; i++)
	{
		_blocksInMap[i].x += offsetX;
		_blocksInMap[i].y += offsetY;
		if(isOutofBlockMap(_blocksInMap[i]) == false)
			_blockMap->turnOnBlock(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
	}
}
void Blocks::turnOnBlocksInMap()
{
	for(int i = 0; i < 4; i++)
	{
		if(isOutofBlockMap(_blocksInMap[i]) == false)
			_blockMap->turnOnBlock(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
	}
}
void Blocks::turnoffBlocksInMap()
{
	for(int i = 0; i < 4; i++)
	{
		if(isOutofBlockMap(_blocksInMap[i]) == false)
			_blockMap->turnOffBlock(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
	}
}
void Blocks::updatePreBlocks(cocos2d::Point* preBlocksInMap)
{
	this->_preBlocks->updatePosition(preBlocksInMap);
}
bool Blocks::isInBlocks(int x, int y)
{
	cocos2d::Point p = cocos2d::Point(x,y);

	int i = 0;
	while(p != _blocksInMap[i])
	{
		i++;
		if(i == 4)
			return false;
	}
	return true;
}
bool Blocks::isOutofBlockMap(int x, int y)
{
	
	if(x < 0)
		return true;
	if(y < 0)
		return true;
	if(x >= BLOCK_X_NUM)
		return true;
	if(y >= BLOCK_Y_NUM)
		return true;
	return false;
}
bool Blocks::isOutofBlockMap(cocos2d::Point point)
{
	
	if(point.x < 0)
		return true;
	if(point.y < 0)
		return true;
	if(point.x >= BLOCK_X_NUM)
		return true;
	if(point.y >= BLOCK_Y_NUM)
		return true;
	return false;
}
bool Blocks::canMoveBlocksLeft()
{
	bool b[4];
	bool s = true;
	for(int i = 0; i < 4; i++)
	{
		if(_blocksInMap[i].y >= BLOCK_Y_NUM)
			b[i] = true;
		else if(isInBlocks(_blocksInMap[i].x-1, _blocksInMap[i].y))
			b[i] = true;
		else
			b[i] = _blockMap->canMoveBlockLeft(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
		s = s&&b[i];
	}
	return s;
}
bool Blocks::canMoveBlocksRight()
{
	bool b[4];
	bool s = true;
	for(int i = 0; i < 4; i++)
	{
		if(_blocksInMap[i].y >= BLOCK_Y_NUM)
			b[i] = true;
		else if(isInBlocks(_blocksInMap[i].x+1, _blocksInMap[i].y))
			b[i] = true;
		else
			b[i] = _blockMap->canMoveBlockRight(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
		s = s&&b[i];
	}
	return s;
}
bool Blocks::canMoveBlocksDown()
{
	bool b[4];
	bool s = true;
	for(int i = 0; i < 4; i++)
	{
		if(_blocksInMap[i].y >= BLOCK_Y_NUM)
			b[i] = true;
		else if(isInBlocks(_blocksInMap[i].x, _blocksInMap[i].y-1))
			b[i] = true;
		else
			b[i] = _blockMap->canMoveBlockDown(_blocksInMap[i].y*BLOCK_X_NUM+_blocksInMap[i].x);
		s = s&&b[i];
	}
	return s;
}
bool Blocks::canMoveBlocksHere(cocos2d::Point* preBlocksInMap)
{
	bool b[4];
	bool s = true;
	for(int i = 0; i < 4; i++)
	{
		if(isInBlocks(preBlocksInMap[i].x, preBlocksInMap[i].y))
			b[i] = true;
		else if(preBlocksInMap[i].y >= BLOCK_Y_NUM)
			b[i] = true;
		else if(preBlocksInMap[i].x < 0)
			b[i] = false;
		else if(preBlocksInMap[i].y < 0)
			b[i] = false;
		else if(preBlocksInMap[i].x >= BLOCK_X_NUM)
			b[i] = false;
		else
			b[i] = !_blockMap->isBlockTurnOn(preBlocksInMap[i].y*BLOCK_X_NUM+preBlocksInMap[i].x);
		s = s&&b[i];
	}
	return s;
}
bool Blocks::canTurnBlocksRight()
{
	int t = 0;
	bool b = false;
	cocos2d::Point preBlocksInMap[4];
	for(int i = 0; i < 4; i++)
	{
		preBlocksInMap[i] = _blocksInMap[i];
	}
	//square
	if(_blocksShape == O_SHAPE_1)
		return false;
	//negative L 
	if((_blocksShape >= NL_SHAPE_1)&&(_blocksShape <= NL_SHAPE_4))
	{
		if(_blocksShape == NL_SHAPE_4)
			getBlcoks(preBlocksInMap,NL_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,_blocksShape+1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}
	//L
	if((_blocksShape >= L_SHAPE_1)&&(_blocksShape <= L_SHAPE_4))
	{
		if(_blocksShape == L_SHAPE_4)
			getBlcoks(preBlocksInMap,L_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,_blocksShape+1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}
	if((_blocksShape >= Z_SHAPE_1)&&(_blocksShape <= Z_SHAPE_2))
	{
		if(_blocksShape == Z_SHAPE_2)
			getBlcoks(preBlocksInMap,Z_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,Z_SHAPE_2,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}
	if((_blocksShape >= NZ_SHAPE_1)&&(_blocksShape <= NZ_SHAPE_2))
	{
		if(_blocksShape == NZ_SHAPE_2)
			getBlcoks(preBlocksInMap,NZ_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,NZ_SHAPE_2,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}
	if((_blocksShape >= T_SHAPE_1)&&(_blocksShape <= T_SHAPE_4))
	{
		if(_blocksShape == T_SHAPE_4)
			getBlcoks(preBlocksInMap,T_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,_blocksShape+1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}
	if((_blocksShape >= I_SHAPE_1)&&(_blocksShape <= I_SHAPE_2))
	{
		if(_blocksShape == I_SHAPE_2)
			getBlcoks(preBlocksInMap,I_SHAPE_1,preBlocksInMap[0].x,preBlocksInMap[0].y);
		else
			getBlcoks(preBlocksInMap,I_SHAPE_2,preBlocksInMap[0].x,preBlocksInMap[0].y);
		
		return canMoveBlocksHere(preBlocksInMap);
	}

	return false;
}

void Blocks::moveBlocksLeft()
{
	if(canMoveBlocksLeft()&&canMoveBlocksDown())
	{
		moveBlocksInMap(-1,0);
	}
}
void Blocks::moveBlocksRight()
{
	if(canMoveBlocksRight()&&canMoveBlocksDown())
	{
		moveBlocksInMap(1,0);
	}
}
void Blocks::moveBlocksDown()
{
	if(canMoveBlocksDown())
	{
		moveBlocksInMap(0,-1);
	}
}
void Blocks::trunBlocksRight()
{
	if(canMoveBlocksDown() == false)
		return;
	if(canTurnBlocksRight() == false)
		return;
	//square
	if(_blocksShape == O_SHAPE_1)
		return ;
	//negative L 
	if((_blocksShape >= NL_SHAPE_1)&&(_blocksShape <= NL_SHAPE_4))
	{
		if(_blocksShape == NL_SHAPE_4)
			_blocksShape = NL_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();

		return ;
	}
	//L
	if((_blocksShape >= L_SHAPE_1)&&(_blocksShape <= L_SHAPE_4))
	{
		if(_blocksShape == L_SHAPE_4)
			_blocksShape = L_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();
		return ;
	}
	if((_blocksShape >= Z_SHAPE_1)&&(_blocksShape <= Z_SHAPE_2))
	{
		if(_blocksShape == Z_SHAPE_2)
			_blocksShape = Z_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();
		return ;
	}
	if((_blocksShape >= NZ_SHAPE_1)&&(_blocksShape <= NZ_SHAPE_2))
	{
		if(_blocksShape == NZ_SHAPE_2)
			_blocksShape = NZ_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();
		return ;
	}
	if((_blocksShape >= T_SHAPE_1)&&(_blocksShape <= T_SHAPE_4))
	{
		if(_blocksShape == T_SHAPE_4)
			_blocksShape = T_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();
		return ;
	}
	if((_blocksShape >= I_SHAPE_1)&&(_blocksShape <= I_SHAPE_2))
	{
		if(_blocksShape == I_SHAPE_2)
			_blocksShape = I_SHAPE_1;
		else
			_blocksShape++;
			turnoffBlocksInMap();
			getBlcoks(_blocksInMap,_blocksShape,_blocksInMap[0].x,_blocksInMap[0].y);
			turnOnBlocksInMap();
		return ;
	}

	return ;
}
void Blocks::moveBlocksToBottom()
{
	while(canMoveBlocksDown())
	{
		moveBlocksInMap(0,-1);
	}
}
bool Blocks::isGameOver()
{
	for(int i = 17*7; i < 18*7; i++)
	{
		if(_blockMap->isBlockTurnOn(i))
			return true;
	}
	return false;
}
bool Blocks::turnOnNextLine()
{
	if(_flagId < BLOCK_Y_NUM)
	{
		_blockMap->turnOnLine(_flagId);
		_flagId++;
		return false;
	}
	else
	{
		_flagId = 0;
		return true;
	}
}

int Blocks::removeFullLines()
{
	int n = 0;
	int lineId = -1;
	while(1)
	{
		lineId = _blockMap->isSomeLineOn();
		if(lineId == -1)
			return n;
		n++;
		_blockMap->removeLine(lineId);
	}
	return n;

}