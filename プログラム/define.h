#pragma once
#include "DxLib.h"
#include <Windows.h>
#include <iostream>
#include <vector>
//様々な定義ヘッダー

//メッセージボックス
#define MSG(m){\
MessageBoxA(NULL,m, "メッセージ", MB_OK);}


#define KEY 256 //キーボードの種類


#define MAZE_H 9  //迷路の縦の長さ
#define MAZE_W 11 //横

#define DUNG_H 27 //ダンジョンの縦の長さ(9*3)
#define DUNG_W 33//横(11*3)

#define F_SIZE 80 //床のパネルのサイズ

#define NUMBER1_W 27 //数字1の幅(メッセージで使用)
#define NUMBER2_W 13 //数字2　(パラメータで使用)
#define NUMBER3_W 23 //数字3　(メッセージで使用)



//プレイヤーの情報　
struct  p_status
{
	int life; //ライフ
	int lifemax; //ライフ最大値
	int power; //力
	int food; //満腹度
	int point; //今稼いでいる経験値
	int level; //今のレベル
	int pointmax; //次のレベルになるための経験値
	int potion; //ポーション所持数
	int mp; //魔法石所持数
};

//敵の情報　列挙型
struct e_status {
	int type; //敵の種類
	int life; //ライフ
	int lifemax; //ライフ最大値
	int power; //力
	int point; //経験値
	int x; //描画するx座標
	int y; //描画するy座標
};

//コマンド列挙型
typedef enum {
	ATTACK, //攻撃 0
	USE_POTION, //ポーション 1
	MAGIC, //魔法 2
	RUN, //逃げる 3
	cnum, //コマンドの数 4
}COM;


//メッセージ列挙型
typedef enum {
	NEW_FLOOR, //新しい階に来た 0
	GET_POTION,//ポーション取得 1
	GET_STONE, //魔法石取得 2
	GET_POISON,//毒取得 3
	GET_FOOD1, //食べ物1取得　4
	GET_FOOD2, //食べ物2取得　5
	ENCOUNTER, //敵と遭遇　6
	P_TUEN,    //プレイヤーのターン 7
	P_ATTACK,  //プレイヤーの攻撃　8
	P_POTION,  //ポーション使用 9
	P_MAGIC,   //魔法　10
	P_AVOID,   //プレイヤーが回避 11
	P_RUN,     //プレイヤーが逃げた　12
	P_NOT_RUN, //逃げられなかった 13
	E_ATTACK,  //敵の攻撃　14
	E_AVOID,   //敵が避けた　15
	DAMAGE,    //〇〇ダメージ　16
	RECOVER,   //回復した　17
	NO_ITEM,   //アイテムをもっていなかった 18
	WIN,       //勝った　19
	LOSE,      //負けた　20
	LEVELUP,   //レベルがアップした　21
	messege_num, //メッセージの数　22
}MESSEGE;


//シーン　列挙型
enum  class eScene { 
	Scene_Menu,    //メニュー画面
	Scene_Game,    //ゲーム画面
	Scene_Howto,   //遊び方画面
	Scene_Result,  //結果画面
	Scene_None,   //画面なし
};

//グローバル変数
//全体でのハイスコアは？
extern int hiscore;