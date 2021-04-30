#include "Parameter.h"

Parameter::Parameter() {
	parameter = LoadGraph("image/parameter.png");

	if (LoadDivGraph("image/messege/number2.png", 10, 10, 1, 13, 17, number) == -1) {
		MSG("�G���[����(number)");
	}
}

void Parameter::draw(p_status status) {
	DrawGraph(0, 630, parameter, TRUE);
	char buf[100];
	int hp_num=0, pow_num=0, fo_num=0, pot_num=0, st_num=0;
	memset(buf, 0, sizeof(buf));

	hp_num = sprintf_s(buf, "%d", status.life);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	for (int i = 0; i < hp_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(100 + (i * NUMBER2_W), 640, number[buf[i] - '0'], TRUE);
	}
	pow_num = sprintf_s(buf, "%d", status.power);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	for (int i = 0; i < pow_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(100 + (i * NUMBER2_W), 665, number[buf[i] - '0'], TRUE);
	}
	fo_num = sprintf_s(buf, "%d", status.food);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	for (int i = 0; i < fo_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(100 + (i * NUMBER2_W), 690, number[buf[i] - '0'], TRUE);
	}

	pot_num = sprintf_s(buf, "%d", status.potion);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	for (int i = 0; i < pot_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(270 + (i * NUMBER2_W), 640, number[buf[i] - '0'], TRUE);
	}

	st_num = sprintf_s(buf, "%d", status.mp);//buf�Ƀn�C�X�R�A������Bfl=num�ɂ͕�����������
	for (int i = 0; i < st_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph(270 + (i * NUMBER2_W), 660, number[buf[i] - '0'], TRUE);

	}
}

void Parameter::All(p_status status) {
	draw(status);
}