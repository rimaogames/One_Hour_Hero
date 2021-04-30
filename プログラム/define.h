#pragma once
#include "DxLib.h"
#include <Windows.h>
#include <iostream>
#include <vector>


//メッセージボックス
#define MSG(m){\
MessageBoxA(NULL,m, "メッセージ", MB_OK);}


#define KEY 256 //キーボードの種類


#define MAZE_H 9  //迷路の縦の長さ
#define MAZE_W 11 //横

#define DUNG_H 27 //ダンジョンの縦の長さ(9*3)
#define DUNG_W 33//横(11*3)

#define F_SIZE 80 //床のパネルのサイズ
#define NUMBER_W 27
#define NUMBER2_W 13
#define NUMBER3_W 23
struct  p_status
{
	int life;
	int lifemax;
	int power;
	int food;
	int point;
	int level;
	int pointmax;
	int potion;
	int mp;
};

struct e_status {
	int type;
	int lifemax;
	int life;
	int power;
	int point;
	int x;
	int y;
};

typedef enum {
	ATTACK,
	USE_POTION,
	MAGIC,
	RUN,
	cnum,
}COM;

typedef enum {
	NEW_FLOOR,
	GET_POTION,
	GET_STONE,
	GET_POISON,
	GET_FOOD1,
	GET_FOOD2,
	ENCOUNTER,
	P_TUEN,
	P_ATTACK,
	P_POTION,
	P_MAGIC,
	P_AVOID,
	P_RUN,
	P_NOT_RUN,
	E_ATTACK,
	E_AVOID,
	DAMAGE,
	RECOVER,
	NO_ITEM,
	WIN,
	LOSE,
	LEVELUP,
	messege_num,
}MESSEGE;

typedef enum {
	POTION,
	MAGIC_STONE,
	POISON,
	FOOD1,
	FOOD2
}ITEM;

//画面
enum  class eScene {      //列挙型
	Scene_Menu,    //メニュー画面
	Scene_Game,    //ゲーム画面
	Scene_Howto,   //遊び方画面
	Scene_Result,  //結果画面
	Scene_None,   //画面なし
};

extern int hiscore;//全体でのハイスコアは？