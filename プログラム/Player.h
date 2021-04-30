#pragma once
#include "define.h"
class Player
{
private:
	double p_x;
	double p_y;

	int playergh[12];
	int width;
	int height;
	int xcount;
	int ycount;
	int ix;
	int iy;
	int index;
	MESSEGE get_item;
	p_status status;
private:
	void move();
	void draw();
	bool check();
public:
	Player();
	p_status get_status();
	void set_status(p_status pl);
	bool check_life();
	bool set_damage(int damage);
	bool All(bool init_flag);
	void get_potision(double* x, double* y);
	MESSEGE  get_item_info();
	void set_init_positon();

};

