#include "Messege.h"
#include "define.h"

Messege::Messege() {

	//���C�u�����ŉ摜�̓ǂݍ���
	b_messege[0] = LoadGraph("image/messege/new_floor.png"); //MESSEGE::NEW_FLOOR,
	b_messege[1] = LoadGraph("image/messege/potion.png");    //MESSEGE::GET_POTION,
	b_messege[2] = LoadGraph("image/messege/gem.png");       //MESSEGE::GET_STONE,
	b_messege[3] = LoadGraph("image/messege/trap.png");      //MESSEGE::GET_TRAP,
	b_messege[4] = LoadGraph("image/messege/food10.png");    //MESSEGE::GET_FOOD1,
	b_messege[5] = LoadGraph("image/messege/food100.png");   //MESSEGE::GET_FOOD2,
	b_messege[6] = LoadGraph("image/messege/enco.png");      //MESSEGE::ENCOUNTER,
	b_messege[7] = LoadGraph("image/messege/pla_turn.png");  //MESSEGE::P_TUEN,
	b_messege[8] = LoadGraph("image/messege/pla_attack.png");//MESSEGE::P_ATTACK,
	b_messege[9] = LoadGraph("image/messege/recover.png");   //MESSEGE::P_POTION,
	b_messege[10] = LoadGraph("image/messege/magic.png");    //MESSEGE::P_MAGIC,
	b_messege[11] = LoadGraph("image/messege/pla_avoid.png");//MESSEGE::P_AVOID,
	b_messege[12] = LoadGraph("image/messege/do_run.png");   //MESSEGE::P_RUN,
	b_messege[13] = LoadGraph("image/messege/cant_run.png"); //MESSEGE::P_NUO_RUN,
	b_messege[14] = LoadGraph("image/messege/ene_attack.png");//MESSEGE::E_ATTACK,,
	b_messege[15] = LoadGraph("image/messege/ene_avoid.png"); //MESSEGE::E_AVOID,
	b_messege[16] = LoadGraph("image/messege/attack_string.png");//MESSEGE::DAMAGE,
	b_messege[17] = LoadGraph("image/messege/recover2.png"); //MESSEGE::RECOVER2,
	b_messege[18] = LoadGraph("image/messege/no_item.png");  //MESSEGE::NO_ITEM,
	b_messege[19] = LoadGraph("image/messege/win.png");      //MESSEGE::WIN,
	b_messege[20] = LoadGraph("image/messege/lose.png");     //MESSEGE::LOSE,
	b_messege[21] = LoadGraph("image/messege/levelup.png");  //MESSEGE::LEVELUP,
	if (LoadDivGraph("image/messege/number.png", 10, 10, 1, 27,34 , number)== -1) { 
		MSG("�G���[����(number)");
	}
	if (LoadDivGraph("image/messege/number3.png", 10, 10, 1, 23, 29, number3) == -1) {
		MSG("�G���[����(number)");
	}

	//���̑�������
	index = 0;
	num = 0;
	memset(buf, 0, sizeof(buf));
}
Messege::~Messege() {

	//�摜���̂Ă�
	for (int i = 0; i < MESSEGE::messege_num; i++) {
		DeleteGraph(b_messege[i]);
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(number[i]);
		DeleteGraph(number3[i]);
	}
}
/////////���b�Z�[�W��ݒ肷��/////////
void Messege::set(int str) {

	//index�Ƀ��b�Z�[�W�̎�ނ��Z�b�g
	index = str;

	//�����A���b�Z�[�W��NEW_FLOOR�Ȃ��
	if (str == MESSEGE::NEW_FLOOR) {
		
		//buf��num��������
		memset(buf, 0, sizeof(buf));
		num = 0;
		//Control�̎Q��
		Control& cont = Control::Instance();

		//buf�ɊK��������Bnum�ɂ͕�����������
		num = sprintf_s(buf, "%d", cont.get_floor());
	}
}

///////�_���[�W����̃��b�Z�[�W��ݒ肷��/////////
void Messege::set_dam(int damage) {

	//index�Ƀ��b�Z�[�W�̎�ނ��Z�b�g
	index = MESSEGE::DAMAGE;

	//buf��num��������
	memset(buf, 0, sizeof(buf));
	num = 0;

	//buf�Ɉ����̃_���[�W������Bnum�ɂ͕�����������
	num = sprintf_s(buf, "%d", damage);
}


/////////�`��////////////
void Messege::draw() {

	///�`�悷�郁�b�Z�[�W��NEW_FLOOR�Ȃ��
	if (index == MESSEGE::NEW_FLOOR) 
	{

		//�K���̕`��
		for (int i = 0; i < num; i++) {
			//���C�u������x���W410+i*�����̕��Ay���W300�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bnumber[buf[i]-0]�Ő����̃O���t�B�b�N�n���h�����擾
			DrawGraph(410 + (i * NUMBER1_W), 300, number[buf[i] - '0'], TRUE);
		}

		//���C�u�����ŐV�K�w�������̐����ȊO�̃��b�Z�[�W��`��
		DrawGraph(300, 300, b_messege[index], TRUE);
	}

	//�`�悷�郁�b�Z�[�W��DAMAGE�Ȃ��
	else if (index == MESSEGE::DAMAGE)
	{    
		//�_���[�W���̕`��(�K���Ɠ��l�ɂ���)
		for (int i = 0; i < num; i++) {
			DrawGraph(310 + (i * NUMBER3_W), 605, number3[buf[i] - '0'], TRUE);
		}

		//���C�u�����Ń_���[�W���ȊO�̃��b�Z�[�W��`��
		DrawGraph(390, 600, b_messege[index], TRUE);
	}

	//���̃��b�Z�[�W
	else {

		//���C�u�����Ń��b�Z�[�W��`��
		DrawGraph(330, 600, b_messege[index], TRUE);
	}
}