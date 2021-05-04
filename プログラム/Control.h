#pragma once
#include "Make_Dungeon.h"
#include "Player.h"
#include "Messege.h"
#include "Battle.h"
#include "define.h"
#include "Parameter.h"

//それぞれのクラスへの参照
class Player;
class Make_Dungeon;
class Messege;
class Battle;
class Parameter;


//ゲームシーン(ゲーム本編の管理)クラス
class Control {

//変数
private:

	//インスタンス
	Make_Dungeon* make_d;
	Player* player;
	Battle* battle;
	Messege* messege;
	Parameter* para;

	//ゲーム進行に使用する変数
    int idx; //今の場面
	int count; //ループをカウント

	//グラフィックハンドル
	int gameovergh; //ゲームオーバー画像
	int gameover_pgh[4]; //ゲームオーバー時のプレイヤー画像


	int floor; //階層
	int gameover_index; //ゲームオーバー時のプレイヤー画像の添え字
	bool gameend; //ゲームオーバーか否か

	//サウンドハンドル
	int dungeon_bgm; //ダンジョン探索中BGM
	int battle_bgm; //バトル中BGM
	int gameover_se; //ゲームオーバーSE
    int win_bgm; //勝利BGM
	int item_se; //アイテムゲットSE
	int stairs_se; //階段おりるSE
	int e_attack_se; //敵攻撃SE
	int p_attack_se; //プレイヤー攻撃SE 
	int magic_se; //魔法SE
	int recover_se; //回復SE
	int run_se;   //逃げるSE

public:
	//音を鳴らすのかフラグ
	bool dungeon_bgm_flag;
	bool battle_bgm_flag;
	bool win_bgm_flag;
	bool gameover_se_flag;
	bool item_se_flag;
	bool stairs_se_flag;
	bool e_attack_se_flag;
	bool p_attack_se_flag;
	bool magic_se_flag;
	bool recover_se_flag;
	bool run_se_flag;

//関数
private:
	Control(); //シングルトン(インスタンス2つ禁止)
	~Control();
	void sound(); //音の管理関数

public:
	void All(); //ループで行う関数
	void Update(); //シーン移動
	void initialize(); //初期化
	void finalize(); //終了処理

	void player_positon(double* x, double* y); //引数にプレイヤーの位置を与える 
	int dungeon_info(int x,int y);  //(x,y)のダンジョンの情報を返す
	void set_dungeon_info(int info, int index_x, int index_y); //(index_x,index_y)のダンジョンの情報をinfoにする
	void set_idx(int index); //今の場面を引数にする(indexにする)
	void get_p_status(p_status *pl); //引数にプレイヤーの情報を与える
	void set_p_status(p_status pl); //プレイヤーの情報を引数の情報に更新する
	bool set_p_damage(int damage); //プレイヤーに引数分のダメージを与える
	int get_floor(); //現在の階数を返す
	static Control& Instance() {//クラス静的変数、自身のインスタンスを格納
		static Control control;//静的変数として宣言
		return control;
	}

};