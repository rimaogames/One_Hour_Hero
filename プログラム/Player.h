#pragma once
#include "define.h"
#include "InputKey.h"
#include "Control.h"
#include <random>


class Player
{
//変数
private:

	//プレイヤー画像のグラフィックハンドル
	int playergh[12];

	//プレイヤー画像の大きさ
	int width;
	int height;

	//プレイヤー画像を変化する時に使う関数
	int xcount;//横に歩くとカウント
	int ycount; //縦
	int ix; //横の添え字
	int iy; //縦の添え字
	int index; //グラフィックハンドルに入れる実際の添え字


	//プレイヤーの位置
	double p_x; 
	double p_y;
    //何のアイテムを手に手に入れた?
	int get_item= MESSEGE::GET_POTION;

	//ステータス
	p_status status;

//関数
private:

	void move(); //移動
	void draw(); //描画
	bool check(); //下にイベントがあるのか調べる

public:
	Player();
	~Player();
	bool All(bool init_flag); //プレイヤーの処理を行う関数

	p_status get_status(); //ステータスを返す
	void set_status(p_status pl); //ステータスを更新
	bool check_life(); //生きているのか調べる。(ダンジョンない移動中に使用)
	bool set_damage(int damage); //ダメージを受けてライフの更新をする
	void get_potision(double* x, double* y); //ポジションを引数に渡す　
	int  get_item_info(); //どのアイテムを手に入れたのかを返す
	void set_init_positon(); //初期位置をセットする

};

