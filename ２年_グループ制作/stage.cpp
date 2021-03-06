#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"

#define TRAP_MAX 20
FILE* fp;

//int mapData[20*27];

// ﾏｯﾌﾟﾁｯﾌﾟ画像
int block[19];
XY mapPos;

// 画像ﾊﾝﾄﾞﾙ
int arrow;			// 矢
int bowgun[6];		// ﾎﾞｳｶﾞﾝ
int round[4];

// 変数
int pNum[PLAYER_MAX];
int stageCnt;
int tmpCycle;


TRAP trap[TRAP_MAX];
STAGE_NUM stage;

// ｽﾃｰｼﾞNo
int nowStage[CHIP_MAX_Y][CHIP_MAX_X] = {
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0
};

int stage1[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,10,0,0,9,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,12,0, 0,0,2,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1,1, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,12,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,1,
	1,0,0,0,0,0,12,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,1,1, 0,0,0,0,10,0,0,0,1, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,13,0, 0,0,0,1,1,1,1,1,13, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,7,0,0,0,0,0,12,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,1,7,1,2,1,1,1,7, 1,1,1,1,1,1,0,0,1,
	1,0,0,0,0,0,0,0,13, 0,0,0,0,0,0,0,0,13, 0,0,13,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,1,1,2,2,1,1,1,1, 1,1,1,1,1,1,1,1,1
};

int stage2[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,13,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,9,
	1,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,0, 0,0,0,1,1,1,2,2,1,
	1,0,0,0,0,0,0,0,12, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,12,0,0,0,0,0,0, 0,0,0,0,0,0,14,1,1, 1,1,7,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,12,12,12,12,0,0,1,
	1,0,0,1,7,2,0,0,0, 0,0,1,1,1,1,7,0,0, 0,0,1,1,1,1,0,0,1,
	1,0,0,1,0,0,1,0,0, 0,0,13,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,1,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,18,0,0,0,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,0,0, 1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,0,0, 12,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,7,1,1,1,1,1,1, 1,7,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1
};

int stage3[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,9,
	1,0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,1,1,1,1,1,
	1,0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 10,0,12,0,0,0,0,0,1,
	1,0,0,0,12,0,0,0,0, 0,0,0,0,0,0,0,0,1, 1,1,1,1,0,0,0,0,1,
	1,0,0,0,1,1,1,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	11,0,0,0,0,0,0,0,1, 1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,2,1,0,0,0,0,0,0, 0,0,0,0,0,0,12,0,0, 0,0,0,0,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,7,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,12,0,0, 1,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 1,1,1,0,18,1,1,1,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,10,0,0,0,0,1, 1,1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,1,1,2,2,1,1,1,1, 1,1,1,1,1,1,1,1,1
};

int stage4[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,9,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,2,1,
	1,0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,0, 0,1,1,2,0,0,0,0,1,
	1,1,2,2,1,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,1,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,18,1,
	1,0,0,0,0,1,1,2,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,12,1,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 1,1,2,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,1,2,1,0,0,0,0,1,
	1,12,12,12,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,1,1, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 1,2,2,1,1,1,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,2, 2,2,2,2,2,2,2,1,1, 1,1,1,1,1,1,1,1,1
};

int stage5[CHIP_MAX_Y][CHIP_MAX_X]{
	1,1,1,1,1,1,1,1,0, 0,0,0,0,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,9,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,2,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,18,12,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,2,1,1,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,12,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,1,1,1,1,1,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,0,0, 0,2,0,0,0,2,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,1,15,0,0,1,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,15,0,0,0,0,0,0,0, 0,1,18, 0,12,1,0,1,1, 7,1,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0, 0,1,1,2,1,1,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,14,1,1,1,1, 0,0,0,0,0,12,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,7,1,1,1,1, 1,2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,1
};

int stage6[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,9,
	1,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,1, 0,0,0,1,1,1,1,1,1,
	1,18,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,2, 0,0,0,0,0,0,0,0,1,
	1,12,0,0,2,0,0,0,0, 0,0,0,0,0,0,0,0,1, 0,0,0,12,0,0,0,0,1,
	1,1,1,2,1,0,0,0,0, 0,0,0,0,0,0,0,0,1, 0,0,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,12,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 1,1,1,1,1,15,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,1,2,7,1,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,12, 0,0,0,0,0,0,0,0,0, 0,0,12,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1, 1,0,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,2,1,1,1,1, 1,2,2,2,2,2,2,2,2, 1,1,1,1,1,1,1,1,1
};

int stage7[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,18,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,0,0,0,0, 0,0,0,0,2,0,0,0,0, 0,0,0,0,0,12,0,0,9,
	1,0,0,0,0,0,0,0,0, 14,1,1,1,1,0,0,0,12, 0,0,0,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,14,1, 15,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,12,0,0, 0,0,0,0,0,0,0,0,13, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,1,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,12,0,0,0,0,0, 0,0,0,0,12,0,0,0,1,
	1,0,0,0,0,0,0,0,12, 0,1,1,1,0,0,0,0,0, 0,0,7,1,1,1,0,0,1,
	1,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,15,0,0,0,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,0, 0,12,0,0,0,0,1,1,1,
	1,0,0,0,0,0,1,1,1, 0,0,0,0,0,0,0,0,0, 1,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,12,0,0,0,0,0,0,1,
	1,1,1,1,1,2,2,2,2, 2,2,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1
};


int Iwanna[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,13,0,0,0,1,0, 0,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,1,
	1,9,0,0,0,0,0,1,0, 0,0,0,1,16,1,1,1,1, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,13,0, 0,0,0,0,0,0,13,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,12,0,0,0, 0,0,1,1,1,1,15,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,12, 0,0,0,0,12,0,0,0,0, 0,1,1,2,1,1,1,0,1,
	1,0,0,0,0,1,0,0,1, 15,0,0,14,1,15,0,0,0, 0,0,0,0,13,0,0,0,1,
	1,0,0,0,0,1,0,0,1, 15,0,0,0,13,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,12,1,0,0,1, 15,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,
	1,0,1,1,1,1,0,0,1, 15,0,0,0,0,12,0,0,0, 12,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,1, 15,0,1,1,0,1,0,0,0, 1,0,0,0,1,0,16,0,1,
	1,0,0,0,0,0,0,0,1, 15,0,1,0,0,1,0,0,0, 1,0,0,14,1,0,0,0,1,
	1,0,0,0,0,0,12,0,1, 15,0,1,0,0,1,0,0,0, 1,15,0,0,1,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 15,0,1,0,0,1,12,12,12, 1,0,0,0,1,1,1,0,1,
	1,0,0,0,13,0,0,0,0, 0,0,1,0,14,1,1,1,1, 1,0,1,0,13,0,13,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0,0, 0,0,1,0,0,0,0,0,1,
	1,0,0,12,0,0,12,12,0,0,0,1,0,0,0,0,0,0, 0,0,1,0,0,12,0,0,1,
	1,1,1,1,1,1,1,1,1, 2,7,1,1,1,1,1,2,2, 1,1,1,1,1,1,1,1,1
};

int Iwanna2[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,0,1,1,0,1,1,        1,1,1,1,1,1,0,1,1,     1,1,1,1,1,1,1,1,1,
	1,1,1,0,1,1,0,0,0,        1,0,0,0,0,0,0,0,0,     0,0,0,0,0,0,0,0,1,
	1,13,13,0,13,13,0,0,0,   1,0,0,12,0,0,0,0,0,     0,12,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,        13,0,14,1,15,0,0,0,0,     14,1,15,0,0,0,14,1,1,
	1,0,0,0,0,0,0,0,0,        0,0,0,13,0,0,0,0,0,     0,13,0,0,0,0,1,13,1,
	1,9,0,0,0,0,0,0,0,       0,0,0,0,0,0,0,0,0,     0,0,0,0,14,1,13,0,1,
	1,1,2,2,1,2,2 ,1,1,       12,12,0,0,12,0,0,0,0,      0,0,0,0,0,13,16,0,1,
	1,13,13,13,13,13,13,0,0, 1,1,1,1,1,12,12,11,0,      0,12,12,12,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,       0,0,0,1,13,1,1,1,1,      1,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0,0,       0,0,0,1,0,0,0,0,0,      0,0,0,0,0,0,13,0,1,
	1,0,0,0,0,0,0,0,0,       1,1,0,1,0,0,0,0,0,      0,0,0,0,0,0,0,0,1,
	1,0,0,0,12,0,12,0,2,    13,1,0,1,0,0,12,0,12,      0,12,0,12,0,12,0,0,1,
	1,0,14,1,1,1,1,2,13,    0,1,0,1,0,1,1,1,1,     1,1,1,1,1,1,1,7,1,
	1,0,0,0,0,0,0,13,0,     0,1,0,1,0,0,0,0,0,       0,0,0,0,0.0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,      0,1,0,1,0,0,0,0,0,       0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,      0,1,0,1,7,1,2,1,1,       1,2,1,1,1,2,1,0,1,
	1,13,0,0,13,13,0,0,13  ,0,1,0,0,0,0,0,0,0,       0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,      0,1,0,16,0,0,0,0,0,       0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,12,0,0,     0,1,0,0,0,12,12 ,0,0,   12,12,0,0,12,12,0,0,0,
	1,1,2,2,1,1,1,1,1,      7,1,12,1,1,1,1,1,1,      1,1,1,1,1,1,1,1,1
};

int lobbyStage[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,1, 1,1,15,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,1,1, 1,0,0,0,0,0,0,0,1,
	1,1,2,1,1,1,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,1,1,2,2,1,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1, 1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,1,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,12,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,7,1,1,1,1,1,1,1, 1,1,0,0,0,0,1,1,1
};

int selectStage[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,1, 1,1,1,1,1,1,1,1,1, 1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,1,1,1,1,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,1, 1,1,1,1,1,1,1,1,1, 1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1
};

int titleStage[CHIP_MAX_Y][CHIP_MAX_X] = {
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1
};

int x1, x2;

void stageSysInit(void) 
{
	if((LoadDivGraph("png/stage4.png", 19, 16, 2, CHIP_SIZE_X, CHIP_SIZE_Y, block, true))== -1)AST();

	/*coin = LoadGraph("png/コイン1.png", true);*/
	if((arrow = LoadGraph("png/矢1.png", true)) == - 1) AST();
	if (LoadDivGraph("png/ボウガン改.png", 6, 6, 1, CHIP_SIZE_X, CHIP_SIZE_Y, bowgun, true) == -1) AST();
	round[0] = LoadGraph("png/1select.png", true);
	round[1] = LoadGraph("png/2select.png", true);
	round[2] = LoadGraph("png/3select.png", true);
	round[3] = LoadGraph("png/extra2.png", true);

	pNum[0] = LoadGraph("png/ネーム1.png");
	pNum[1] = LoadGraph("png/ネーム2.png");
	pNum[2] = LoadGraph("png/ネーム3.png");
	pNum[3] = LoadGraph("png/ネーム4.png");
	stageCnt = 0;
}

void stageInit(void)	
{
	
	GAME_MODE tmpMode = GetGameMode();
	if (stageCnt == 0) {
		tmpCycle = GetCycleType();
	}
	// ﾗﾝﾀﾞﾑで出した値でｽﾃｰｼﾞを決める
	if (tmpMode == GMODE_INIT) {
		stage = TITLE_STAGE;
	}
	if(tmpMode == GMODE_BATTLESELECT){
		stage = LOBBY_STAGE;
	}
	if(tmpMode != GMODE_INIT && tmpMode != GMODE_BATTLESELECT && tmpCycle != 4){
		stage = (STAGE_NUM)(rand() % 6);
		stageCnt++;
	}
	if (tmpMode != GMODE_INIT && tmpMode != GMODE_BATTLESELECT && tmpCycle == 4) {
		if (stageCnt == 0) {
			stage = EX_STAGE1;
		}
		else {
			stage = EX_STAGE2;
		}
		stageCnt++;
	}

	for (int i = 0; i < SCREEN_SIZE_X / CHIP_SIZE_X; i++)
	{
		for (int j = 0; j < SCREEN_SIZE_Y / CHIP_SIZE_Y; j++)
		{
			switch (stage) {					
			case STAGE1:
				nowStage[j][i] = stage1[j][i];
				break;
			case STAGE2:
				nowStage[j][i] = stage2[j][i];
				break;
			case STAGE3:
				nowStage[j][i] = stage3[j][i];
				break;
			case STAGE4:
				nowStage[j][i] = stage4[j][i];
				break;
			case STAGE5:
				nowStage[j][i] = stage5[j][i];
				break;
			case STAGE6:
				nowStage[j][i] = stage6[j][i];
				break;
			case STAGE7:
				nowStage[j][i] = stage7[j][i];
				break;
			case EX_STAGE1:
				nowStage[j][i] = Iwanna[j][i];
				break;
			case EX_STAGE2:
				nowStage[j][i] = Iwanna2[j][i];
				break;
			case LOBBY_STAGE:
				nowStage[j][i] = selectStage[j][i];
				break;
			case TITLE_STAGE:
				nowStage[j][i] = titleStage[j][i];
				break;
			default:
				AST();
				break;
			}
			//nowStage[j][i] = mapData[j * 27 + i];
		}
	}
	/*switch (stage) {
	case STAGE1:
		fopen_s(&fp, "mapData/stage1.bin", "rb");
		break;
	case STAGE2:
		fopen_s(&fp, "mapData/stage2.bin", "rb");
		break;
	case STAGE3:
		fopen_s(&fp, "mapData/stage3.bin", "rb");
		break;
	case STAGE4:
		fopen_s(&fp, "mapData/stage4.bin", "rb");
		break;
	case STAGE5:
		fopen_s(&fp, "mapData/stage5.bin", "rb");
		break;
	}
	
	fread(&mapData, sizeof(mapData), 1, fp);
	fclose(fp);*/
	
	// ﾄﾗｯﾌﾟの初期化
	for (int i = 0; i < TRAP_MAX; i++) {
		trapInit(i);
	}
}

void trapInit(int i) {
	// ﾄﾗｯﾌﾟ
	trap[i].flag = false;
	trap[i].pos = { 0, 0 };
	trap[i].size = { CHIP_SIZE_X, CHIP_SIZE_Y };
	trap[i].cnt = 0;
	trap[i].cntMax = 200;
	trap[i].moveSpeed = NOMAL_SPEED;
	trap[i].type = HIT_NEEDLE;															// 当たり判定を矩形と矩形で初期化
	trap[i].tEvent = BLOCK_FALL;												// イベントは落下で初期化


	// ｽﾃｰｼﾞ1
	if (stage == STAGE1)
	{
		switch (i) {
			// 落下針
		case 0:
			trap[i].pos = { 5 * CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			break;
			// 高速落下ﾌﾞﾛｯｸ
		case 1:
			trap[i].pos = { 5 * CHIP_SIZE_X, 0 };
			trap[i].moveSpeed = HIGH_SPEED;
			break;
			// 普通落下ﾌﾞﾛｯｸ
		case 2:
		case 3:
		case 4:
		case 5:
			trap[i].pos = { 5 * CHIP_SIZE_X, (i - 1) * CHIP_SIZE_Y };
			break;
			// 1/6針
		case 6:
			trap[i].pos = { 4 * CHIP_SIZE_X, 19 * CHIP_SIZE_Y - CHIP_SIZE_Y / 6 };
		
			trap[i].tEvent = BLOCK_STOP;
			break;
			// 飛び出す針(実際は飛び出すのではなく針の上に背景を描画して隠していた針を出現させる) 
		case 7:
			trap[i].pos = { 20 * CHIP_SIZE_X, 17 * CHIP_SIZE_Y };		
			trap[i].tEvent = BLOCK_POP;
			break;
		case 8:
			trap[i].pos = { 12 * CHIP_SIZE_X, 7 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 9:
			trap[i].pos = { 16 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 10:
			trap[i].pos = { 17 * CHIP_SIZE_X, 17 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
			// 矢
		case 11:
			trap[i].pos = { 25 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_MOVE;
		default:
			break;
		}

	}

	// ｽﾃｰｼﾞ2
	if (stage == STAGE2) {
		switch (i) {
			// 飛び出す針(実際は飛び出すのではなく針の上に背景を描画して隠していた針を出現させる) 
		case 0:
		case 1:
		case 2:
		case 3:
			trap[i].pos = { 20 * CHIP_SIZE_X + i * CHIP_SIZE_X, 12 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 4:
			trap[i].pos = { 9 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 5:
			trap[i].pos = { 20 * CHIP_SIZE_X, CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 6:
			trap[i].pos = { 2 * CHIP_SIZE_X, 7 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 7:
			trap[i].pos = { 8 * CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 8:
			trap[i].pos = { 15 * CHIP_SIZE_X, 7 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
			// 矢
		case 9:
		case 10:
		case 11:
			trap[i].pos = { 25 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y + (i - 8) * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_MOVE;
			trap[i].cntMax = 0;
			break;
		default:
			break;
		}
	}

	// ｽﾃｰｼﾞ3
	if (stage == STAGE3) {
		switch (i) {
		case 0:
			trap[i].pos = { 25 * CHIP_SIZE_X, 3 * CHIP_SIZE_Y - CHIP_SIZE_Y / 6 };
			trap[i].tEvent = BLOCK_STOP;
			break;
			// 飛び出す針
		case 1:
			trap[i].pos = { 20 * CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 2:
			trap[i].pos = { 15 * CHIP_SIZE_X, 15 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 3:
			trap[i].pos = { 4 * CHIP_SIZE_X, 6 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		default:
			break;
		}
	}

	// ｽﾃｰｼﾞ4
	if (stage == STAGE4) {
		switch (i) {
		case 0:
		case 1:
		case 2:
			trap[i].pos = { CHIP_SIZE_X + CHIP_SIZE_X * i, 13 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		default:
			break;
		}
	}

	// ｽﾃｰｼﾞ5
	if (stage == STAGE5) {
		switch (i) {
		case 0:		// 普通落下ﾌﾞﾛｯｸ
		case 1:
		case 2:
		case 3:
		case 4:
			trap[i].pos = { 7 * CHIP_SIZE_X + (i + 1) * CHIP_SIZE_X, 0 };
			break;
		case 5:
			trap[i].pos = { 4 * CHIP_SIZE_X, 15 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 6:
			trap[i].pos = { 14 * CHIP_SIZE_X, 15 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 7:
			trap[i].pos = { 11 * CHIP_SIZE_X, 10 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 8:
			trap[i].pos = { 13 * CHIP_SIZE_X, 11 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 9:
			trap[i].pos = { 2 * CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 10:
			trap[i].pos = { 12 * CHIP_SIZE_X, 7 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		default:
			break;
		}
	}

	// ｽﾃｰｼﾞ6
	if (stage == STAGE6) {
		switch (i) {
		// 飛び出す針
		case 0:	
			trap[i].pos = { 8 * CHIP_SIZE_X, 15 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 1:
			trap[i].pos = { 20 * CHIP_SIZE_X, 15 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 2:
			trap[i].pos = {  CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 3:
			trap[i].pos = { 11 * CHIP_SIZE_X, 7 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 4:
			trap[i].pos = { 14 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 5:
			trap[i].pos = { 21 * CHIP_SIZE_X, 5 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		// 6分の1針
		case 6:
			trap[i].pos = { 23 * CHIP_SIZE_X, 3 * CHIP_SIZE_Y - CHIP_SIZE_Y / 6};
			trap[i].tEvent = BLOCK_STOP;
			break;
		default:
			break;
		}
	}

	// ｽﾃｰｼﾞ7
	if (stage == STAGE7) {
		switch (i) {
		// 飛び出す針
		case 0:
			trap[i].pos = { 6 * CHIP_SIZE_X, 6 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 1:
			trap[i].pos = { 12 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 2:
			trap[i].pos = { 22 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 3:
			trap[i].pos = { 19 * CHIP_SIZE_X, 13 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 4:
			trap[i].pos = { 19 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		case 5:
			trap[i].pos = { 23 * CHIP_SIZE_X, 3 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_POP;
			break;
		default:
			break;
		}
	}

	// EXｽﾃｰｼﾞ2	※ EXｽﾃｰｼﾞ1は動くｷﾞﾐｯｸがないため何もしない
	if (stage == EX_STAGE2)
	{
		switch (i) {
			// 落下針
		case 0:
		case 1:
			trap[i].pos = { 3 * CHIP_SIZE_X + (3 * CHIP_SIZE_X * i), 2 * CHIP_SIZE_Y };
			break;
			// 普通落下ﾌﾞﾛｯｸ
		case 2:
		case 3:
			trap[i].pos = { 3 * CHIP_SIZE_X, (i - 2)* CHIP_SIZE_Y };			// ゴール前
			break;
		case 4:
		case 5:
			trap[i].pos = { 6 * CHIP_SIZE_X, (i - 4)* CHIP_SIZE_Y };			// ゴール前
			break;
		case 6:
			trap[i].pos = { 15 * CHIP_SIZE_X, 0 };	//真ん中上
			break;
		// 矢
		case 7:
			trap[i].pos = { 26 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_MOVE;
			break;
		case 8:
			trap[i].pos = { 23 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_MOVE;
			break;
		default:
			break;
		}

	}

	if (stage == LOBBY_STAGE) {
		switch (i) {
		case 0:
			trap[i].pos = { 7 * CHIP_SIZE_X, 10 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_SELECT;
			trap[i].type = HIT_SELECT_1;
			break;
		case 1:
			trap[i].pos = { 14 * CHIP_SIZE_X, 10 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_SELECT;
			trap[i].type = HIT_SELECT_2;
			break;
		case 2:
			trap[i].pos = { 7 * CHIP_SIZE_X, 2 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_SELECT;
			trap[i].type = HIT_SELECT_3;
			break;
		case 3:
			trap[i].pos = { 14 * CHIP_SIZE_X, 2 * CHIP_SIZE_Y };
			trap[i].tEvent = BLOCK_SELECT;
			trap[i].type = HIT_SELECT_EX;
			break;
		}
	}

	// ｲﾍﾞﾝﾄごとのﾄﾗｯﾌﾟの初期化
	switch (trap[i].tEvent) {
	case BLOCK_FALL:
		break;
	case BLOCK_POP:
		trap[i].type = NO_HIT;																	// 当たり判定がないため　7
		trap[i].flag = true;																// ﾌﾟﾚｲﾔｰが近づくまでtrue
		trap[i].cntMax = 100;
		break;
	case BLOCK_MOVE:
		trap[i].type = HIT_ARROW;
		break;
	case BLOCK_STOP:
		trap[i].type = HIT_S_NEEDLE;																	// 当たり判定を小さくするため　1
		trap[i].flag = true;																// 動きがないため常にtrue
		break;
	case BLOCK_SELECT:
		trap[i].size = { CHIP_SIZE_X * 6, CHIP_SIZE_Y * 6};
		trap[i].flag = true;
		break;
	}
}

void stageMain(void)
{
	
	// ﾄﾗｯﾌﾟの起動
	for (int i = 0; i < TRAP_MAX; i++) {
		for (int j = 0; j < 4; j++) {
			CHARACTER tmp = GetPlayer(j);
			if (stage == STAGE1) {
				// 岩落としﾄﾗｯﾌﾟ
				if (trap[i].tEvent == BLOCK_FALL) {
					if (tmp.pos.x < trap[i].pos.x + 2 * CHIP_SIZE_X && tmp.pos.x > trap[i].pos.x - 3 * CHIP_SIZE_X && tmp.pos.y < trap[i].pos.y + 7 * CHIP_SIZE_Y) {
						trap[i].flag = true;						// ﾄﾗｯﾌﾟの起動
					}

				}
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
				// 矢
				if (trap[i].tEvent == BLOCK_MOVE) {
					if (tmp.pos.x > trap[i].pos.x - 13 * CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y * 2
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = true;
					}
				}
			}

			if (stage == STAGE2) {
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
				// 矢
				if (trap[i].tEvent == BLOCK_MOVE) {
					trap[i].flag = true;
				}
			}

			if (stage == STAGE3) {
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
			}

			if (stage == STAGE4) {
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y * 2) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
			}

			if (stage == STAGE5) {
				// 岩落としﾄﾗｯﾌﾟ
				if (trap[i].tEvent == BLOCK_FALL) {
					if (tmp.pos.x < trap[i].pos.x + 2 * CHIP_SIZE_X && tmp.pos.x > trap[i].pos.x - 3 * CHIP_SIZE_X && tmp.pos.y < trap[i].pos.y + 7 * CHIP_SIZE_Y) {
						trap[i].flag = true;						// ﾄﾗｯﾌﾟの起動
					}
				}
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}

				}
			}

			if (stage == STAGE6) {
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + (CHIP_SIZE_X + CHIP_SIZE_X / 2)
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
			}

			if (stage == STAGE7) {
				// 針飛び出し
				if (trap[i].tEvent == BLOCK_POP) {
					if (tmp.pos.x < trap[i].pos.x + CHIP_SIZE_X + CHIP_SIZE_X * 2
						&& tmp.pos.x > trap[i].pos.x - CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = false;
						trap[i].cnt = 0;
					}
				}
			}

			if (stage == EX_STAGE2) {
				// 岩落としﾄﾗｯﾌﾟ
				if (trap[i].tEvent == BLOCK_FALL) {
					if (tmp.pos.x < trap[i].pos.x + 2 * CHIP_SIZE_X && tmp.pos.x > trap[i].pos.x - 3 * CHIP_SIZE_X && tmp.pos.y < trap[i].pos.y + 7 * CHIP_SIZE_Y) {
						trap[i].flag = true;						// ﾄﾗｯﾌﾟの起動
					}
				}
				// 矢
				if (trap[i].tEvent == BLOCK_MOVE) {
					if (tmp.pos.x > trap[i].pos.x - 13 * CHIP_SIZE_X
						&& tmp.pos.y < trap[i].pos.y + CHIP_SIZE_Y * 2
						&& tmp.pos.y > trap[i].pos.y - CHIP_SIZE_Y) {
						trap[i].flag = true;
					}
				}
			}
		}
	}

	// 動くﾄﾗｯﾌﾟの移動
	for (int i = 0; i < TRAP_MAX; i++) {
		TrapMove(trap[i].tEvent, i, DIR_LEFT);
		if (trap[i].pos.x < 0 || trap[i].pos.y > SCREEN_SIZE_Y) {
			trap[i].cnt++;
			if (trap[i].cnt > trap[i].cntMax) {				// 再生成の時間
				trapInit(i);
				trap[i].cnt = 0;
			}
		}
	}
	//ｾｰﾌﾞﾎﾟｲﾝﾄ1ﾙｰﾌﾟ毎に初期化判定
	for (int i = 0; i < SCREEN_SIZE_X / CHIP_SIZE_X; i++)
	{
		for (int j = 0; j < SCREEN_SIZE_Y / CHIP_SIZE_Y; j++)
		{
			switch (nowStage[j][i]) {
			case 17:
				nowStage[j][i] = 16;
				break;
			}
		}
	}
}
void stageDraw(void)
{
	
	//ステージの描画
	for (int i = 0; i < SCREEN_SIZE_X / CHIP_SIZE_X; i++)										// SCREEN_SIZE_X / CHIP_SIZE_X = 27
	{	
		for (int j = 0; j < SCREEN_SIZE_Y / CHIP_SIZE_Y; j++)									// SCREEN_SIZE_Y / CHIP_SIZE_Y = 20
		{
			DrawGraph(i * CHIP_SIZE_X, j * CHIP_SIZE_Y, block[nowStage[j][i]], true);

			// ｽﾃｰｼﾞ1
			if (stage == STAGE1)
			{
				// 飛び出す針を隠す背景
				for (int k = 7; k <= 10; k++) {
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);				//trap[] = { 7 ~ 10}
					}
				}
				//落下ﾄﾗｯﾌﾟ
				DrawGraph(trap[0].pos.x, trap[0].pos.y, block[4], true);						//5 * CHIP_SIZE_X,5 * CHIP_SIZE_Y
				for (int y = 1; y < 6; y++)
				{
					DrawGraph(trap[y].pos.x, trap[y].pos.y, block[1], true);					//trap[] = { 1 ~ 5}
				}
				// 小さい針
				DrawGraph(trap[6].pos.x, trap[6].pos.y, block[3], true);
				DrawGraph(4 * CHIP_SIZE_X, 19 * CHIP_SIZE_Y, block[1], true);					// ﾄﾗｯﾌﾟの下側を隠すﾌﾞﾛｯｸ

		
				// ボウガンと矢
				if (!trap[11].flag) {
					DrawGraph(25 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y, bowgun[2], true);
				}
				else
				{
					DrawGraph(25 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y, bowgun[0], true);
				}
				DrawGraph(trap[11].pos.x, trap[11].pos.y, arrow, true);				
				
			}
			// ｽﾃｰｼﾞ2
			if (stage == STAGE2)
			{
			// 飛び出す針
				for (int k = 0; k < 9; k++)
				{
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);
					}	
				}
				// ボウガンと矢
				for (int h = 9; h < 12; h++)												
				{
					if (!trap[h].flag) {
						DrawGraph(25 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y + (h - 8) * CHIP_SIZE_Y, bowgun[2], true);
					}
					else {
						DrawGraph(25 * CHIP_SIZE_X, 8 * CHIP_SIZE_Y + (h - 8) * CHIP_SIZE_Y, bowgun[0], true);
					}
					DrawGraph(trap[h].pos.x, trap[h].pos.y, arrow, true);
				}
				// 偽岩
				DrawGraph(25 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y, block[1], true);
				
			}
			// ｽﾃｰｼﾞ3
			if (stage == STAGE3)
			{
				// 1/6針
				DrawGraph(trap[0].pos.x, trap[0].pos.y, block[3], true);
				DrawGraph(25 * CHIP_SIZE_X, 3 * CHIP_SIZE_Y, block[1], true);

				
				// 飛び出す針
				for (int k = 1; k < 4; k++) {
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);
					}
				}
			}
			// ｽﾃｰｼﾞ4
			if (stage == STAGE4)
			{
				// 飛び出す針
				for (int h = 0; h < 3; h++)
				{
					if (trap[h].flag) {
						DrawGraph(trap[h].pos.x, trap[h].pos.y, block[0], true);
					}
				}
				
				//// 半透明床を隠す普通の床
				for (int g = 22; g < 26; g++)
				{
					DrawGraph(g * CHIP_SIZE_X, 9 * CHIP_SIZE_Y, block[3], true);
					DrawGraph(g * CHIP_SIZE_X, 9 * CHIP_SIZE_Y, block[1], true);
				}
			}
			// ｽﾃｰｼﾞ5
			if (stage == STAGE5)
			{
				// 飛び出す針
				for (int k = 5; k < 11; k++)
				{
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);			// //trap[] = { 0 ~ 3}
					}
				}
				// 落下するﾌﾞﾛｯｸ
				for (int k = 0; k < 5; k++)
				{
 					DrawGraph(trap[k].pos.x, trap[k].pos.y, block[1], true);			// //trap[] = { 0 ~ 3}
				}
			}
			// ｽﾃｰｼﾞ6
			if (stage == STAGE6) {
				// 飛び出す針
				for (int k = 0; k < 6; k++) {
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);
					}
				}
				DrawGraph(trap[6].pos.x, trap[6].pos.y, block[3], true);
				DrawGraph(23 * CHIP_SIZE_X, 3 * CHIP_SIZE_Y, block[1], true);					// ﾄﾗｯﾌﾟの下側を隠すﾌﾞﾛｯｸ
			}

			if (stage == STAGE7) {
				for (int k = 0; k < 6; k++) {
					if (trap[k].flag) {
						DrawGraph(trap[k].pos.x, trap[k].pos.y, block[0], true);
					}
				}
			}

			if (stage == EX_STAGE2) {
				// 落下するﾌﾞﾛｯｸ
				DrawGraph(trap[0].pos.x, trap[0].pos.y, block[4], true);
				DrawGraph(trap[1].pos.x, trap[1].pos.y, block[4], true);
				for (int k = 2; k < 7; k++){
					DrawGraph(trap[k].pos.x, trap[k].pos.y, block[1], true);					//trap[] = { 1 ~ 5}23 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y
				}
				// ﾎﾞｳｶﾞﾝと矢
				if (!trap[7].flag) {
					DrawGraph(26 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y, bowgun[2], true);
				}
				else {
					DrawGraph(26 * CHIP_SIZE_X, 18 * CHIP_SIZE_Y, bowgun[0], true);
				}
				if (!trap[8].flag) {
					DrawGraph(23 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y, bowgun[2], true);
				}
				else {
					DrawGraph(23 * CHIP_SIZE_X, 4 * CHIP_SIZE_Y, bowgun[0], true);
				}
				for (int l = 7; l < 9; l++) {
					
					DrawGraph(trap[l].pos.x, trap[l].pos.y, arrow, true);
				}
			}

			if (stage == LOBBY_STAGE) {
			
				for (int k = 0; k < 4; k++) {
					DrawGraph(trap[k].pos.x, trap[k].pos.y, round[k], false);
				}
				for (int l = 0; l < PLAYER_MAX; l++) {
					CHARACTER tmp = GetPlayer(l);
					if (tmp.selectFlag) {
						if (tmp.selectType == 1) {
							DrawGraph(7 * CHIP_SIZE_X + 48 * l, 9 * CHIP_SIZE_Y, pNum[l], false);
						}
						if (tmp.selectType == 2) {
							DrawGraph(14 * CHIP_SIZE_X + 48 * l, 9 * CHIP_SIZE_Y, pNum[l], false);
						}
						if (tmp.selectType == 3) {
							DrawGraph(7 * CHIP_SIZE_X + 48 * l,  CHIP_SIZE_Y, pNum[l], false);
						}
						if (tmp.selectType == 4) {
							DrawGraph(14 * CHIP_SIZE_X + 48 * l,  CHIP_SIZE_Y, pNum[l], false);
						}
					}
				}
				
				
			}
		}		
	}	//DrawFormatString(0, 60, 0x000000, "trap.pos x %d, y %d" , trap[11].pos.x, trap[11].pos.y);
}

bool IsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 1:		// 壁
	case 7:		// ｼﾞｬﾝﾌﾟﾌﾞﾛｯｸ
		ret = false;
		break;
	}
	return ret;
}

// ﾃﾚﾎﾟｰﾄ
bool TelIsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 10:
		ret = false;
		break;
	}
	return ret;
}

// 針
bool NeedleIsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 3:
	case 4:
	case 5:
	case 6:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		ret = false;
		break;
	}
	return ret;
}

bool JumpIsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 7:
		ret = false;
		break;
	}
	return ret;
}

// ｺﾞｰﾙ
bool GoalIsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 9:
		ret = false;
		break;
	}
	return ret;
}

bool SaveIsPass(XY pos)
{
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 16:
		nowStage[mapIndex.y][mapIndex.x] = 17;
		ret = false;
		break;
	}
	return ret;
}

bool CoinIsPass(XY pos) {
	bool ret = true;
	int mapNo;
	XY mapIndex;

	mapIndex = MapPosToIndex(pos);
	mapNo = nowStage[mapIndex.y][mapIndex.x];

	switch (mapNo) {
	case 18:
		nowStage[mapIndex.y][mapIndex.x] = 0;
		ret = false;
		break;
	}
	return ret;
}


XY MapPosToIndex(XY pos)
{
	XY mapIndex;
	mapIndex = { pos.x / CHIP_SIZE_X,  pos.y / CHIP_SIZE_Y };

	return mapIndex;
}

XY MapIndexToPos(XY index) {
	XY mapPos;
	mapPos = { index.x * CHIP_SIZE_X, index.y * CHIP_SIZE_Y };
	return mapPos;
}

XY MapPosToMoveIndex(XY pos, bool flag, XY_F velocity) {

	XY tmpIndex;
	XY tmpPos;
	tmpIndex = MapPosToIndex(pos);

	if (flag) {
		tmpIndex.y++;
	}
	if (velocity.x < 0) {			// 左
		tmpIndex.x++;
	}
	tmpPos = MapIndexToPos(tmpIndex);

	return tmpPos;
}

XY GetMapPos() {
	return mapPos;
}

TRAP GetTrap(int i) {
	return trap[i];
}

void TrapMove(T_EVENT_MODE event, int i, MOVE_DIR dir) {
	
	switch (event) {
	case BLOCK_FALL:
		if (trap[i].flag) {
			trap[i].pos.y += trap[i].moveSpeed;
		}
		break;
	case BLOCK_POP:
		trap[i].cnt++;
		if (trap[i].cnt > trap[i].cntMax) {				// 再生成の時間
			trapInit(i);
			trap[i].cnt = 0;
		}
		break;
	case BLOCK_MOVE:
		if (trap[i].flag) {
			trap[i].pos.x -= trap[i].moveSpeed;
		}
		break;
	default:
		break;

	}
}