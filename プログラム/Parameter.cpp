#include "Parameter.h"

Parameter::Parameter() {

	//���C�u�����ŉ摜�̓ǂݍ���
	parameter = LoadGraph("image/parameter.png");

	if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number2) == -1) {
		MSG("�G���[����(number)");
	}
}


//////////�`��//////////
void Parameter::draw(p_status status) {

	///���C�u�����Ńp�����[�^�̘g�̉摜�̕`��
	DrawGraph(0, 630, parameter, TRUE);

	///////////////////�p�����[�^�̐����̕`��/////////////////

	//�`��Ɏg�p����ϐ��̐錾�Ə�����
	char buf[100];
	int hp_num=0, pow_num=0, fo_num=0, pot_num=0, mp_num=0;
	memset(buf, 0, sizeof(buf));


	//life�̕`��
	hp_num = sprintf_s(buf, "%d", status.life);//buf�Ƀn�C�X�R�A������Bhp_num�ɂ͕�����������
	for (int i = 0; i < hp_num; i++) {
		//���C�u�����Œl�̏����n�߂�100+�����̕�����,y���W645�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bnumber[buf[i]-0]��buf[i]�̃O���t�B�b�N�n���h�����擾�B�`�悷��
		DrawGraph(100 + (i * NUMBER2_W), 640, number2[buf[i] - '0'], TRUE);
	}

	//�ȉ����l

	//��
	pow_num = sprintf_s(buf, "%d", status.power);
	for (int i = 0; i < pow_num; i++) {
		DrawGraph(100 + (i * NUMBER2_W), 665, number2[buf[i] - '0'], TRUE);
	}

	//�����x
	fo_num = sprintf_s(buf, "%d", status.food);
	for (int i = 0; i < fo_num; i++) {
		DrawGraph(100 + (i * NUMBER2_W), 690, number2[buf[i] - '0'], TRUE);
	}

	//�|�[�V����
	pot_num = sprintf_s(buf, "%d", status.potion);
	for (int i = 0; i < pot_num; i++) {
		DrawGraph(270 + (i * NUMBER2_W), 640, number2[buf[i] - '0'], TRUE);
	}

	//���@��
	mp_num = sprintf_s(buf, "%d", status.mp);
	for (int i = 0; i < mp_num; i++) {
		DrawGraph(270 + (i * NUMBER2_W), 660, number2[buf[i] - '0'], TRUE);

	}
}


//���[�v�ōs�����s�֐�
void Parameter::All(p_status status) {

	//�����̃X�e�[�^�X��`��
	draw(status);
}