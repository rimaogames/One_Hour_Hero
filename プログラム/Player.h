#pragma once
#include "define.h"
#include "InputKey.h"
#include "Control.h"
#include <random>


class Player
{
//�ϐ�
private:

	//�v���C���[�摜�̃O���t�B�b�N�n���h��
	int playergh[12];

	//�v���C���[�摜�̑傫��
	int width;
	int height;

	//�v���C���[�摜��ω����鎞�Ɏg���֐�
	int xcount;//���ɕ����ƃJ�E���g
	int ycount; //�c
	int ix; //���̓Y����
	int iy; //�c�̓Y����
	int index; //�O���t�B�b�N�n���h���ɓ������ۂ̓Y����


	//�v���C���[�̈ʒu
	double p_x; 
	double p_y;
    //���̃A�C�e������Ɏ�ɓ��ꂽ?
	int get_item= MESSEGE::GET_POTION;

	//�X�e�[�^�X
	p_status status;

//�֐�
private:

	void move(); //�ړ�
	void draw(); //�`��
	bool check(); //���ɃC�x���g������̂����ׂ�

public:
	Player();
	~Player();
	bool All(bool init_flag); //�v���C���[�̏������s���֐�

	p_status get_status(); //�X�e�[�^�X��Ԃ�
	void set_status(p_status pl); //�X�e�[�^�X���X�V
	bool check_life(); //�����Ă���̂����ׂ�B(�_���W�����Ȃ��ړ����Ɏg�p)
	bool set_damage(int damage); //�_���[�W���󂯂ă��C�t�̍X�V������
	void get_potision(double* x, double* y); //�|�W�V�����������ɓn���@
	int  get_item_info(); //�ǂ̃A�C�e������ɓ��ꂽ�̂���Ԃ�
	void set_init_positon(); //�����ʒu���Z�b�g����

};

