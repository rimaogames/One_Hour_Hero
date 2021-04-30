#include "Messege.h"

Messege::Messege() {
	WHITE = GetColor(255, 255, 255);
	b_messege[0] = LoadGraph("image/messege/new_floor.png");
	b_messege[1] = LoadGraph("image/messege/potion.png");
	b_messege[2] = LoadGraph("image/messege/gem.png");
	b_messege[3] = LoadGraph("image/messege/trap.png");
	b_messege[4] = LoadGraph("image/messege/food10.png");
	b_messege[5] = LoadGraph("image/messege/food100.png");
	b_messege[6] = LoadGraph("image/messege/enco.png");
	b_messege[7] = LoadGraph("image/messege/pla_turn.png");
	b_messege[8] = LoadGraph("image/messege/pla_attack.png");
	b_messege[9] = LoadGraph("image/messege/recover.png");
	b_messege[10] = LoadGraph("image/messege/magic.png");
	b_messege[11] = LoadGraph("image/messege/pla_avoid.png");
	b_messege[12] = LoadGraph("image/messege/do_run.png");
	b_messege[13] = LoadGraph("image/messege/cant_run.png");
	b_messege[14] = LoadGraph("image/messege/ene_attack.png");
	b_messege[15] = LoadGraph("image/messege/ene_avoid.png");
	b_messege[16] = LoadGraph("image/messege/attack_string.png");
	b_messege[17] = LoadGraph("image/messege/recover2.png");
	b_messege[18] = LoadGraph("image/messege/no_item.png");
	b_messege[19] = LoadGraph("image/messege/win.png");
	b_messege[20] = LoadGraph("image/messege/lose.png");
	b_messege[21] = LoadGraph("image/messege/levelup.png");
	if (LoadDivGraph("image/messege/number.png", 10, 10, 1, 27,34 , number)== -1) {
		MSG("�G���[����(number)");
	}
	if (LoadDivGraph("image/messege/number3.png", 10, 10, 1, 23, 29, number3) == -1) {
		MSG("�G���[����(number)");
	}
	index = 0;
	fl_num = 0;
	d_num = 0;
	memset(buf, 0, sizeof(buf));
}


void Messege::set(MESSEGE str) {
	index = str;
	if (str == MESSEGE::NEW_FLOOR) {
		memset(buf, 0, sizeof(buf));
		Control& cont = Control::Instance();
		fl_num = sprintf_s(buf, "%d", cont.get_floor());//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	}
}
void Messege::set_dam(int damage) {
	index = MESSEGE::DAMAGE;
	memset(buf, 0, sizeof(buf));
	d_num = sprintf_s(buf, "%d", damage);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
}

void Messege::draw() {
	if (index == MESSEGE::NEW_FLOOR) {
		for (int i = 0; i < fl_num; i++) {
			//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
			DrawGraph(410 + (i * NUMBER_W), 300, number[buf[i] - '0'], TRUE);
		}
		DrawGraph(300, 300, b_messege[index], TRUE);
	}
	else if (index == MESSEGE::DAMAGE) {
		for (int i = 0; i < d_num; i++) {
			//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
			DrawGraph(310 + (i * NUMBER3_W), 605, number3[buf[i] - '0'], TRUE);
		}
		DrawGraph(390, 600, b_messege[index], TRUE);
	}
	else {
		DrawGraph(330, 600, b_messege[index], TRUE);
	}
}