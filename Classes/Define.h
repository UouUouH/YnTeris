#ifndef  _DEFINE_H_
#define  _DEFIEN_H_


//GAME RUNING LAYER
#define SYSSET_X	203+65/2
#define SYSSET_Y	512-360+28/2
#define PAUSE_X		203+65/2
#define PAUSE_Y		512-414+28/2
#define PLAY_X		286/2
#define PLAY_Y		512/2
#define LEFT_X		20+43/2
#define LEFT_Y		38
#define TURN_X		20+43/2+43+8
#define TURN_Y		38
#define DOWN_X		20+43/2+(43+8)*2
#define DOWN_Y		38
#define FAST_X		20+43/2+(43+8)*3
#define FAST_Y		38
#define RIGHT_X		20+43/2+(43+8)*4
#define RIGHT_Y		38

//---------block----------
#define BLOCK_IMG_NUM	16
#define BLOCK_WIDTH		22
#define BLOCK_HEIGHT	22
//id 为0 的block 的坐标位置，即最左下方的那个方块的位置
#define BLOCK_X			26//25
#define BLOCK_Y			88//89
#define PRE_BLOCK_X		220
#define PRE_BLOCK_Y		405
#define PRE_BLOCK_WIDTH		15
#define PRE_BLOCK_HEIGHT	15

#define BLOCK_X_NUM		7//x方向方块的数目
#define BLOCK_Y_NUM		18//y 方向方块的数目
#define BLOCK_GAME_OVER_TIME	1/60 //游戏结束的动画刷新时间
#define BLOCK_MOVE_DOWN_TIME	1 //游戏结束的动画刷新时间
#define BLOCKS_SHAPES	19
//BLOCKS_X_POSITION 指的一个新的俄罗斯方块出来时，它的初始位置
#define BLOCKS_X_POSITION 3
#define BLOCKS_Y_POSITION 17

#define BLOCK_TAG   1
/*
//   * *
//   * *
#define O_SHAPE_1		0   
//    *      *       * *   * * *
//    *	     * * *   *         *
//  * *			 	 *          
#define NL_SHAPE_1		1
#define NL_SHAPE_2		2
#define NL_SHAPE_3		3
#define NL_SHAPE_4		4

#define L_SHAPE_1		5
#define L_SHAPE_2		6
#define L_SHAPE_3		7
#define L_SHAPE_4		8
#define Z_SHAPE_1		9
#define Z_SHAPE_2		10
#define NZ_SHAPE_1		11
#define NZ_SHAPE_2		12
#define	T_SHAPE_1		13
#define	T_SHAPE_2		14
#define	T_SHAPE_3		15
#define	T_SHAPE_4		16
#define	I_SHAPE_1		17
#define	I_SHAPE_2		18

*/



#endif  _DEFIEN_H_
