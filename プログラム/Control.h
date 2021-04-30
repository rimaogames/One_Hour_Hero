#pragma once
#include "Make_Dungeon.h"
#include "Player.h"
#include "Messege.h"
#include "Battle.h"
#include "define.h"
#include "Parameter.h"

class Player;
class Make_Dungeon;
class Messege;
class Battle;

class Control {
private:
	Make_Dungeon* make_d;
	Player* player;
	Battle* battle;
	Messege* messege;
	Parameter* para;
    int idx;
	int count;

	int floor;
	int gameovergh;
	int gameover_pgh[4];
	int gameover_count;
	bool gameend;

	int dungeon_bgm;
	int battle_bgm;
	int gameover_se;
    int win_bgm;
	int item_se;
	int stairs_se;
	int e_attack_se;
	int p_attack_se;
	int magic_se;
	int recover_se;
	int run_se;

public:
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


private:
	Control();
	~Control();
	void sound();
public:
	void All();
	void Update();
	void initialize();
	void finalize();
	void player_positon(double* x, double* y);
	int dungeon_info(int x,int y);
	void set_dungeon_info(int info, int index_x, int index_y);
	//int item_info(int *item, int* a);
	void set_idx(int index);
	void get_p_status(p_status *pl);
	void set_p_status(p_status pl);
	bool set_p_damage(int damage);
	int get_floor();
	static Control& Instance() {//クラス静的変数、自身のインスタンスを格納
		static Control control;//静的変数として宣言
		return control;
	}

};