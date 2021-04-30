#include "Player.h"
#include "InputKey.h"
#include "Control.h"
#include <random>

Player::Player() {
	//���C�u������player�摜�ǂݍ���
	if (LoadDivGraph("image/Player.png", 12, 3, 4, 80, 80, playergh) == -1) {
		MSG("�G���[����(player)");
	}
	/*if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number) == -1) {
		MSG("�G���[����(number)");
	}*/
	//parameter = LoadGraph("image/parameter.png");
	width = 80;
	height = 80;
	p_x = 4;
	p_y = 4;
	xcount = 0;
	ycount = 0;
	ix = 0;
	iy = 0;
	index = 0;
	get_item = MESSEGE::GET_POTION;
	status.food = 100;
	status.level = 1;
	status.life = 100;
	status.lifemax = 100;
	status.point = 0;
	status.pointmax = 30;
	status.power = 50;
	status.potion = 0;
	status.mp = 0;
}

void Player::move() {
	//Control�̎Q��
	Control& cont = Control::Instance();
	int pre_x = int(p_x);
	int pre_y = int(p_y);
	if (InputKey::GetKey(KEY_INPUT_UP)) {
		if (cont.dungeon_info(int(p_x), int(p_y) - 1) != 4) {
			p_y -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) {
		if (cont.dungeon_info(int(p_x), int(p_y) + 1) != 4) {
			p_y += 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_LEFT)) {
		if (cont.dungeon_info(int(p_x) - 1, int(p_y)) != 4) {
			p_x -= 0.1;
		}
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) {
		if (cont.dungeon_info(int(p_x) + 1, int(p_y)) != 4) {
			p_x += 0.1;
		}
	}

	if (pre_x != int(p_x) || pre_y != int(p_y)) {
		status.food -= 1;
		if (status.food < 0) status.food = 0;
		if (status.food == 0) {
			status.life -= 10;
			if(status.life<0) status.life = 0;
		}
	}





	//���̕����L�[�������Ă���Ԃ͑Ή������J�E���^�𑝂₵�A���񐔕��J�E���^���������Ȃ�摜�����̓���̂��̂ɐ؂�ւ���
	if (InputKey::GetKey(KEY_INPUT_LEFT)) {
		if (xcount < 0) xcount = 0;
		++xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) {
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_UP)) {
		if (ycount < 0) ycount = 0;
		++ycount;
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) {
		if (ycount > 0) ycount = 0;
		--ycount;
	}
	//count����摜�̓Y�������߂�
	ix = abs(xcount) % 40 / 10;//|xcount|%30/10=0����29��10�Ŋ����0����2�܂ł̒l�𓾂�=10count���Ƃɉ摜��ς��� 0,1,2,3�Ɠ���
	iy = abs(ycount) % 40 / 10;//|ycount|%30/10�@
	if (ix == 3)ix = 1; //3���P�ɂ��邱�Ƃ�0,1,2,1,0...�Ɠ����悤�ɂ���
	if (iy == 3)iy = 1;

	//������
	//xcount>0�͍������B2�s�ڂ̐擪�Y���𑫂��B
	if (xcount > 0) {
		ix += 3;
		index = ix;//3~5
	}
	else if (xcount < 0) {//xcoount<0�͉E�����B3�s�ڂ̐擪�Y���𑫂��B
		ix += 6;
		index = ix;//6~8
	}


	//�c����
	//ycount>0�͏�����B4�s�ڂ̐擪�Y���𑫂��B
	if (ycount > 0) {
		iy += 9;
		index = iy;//9~11
	}
	else if (ycount < 0) {//ycount<0�͉������B�擪�Y����0�Ȃ̂ŉ������Ȃ��Ă悢�B
		//iy += 0;
		index = iy;
	}


	
	//�L�[���͖����̎���count�����Z�b�g
	if (InputKey::GetKey(KEY_INPUT_LEFT) != 1 && InputKey::GetKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (InputKey::GetKey(KEY_INPUT_UP) != 1 && InputKey::GetKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}
}

bool Player::check() {
	Control& cont = Control::Instance();
	
	if (cont.dungeon_info(int(p_x), int(p_y)) == 1) {
		cont.set_dungeon_info(0, p_x, p_y);
		int temp = rand() % 100;
		if (temp <= 50) {
			status.potion += 1;
			get_item = MESSEGE::GET_POTION;
		}else
		if (50 < temp && temp<= 85) {
			status.mp += 1;
			get_item = MESSEGE::GET_STONE;
		}else
		if (85 < temp  && temp < 100) {
			status.food = status.food / 2;
			get_item = MESSEGE::GET_POISON;
		}
		return true;
	}
	else if (cont.dungeon_info(int(p_x), int(p_y)) == 2) 
	{
		cont.set_dungeon_info(0, p_x, p_y);
		int temp = rand() % 100;
		if (temp <=40) {
			cont.set_idx(4);
			return false;
		}else
		if (40<temp && temp<=50 ) {
			status.food += 10;
			status.life += 10;
			if (status.life > status.lifemax) status.life = status.lifemax;
			get_item = MESSEGE::GET_FOOD1;
			return true;
		}
		else
		if (50<temp && temp <100) {
			status.food += 100;
			status.life += 50;
			if (status.life > status.lifemax) status.life = status.lifemax;
			get_item = MESSEGE::GET_FOOD2;
			return true;
		}
	}
	else {
		if (cont.dungeon_info(int(p_x), int(p_y)) == 3) {
			cont.set_idx(2);
		}
		return false;
	}
}
void Player::set_init_positon() {
	std::random_device rnd;
	std::mt19937 ran(rnd());
	std::uniform_int_distribution<> randH(3, DUNG_H - 4);
	std::uniform_int_distribution<> randW(3, DUNG_W - 4);
	Control& cont = Control::Instance();
	while (1) {
		p_x = randW(ran);
		p_y = randH(ran);
		if (cont.dungeon_info(int(p_x), int(p_y)) == 0) break;
	}
}
void Player::draw() {

	DrawGraph(5*F_SIZE, 5*F_SIZE-40, playergh[index], TRUE);

}
p_status Player::get_status() {
	return status;
}
void Player::get_potision(double* x, double* y) {
	*x = p_x;
	*y = p_y;
}
MESSEGE  Player::get_item_info() {
	return get_item;
}
bool Player::check_life() {
	if (status.life == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Player::set_damage(int damage) {
	status.life -= damage;
	if (status.life < 0) status.life = 0;
	if (status.life ==0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::set_status(p_status pl) {
	status = pl;
}

bool Player::All(bool init_flag) {
	draw();
	if(!init_flag){
		move();
	    return check();
	}
	else {
		return false;
	}
}