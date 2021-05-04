#pragma once
#include "define.h"
#include <random>
#include <string>

//敵のクラス

class Enemy
{
//変数
private:

	//グラフィックハンドル
	int number2[10]; //数字
	int slashgh;//スラッシュ(/)
	int enemygh;//敵

	//敵の情報
	e_status enemy;

//関数
public:
	Enemy();
	~Enemy();
	void e_init(int fl); //初期化
	bool set_damage(int e_damage); //ダメージの設定
	void get_point(int *p); //経験値を引数に取得
	int  get_power(); //敵の力を返す
	void draw(int d_count,int step); //描画
	
};

