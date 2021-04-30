#pragma once
#include "define.h"
#include "Control.h"

class Messege
{
private:
	int WHITE;
	int b_messege[MESSEGE::messege_num];
	int number[10];
	int number3[10];
	int index;
	int fl_num;
	char buf[100];
	int d_num;
public:
	Messege();
	void set(MESSEGE str);
	void set_dam(int damage);
	void draw();
};

