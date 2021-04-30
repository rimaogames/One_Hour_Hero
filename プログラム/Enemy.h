#pragma once
#include "define.h"
#include <random>
#include <string>
class Enemy
{
private:
	int WHITE;
	int enemygh;
	e_status enemy;
private:
public:
	Enemy();
	void e_init(int fl);
	bool set_damage(int damage);
	void get_point(int *p);
	int  get_power();
	void draw(int d_count,int step);
	
};

