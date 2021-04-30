#include "Enemy.h"

Enemy::Enemy() {
	WHITE = GetColor(255, 255, 255);
	enemygh = NULL;
	enemy.type = 0;
	enemy.lifemax = 0;
	enemy.life = 0;
	enemy.power = 0;
	enemy.point = 0;
	enemy.x = 0;
	enemy.y = 0;
}

void Enemy::e_init(int fl) {
	std::random_device rnd;
	std::mt19937 ran(rnd());
	std::uniform_int_distribution<> randfloor(0, fl);
	std::uniform_int_distribution<> rand9(0, 9);
	if (fl >= 10) {
		enemy.type = rand9(ran);
	}
	else {
		enemy.type = randfloor(ran);
	}
	std::string temp;
	temp = "image/enemy" + std::to_string(enemy.type) + ".png";
	enemygh = LoadGraph(temp.c_str());
	int w, h;
	GetGraphSize(enemygh, &w, &h);
	enemy.lifemax = 50 * (enemy.type + 1) + fl * 10 + (rand9(ran) + 1) * 5;
	enemy.life = enemy.lifemax;
	enemy.power = 5 * (enemy.type + 1) + fl * 3 + (rand9(ran) + 1) * 2;
	enemy.point = 5 * (enemy.type + 1) + fl * 5 + (rand9(ran) + 1) * 2;
	enemy.x = 440 - w / 2;
	enemy.y = 560 - h;
}
bool Enemy::set_damage(int damage) {
	if (enemy.life > 0) {
		enemy.life -= damage;
	}
	if (enemy.life <= 0) {
		enemy.life = 0;
		return true;
	}
	else {
		return false;
	}
}
int  Enemy::get_power() {
	return enemy.power;
}
void Enemy::get_point(int *p) {
	*p = enemy.point;
}
void Enemy::draw(int damage,int step) {
	if (enemy.life > 0 && damage > 0) {
		if (damage % 2 == 0) {
			//•`‰æ‚µ‚È‚¢
		}
		else {
			DrawGraph(enemy.x, enemy.y, enemygh, TRUE);
		}
	}
	else if (enemy.life > 0) {
		DrawGraph(enemy.x, enemy.y + step, enemygh, TRUE);
	}

	std::string temp;
	temp = std::to_string(enemy.life) + "/" +std::to_string(enemy.lifemax);
	DrawFormatString(400, 580, WHITE, temp.c_str());
	
}
