#pragma once
#include "define.h"
#include "Control.h"
#include "InputKey.h"
#include "Enemy.h"
#include "Messege.h"
#include <sstream>
#include <random>


//Messegeクラスへの参照
class Messege;


//バトルクラス
class Battle
{

//変数
private:
	//インスタンス
	Enemy *enemy;
	Messege* messege;

	//グラフィックハンドル
	int backgh; //背景
	int efectgh[9]; //プレイヤ攻撃エフェクト
	int magicgh[8]; //プレイヤ魔法エフェクト
	int com[4]; //コマンド


	//演出に使用する変数
	int step;   //敵が一歩前へ
	int swing;  //画面が揺れる
	int d_count; //敵が点滅
	int pre_bx;  //1つ前の背景の描画x座標
	int pre_by;  //y座標
	int efe_cont; //攻撃エフェクトを出すフラグ
	int mag_cont; //魔法エフェクトを出すフラグ

	//フラグ
	bool use_item; //アイテムを使用するフラグ
	bool p_turn; //プレイヤのターンフラグ
	bool end;    //バトル終了フラグ

	//今選んでいるコマンド
	int now_com; 

	//ターンを管理する変数
	int idx;
	int count;

	//ダメージを保持する変数
	int e_damage;
	int p_damage;

	//経験値
	int e_point;

//関数
private:

	void draw(); //描画
	void command(); //コマンド
	void recover(); //ライフ回復
	void levelup(int point); //レベルアップ

public:

	Battle();
	void init(); //バトル初期化
	void set_player_turn(bool flag); //プレイヤターンフラグをflagにする　
	void set_effect(int s, int d, int e, int m,int st); //エフェクトの設定をする
	void All(); //ループで行う実行関数

};

