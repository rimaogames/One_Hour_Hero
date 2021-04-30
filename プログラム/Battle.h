#pragma once
#include "define.h"
#include "Control.h"
#include "InputKey.h"
#include "Enemy.h"
#include "Messege.h"
#include <sstream>
#include <random>

class Messege;

class Battle
{
private:
	Enemy *enemy;
	Messege* messege;
	int WHITE = (255, 255, 255);
	int BLACK = (0, 0, 0);
	int backgh;
	int efectgh[9];
	int magicgh[8];
	int step;
	int swing;
	int s_x;
	int s_y;
	int efe_cont;
	int mag_cont;
	bool use_item;
	int d_count;
	bool p_turn;
	bool end;
	int com[4];
	int now_com;
	int idx;
	int count;

	int e_damage;
	int p_damage;
	int e_point;
private:
	void draw();
	void command();
	void recover();
	void levelup(int point);
public:
	Battle();
	void init();
	void set_player_turn(bool flag);
	void set_effect(int s, int d, int e, int m,int st);
	void All();
};

