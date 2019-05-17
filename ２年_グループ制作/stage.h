#pragma once

#define CHIP_SIZE_X 48
#define CHIP_SIZE_Y 48

#define CHIP_MAX_X 27
#define CHIP_MAX_Y 20

enum TRAP_SPEED {
	NOMAL_SPEED = 15,
	HIGH_SPEED = 50
};

enum STAGE_NUM {
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	EX_STAGE1,
	STAGE_MAX
};

enum T_EVENT_MODE {
	BLOCK_FALL,
	BLOCK_POP,
	BLOCK_MOVE,
	BLOCK_STOP
};

typedef struct {
	bool flag;
	int type;				// 当たり判定用 0: 矩形と矩形 1:矩形と線 2: ﾌﾞﾛｯｸ(死なない)
	XY pos;					// 位置
	XY size;				// ｻｲｽﾞ
	TRAP_SPEED moveSpeed;
	int animCnt;
	int cnt;
	T_EVENT_MODE tEvent;
	MOVE_DIR moveDir;

} TRAP;




// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void stageSysInit(void);
void stageInit(void);
void trapInit(int);
void stageMain(void);
void stageDraw(void);
bool IsPass(XY pos);
XY MapPosToIndex(XY pos);
XY MapIndexToPos(XY index);
XY MapPosToMoveIndex(XY pos, bool flag, XY_F velocity);
XY GetMapPos();
bool TelIsPass(XY pos);
bool NeedleIsPass(XY pos);
bool JumpIsPass(XY pos);
bool GoalIsPass(XY pos);
bool SaveIsPass(XY pos);
TRAP GetTrap(int i);

void TrapMove(T_EVENT_MODE event, int i, int cnt);


